#include "REL/Iddb.hpp"

#include "REL/Module.hpp"

#include "REX/Crc.hpp"
#include "REX/ErrorCode.hpp"
#include "REX/Format.hpp"
#include "REX/Locale.hpp"
#include "REX/Message.hpp"
#include "REX/W32/KERNEL32.hpp"

#if COMMONLIB_RUNTIME_VR == 1
#include "REX/Convert.hpp"

#include <rapidcsv.h>
#endif

namespace REL
{
	enum class Iddb::FormatVersion : std::int32_t
	{
		kNone = std::numeric_limits<std::underlying_type_t<FormatVersion>>::min(),
		kVR = -1,
		kV0 = 0,
		kV1 = 1,
		kV2 = 2,
		kV5 = 5
	};

	class Iddb::Mapping final
	{
	public:
		std::uintptr_t id;
		std::ptrdiff_t offset;
	};

	class Iddb::Stream final
	{
	public:
		using value_type = std::fstream;

		Stream() = default;
		~Stream() noexcept = default;

		Stream(const Stream&) = delete;
		Stream(Stream&&) noexcept = default;

		Stream& operator=(const Stream&) = delete;
		Stream& operator=(Stream&&) noexcept = default;

		void Open(const std::filesystem::path& a_path, std::ios::openmode a_mode) noexcept(false)
		{
			_stream.exceptions(std::ios::badbit | std::ios::failbit | std::ios::eofbit);
			_stream.open(a_path, a_mode);
		}

		template <class T>
		void ReadIn(T& a_in) noexcept(false)
		{
			_stream.read(reinterpret_cast<char*>(std::addressof(a_in)), sizeof(T));
		}

		void ReadIn(std::span<char> a_in) noexcept(false)
		{
			_stream.read(a_in.data(), static_cast<std::streamsize>(a_in.size()));
		}

		template <class T>
		[[nodiscard]] T ReadOut() noexcept(false)
			requires(std::is_arithmetic_v<T>)
		{
			auto result = T();
			ReadIn(result);
			return result;
		}

	private:
		value_type _stream;
	};

	class Iddb::HeaderV2 final
	{
	public:
		HeaderV2() = default;
		~HeaderV2() noexcept = default;

		HeaderV2(const HeaderV2&) = delete;
		HeaderV2(HeaderV2&&) noexcept = default;

		HeaderV2& operator=(const HeaderV2&) = delete;
		HeaderV2& operator=(HeaderV2&&) noexcept = default;

		[[nodiscard]] std::string_view GetName() const noexcept { return { _name.data(), _nameLength }; }
		[[nodiscard]] std::size_t GetPointerSize() const noexcept { return static_cast<std::size_t>(_pointerSize); }
		[[nodiscard]] std::size_t GetAddressCount() const noexcept { return static_cast<std::size_t>(_addressCount); }

		[[nodiscard]] REX::Version GetGameVersion() const noexcept
		{
			auto version = REX::Version();
			for (auto i = static_cast<REX::Version::size_type>(0); i < REX::Version::MAX_SIZE; i++) {
				version[i] = static_cast<REX::Version::value_type>(_gameVersion[i]);
			}

			return version;
		}

		void Load(Iddb::Stream& a_stream)
		{
			a_stream.ReadIn(_gameVersion);
			a_stream.ReadIn(_nameLength);
			a_stream.ReadIn(std::span(_name.data(), _nameLength));
			a_stream.ReadIn(_pointerSize);
			a_stream.ReadIn(_addressCount);
		}

	private:
		std::array<std::uint32_t, 4> _gameVersion{ 0 };
		std::uint32_t _nameLength{ 0 };
		std::array<char, 64> _name{ '\0' };
		std::int32_t _pointerSize{ 0 };
		std::int32_t _addressCount{ 0 };
	};

	class Iddb::HeaderV5 final
	{
	public:
		HeaderV5() = default;
		~HeaderV5() noexcept = default;

		HeaderV5(const HeaderV5&) = delete;
		HeaderV5(HeaderV5&&) noexcept = default;

		HeaderV5& operator=(const HeaderV5&) = delete;
		HeaderV5& operator=(HeaderV5&&) noexcept = default;

		[[nodiscard]] std::string_view GetName() const noexcept { return _name.data(); }
		[[nodiscard]] std::size_t GetPointerSize() const noexcept { return static_cast<std::size_t>(_pointerSize); }
		[[nodiscard]] std::int32_t GetDataFormat() const noexcept { return _dataFormat; }
		[[nodiscard]] std::size_t GetOffsetCount() const noexcept { return static_cast<std::size_t>(_offsetCount); }

		[[nodiscard]] REX::Version GetGameVersion() const noexcept
		{
			auto version = REX::Version();
			for (auto i = static_cast<REX::Version::size_type>(0); i < REX::Version::MAX_SIZE; i++) {
				version[i] = static_cast<REX::Version::value_type>(_gameVersion[i]);
			}

			return version;
		}

		void Load(Iddb::Stream& a_stream)
		{
			a_stream.ReadIn(_gameVersion);
			a_stream.ReadIn(_name);
			a_stream.ReadIn(_pointerSize);
			a_stream.ReadIn(_dataFormat);
			a_stream.ReadIn(_offsetCount);
		}

	private:
		std::array<std::uint32_t, 4> _gameVersion{};
		std::array<char, 64> _name{ '\0' };
		std::int32_t _pointerSize{ 0 };
		std::int32_t _dataFormat{ 0 };
		std::int32_t _offsetCount{ 0 };
	};

	class Iddb::LoaderInfo final
	{
	public:
		std::vector<std::string> rootNames;
		std::unordered_map<REX::Version, std::uint64_t> versionCrcMap;
		bool supportsStreaming{ true };
	};

	class Iddb::IFormatInfo
		: public std::enable_shared_from_this<IFormatInfo>
	{
	public:
		class LoadContext final
		{
		public:
			std::filesystem::path path;
			Stream stream;
			REX::NotNull<std::shared_ptr<LoaderInfo>> loaderInfo;
			REX::NotNull<std::shared_ptr<REX::MemoryMap>> memoryMap;
		};

		IFormatInfo() = default;
		virtual ~IFormatInfo() noexcept = default;

		IFormatInfo(const IFormatInfo&) = delete;
		IFormatInfo(IFormatInfo&&) = delete;

		IFormatInfo& operator=(const IFormatInfo&) = delete;
		IFormatInfo& operator=(IFormatInfo&&) = delete;

		[[nodiscard]] virtual std::ptrdiff_t GetOffset(std::uintptr_t a_id) const noexcept = 0;
		virtual void Load(LoadContext& a_context) = 0;

	protected:
		static void ValidateFile(const REX::NotNull<std::shared_ptr<LoaderInfo>>& a_loaderInfo, const REX::NotNull<std::shared_ptr<REX::MemoryMap>>& a_memoryMap)
		{
			const auto moduleVersion = REL::Module::GetSingleton()->GetVersion();

			const auto crcHashIt = a_loaderInfo->versionCrcMap.find(moduleVersion);
			if (crcHashIt == a_loaderInfo->versionCrcMap.end()) {
				return;
			}

			const auto expectedHash = crcHashIt->second;
			const auto actualHash = REX::HashCrc64(std::string_view{ reinterpret_cast<const char*>(a_memoryMap->data()), a_memoryMap->size() });

			if (expectedHash != actualHash) [[unlikely]] {
				REX::Fail(
					"Invalid Address Library loaded.\n"
					"Redownload Address Library for your module version.\n"
					"Module Version: {}"sv,
					moduleVersion);
			}
		}
	};

	class Iddb::FormatInfoV0
		: public IFormatInfo
	{
	public:
		FormatInfoV0() = default;
		~FormatInfoV0() noexcept override = default;

		FormatInfoV0(const FormatInfoV0&) = delete;
		FormatInfoV0(FormatInfoV0&&) = delete;

		FormatInfoV0& operator=(const FormatInfoV0&) = delete;
		FormatInfoV0& operator=(FormatInfoV0&&) = delete;

		[[nodiscard]] std::ptrdiff_t GetOffset(std::uintptr_t a_id) const noexcept override
		{
			if (_mapping.empty()) [[unlikely]] {
				REX::Fail("Failed to find Address Library offset due to empty mapping."sv);
			}

			const auto mappingElement = Mapping{
				.id = a_id,
				.offset = 0
			};

			const auto mappingIt = std::ranges::lower_bound(_mapping, mappingElement, [](const Mapping& a_lhs, const Mapping& a_rhs) {
				return a_lhs.id < a_rhs.id;
			});

			if (mappingIt == _mapping.end()) [[unlikely]] {
				REX::Fail(
					"Failed to find offset for Address Library ID.\n"
					"Invalid ID: {}\n"
					"Module Version: {}"sv,
					a_id, REL::Module::GetSingleton()->GetVersion());
			}

			return mappingIt->offset;
		}

		void Load(LoadContext& a_context) override
		{
			const auto mapName = GetMemoryMapName(REL::Module::GetSingleton()->GetVersion());

			const auto createError = a_context.memoryMap->Create(false, a_context.path, mapName);
			if (createError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				REX::Fail(
					"Failed to create Address Library memory map.\n"
					"File Path: \"{}\"\n"
					"System Error (0x{:08X}): {}"sv,
					a_context.path.generic_string(), createError.value(), createError.message());
			}

			ValidateFile(a_context.loaderInfo, a_context.memoryMap);

			_mapping = {
				reinterpret_cast<Mapping*>(a_context.memoryMap->data() + sizeof(std::uintptr_t)),
				*reinterpret_cast<std::uintptr_t*>(a_context.memoryMap->data())
			};
		}

	protected:
		std::span<Mapping> _mapping;
	};

	class Iddb::FormatInfoV1 final
		: public FormatInfoV0
	{
	public:
		FormatInfoV1() = default;
		~FormatInfoV1() noexcept override = default;

		FormatInfoV1(const FormatInfoV1&) = delete;
		FormatInfoV1(FormatInfoV1&&) = delete;

		FormatInfoV1& operator=(const FormatInfoV1&) = delete;
		FormatInfoV1& operator=(FormatInfoV1&&) = delete;
	};

	class Iddb::FormatInfoV2 final
		: public FormatInfoV0
	{
	public:
		FormatInfoV2() = default;
		~FormatInfoV2() noexcept override = default;

		FormatInfoV2(const FormatInfoV2&) = delete;
		FormatInfoV2(FormatInfoV2&&) = delete;

		FormatInfoV2& operator=(const FormatInfoV2&) = delete;
		FormatInfoV2& operator=(FormatInfoV2&&) = delete;

		void Load(LoadContext& a_context) override
		{
			try {
				auto header = HeaderV2();
				header.Load(a_context.stream);

				const auto& module = REL::Module::GetSingleton();
				if (header.GetGameVersion() != module->GetVersion()) [[unlikely]] {
					REX::Fail(
						"Address Library version mismatch.\n"
						"Expected Version: {}\n"
						"Actual Version: {}"sv,
						module->GetVersion(), header.GetGameVersion());
				}

				const auto mapName = GetMemoryMapName(module->GetVersion());
				const auto byteSize = header.GetAddressCount() * sizeof(Mapping);

				if (!a_context.memoryMap->Create(true, mapName, byteSize)) [[unlikely]] {
					const auto currentError = REX::GetCurrentSystemError();
					REX::Fail(
						"Failed to create Address Library memory map.\n"
						"System Error (0x{:08X}): {}"sv,
						currentError.value(), currentError.message());
				}

				ValidateFile(a_context.loaderInfo, a_context.memoryMap);

				_mapping = { reinterpret_cast<Mapping*>(a_context.memoryMap->data()), header.GetAddressCount() };

				if (!a_context.memoryMap->IsOwner()) {
					return;
				}

				UnpackFile(a_context.stream, header);

				std::sort(std::execution::par, _mapping.begin(), _mapping.end(), [](const Mapping& a_lhs, const Mapping& a_rhs) {
					return a_lhs.id < a_rhs.id;
				});
			}
			catch (const std::ios::failure& error) {
				REX::Fail(
					"Failed to open Address Library file.\n"
					"File Path: \"{}\"\n"
					"Exception Error: {}"sv,
					a_context.path.generic_string(), error.what());
			}
		}

	private:
		void UnpackFile(Stream& a_stream, const HeaderV2& a_header)
		{
			auto type = 0ui8;
			auto currentId = static_cast<std::uintptr_t>(0);
			auto currentOffset = static_cast<std::ptrdiff_t>(0);
			auto previousId = static_cast<std::uintptr_t>(0);
			auto previousOffset = static_cast<std::ptrdiff_t>(0);

			for (auto& mapping : _mapping) {
				a_stream.ReadIn(type);

				const auto lowPart = static_cast<std::uint8_t>(type & 0x0F);
				const auto highPart = static_cast<std::uint8_t>(type >> 4);

				switch (lowPart) {
					case 0: {
						a_stream.ReadIn(currentId);
						break;
					}
					case 1: {
						currentId = previousId + 1;
						break;
					}
					case 2: {
						currentId = previousId + a_stream.ReadOut<std::uint8_t>();
						break;
					}
					case 3: {
						currentId = previousId - a_stream.ReadOut<std::uint8_t>();
						break;
					}
					case 4: {
						currentId = previousId + a_stream.ReadOut<std::uint16_t>();
						break;
					}
					case 5: {
						currentId = previousId - a_stream.ReadOut<std::uint16_t>();
						break;
					}
					case 6: {
						currentId = a_stream.ReadOut<std::uint16_t>();
						break;
					}
					case 7: {
						currentId = a_stream.ReadOut<std::uint32_t>();
						break;
					}
					[[unlikely]] default: {
						REX::Fail("Failed to load Address Library due to unhandled low type."sv);
					}
				}

				const auto temp = static_cast<std::ptrdiff_t>((highPart & 8) != 0 ? (previousOffset / a_header.GetPointerSize()) : previousOffset);

				switch (highPart & 7) {
					case 0: {
						a_stream.ReadIn(currentOffset);
						break;
					}
					case 1: {
						currentOffset = temp + 1;
						break;
					}
					case 2: {
						currentOffset = temp + a_stream.ReadOut<std::uint8_t>();
						break;
					}
					case 3: {
						currentOffset = temp - a_stream.ReadOut<std::uint8_t>();
						break;
					}
					case 4: {
						currentOffset = temp + a_stream.ReadOut<std::uint16_t>();
						break;
					}
					case 5: {
						currentOffset = temp - a_stream.ReadOut<std::uint16_t>();
						break;
					}
					case 6: {
						currentOffset = a_stream.ReadOut<std::uint16_t>();
						break;
					}
					case 7: {
						currentOffset = a_stream.ReadOut<std::uint32_t>();
						break;
					}
					[[unlikely]] default: {
						REX::Fail("Failed to load Address Library due to unhandled high type."sv);
					}
				}

				if ((highPart & 8) != 0) {
					currentOffset *= static_cast<std::ptrdiff_t>(a_header.GetPointerSize());
				}

				mapping = { .id = currentId, .offset = currentOffset };
				previousOffset = currentOffset;
				previousId = currentId;
			}
		}
	};

	class Iddb::FormatInfoV5 final
		: public IFormatInfo
	{
	public:
		FormatInfoV5() = default;
		~FormatInfoV5() noexcept override = default;

		FormatInfoV5(const FormatInfoV5&) = delete;
		FormatInfoV5(FormatInfoV5&&) = delete;

		FormatInfoV5& operator=(const FormatInfoV5&) = delete;
		FormatInfoV5& operator=(FormatInfoV5&&) = delete;

		[[nodiscard]] std::ptrdiff_t GetOffset(std::uintptr_t a_id) const noexcept override
		{
			if (_mapping.empty()) [[unlikely]] {
				REX::Fail("Failed to find Address Library offset due to empty mapping."sv);
			}

			const auto offset = static_cast<std::ptrdiff_t>(_mapping[a_id]);
			if (offset == 0) [[unlikely]] {
				REX::Fail(
					"Failed to find offset for Address Library ID.\n"
					"Invalid ID: {}\n"
					"Module Version: {}"sv,
					a_id, REL::Module::GetSingleton()->GetVersion());
			}

			return offset;
		}

		void Load(LoadContext& a_context) override
		{
			try {
				auto header = HeaderV5();
				header.Load(a_context.stream);

				const auto& module = REL::Module::GetSingleton();
				if (header.GetGameVersion() != module->GetVersion()) [[unlikely]] {
					REX::Fail(
						"Address Library version mismatch.\n"
						"Expected Version: {}\n"
						"Actual Version: {}"sv,
						module->GetVersion(), header.GetGameVersion());
				}

				const auto mapName = GetMemoryMapName(module->GetVersion());

				const auto createError = a_context.memoryMap->Create(false, a_context.path, mapName);
				if (createError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					REX::Fail(
						"Failed to create Address Library memory map.\n"
						"File Path: \"{}\"\n"
						"System Error (0x{:08X}): {}"sv,
						a_context.path.generic_string(), createError.value(), createError.message());
				}

				ValidateFile(a_context.loaderInfo, a_context.memoryMap);

				_mapping = { reinterpret_cast<std::uint32_t*>(a_context.memoryMap->data() + sizeof(HeaderV5)), header.GetOffsetCount() };
			}
			catch (const std::ios::failure& error) {
				REX::Fail(
					"Failed to open Address Library file.\n"
					"File Path: \"{}\"\n"
					"Exception Error: {}"sv,
					a_context.path.generic_string(), error.what());
			}
		}

	private:
		std::span<std::uint32_t> _mapping;
	};

#if COMMONLIB_RUNTIME_VR == 1
	class Iddb::FormatInfoVR final
		: public IFormatInfo
	{
	public:
		FormatInfoVR() = default;
		~FormatInfoVR() noexcept override = default;

		FormatInfoVR(const FormatInfoVR&) = delete;
		FormatInfoVR(FormatInfoVR&&) = delete;

		FormatInfoVR& operator=(const FormatInfoVR&) = delete;
		FormatInfoVR& operator=(FormatInfoVR&&) = delete;

		[[nodiscard]] std::ptrdiff_t GetOffset(std::uintptr_t a_id) const noexcept override
		{
			if (_mapping.empty()) [[unlikely]] {
				REX::Fail("Failed to find Address Library offset due to empty mapping."sv);
			}

			const auto mappingElement = Mapping{
				.id = a_id,
				.offset = 0
			};

			const auto mappingIt = std::ranges::lower_bound(_mapping, mappingElement, [](const Mapping& a_lhs, const Mapping& a_rhs) {
				return a_lhs.id < a_rhs.id;
			});

			if (mappingIt == _mapping.end()) [[unlikely]] {
				REX::Fail(
					"Failed to find offset for Address Library ID.\n"
					"Invalid ID: {}\n"
					"Module Version: {}"sv,
					a_id, REL::Module::GetSingleton()->GetVersion());
			}

			return mappingIt->offset;
		}

		void Load(LoadContext& a_context) override
		{
			auto file = rapidcsv::Document(a_context.path.generic_string());

			auto id = 0ui64;
			auto offset = std::string();

			auto addressCount = file.GetCell<std::size_t>(0, 0);
			auto version = file.GetCell<std::string>(1, 0);

			if (file.GetRowCount() > addressCount + 1) [[unlikely]] {
				REX::Fail(
					"The VR Address Library has more entries than expected.\n"
					"Version: {}\n"
					"Expected Entries: {}\n"
					"Actual Entries: {}"sv,
					version, addressCount, file.GetRowCount() - 1);
			}

			if (file.GetRowCount() < addressCount + 1) [[unlikely]] {
				REX::Fail(
					"The VR Address Library has fewer entries than expected.\n"
					"Version: {}\n"
					"Expected Entries: {}\n"
					"Actual Entries: {}"sv,
					version, addressCount, file.GetRowCount() - 1);
			}

			auto index = static_cast<std::size_t>(1);

			for (; index < file.GetRowCount(); index++) {
				id = file.GetCell<std::size_t>(0, index);
				offset = file.GetCell<std::string_view>(1, index);

				const auto offsetNumber = REX::FromString<std::ptrdiff_t>(offset, REX::IntFormat::kHexadecimal);
				if (!offsetNumber) [[unlikely]] {
					REX::Fail(
						"The VR Address Library found an invalid offset.\n"
						"Version: {}\n"
						"Invalid ID: {}\n"
						"Invalid Offset: {}"sv,
						version, id, offset);
				}

				auto mappingElement = Mapping{
					.id = id,
					.offset = *offsetNumber
				};

				_mapping.push_back(mappingElement);
			}

			std::sort(std::execution::par, _mapping.begin(), _mapping.end(), [](const Mapping& a_lhs, const Mapping& a_rhs) {
				return a_lhs.id < a_rhs.id;
			});
		}

	private:
		std::vector<Mapping> _mapping;
	};
#endif
}

namespace REL
{
	Iddb::Iddb()
		// clang-format off
		: _loaderInfoMap{
			{
				"SKSE"sv,
				std::make_shared<LoaderInfo>(LoaderInfo{
					.rootNames = { "versionlib"s, "version"s },
					.versionCrcMap = {
						{ REX::Version(1, 5, 97, 0), 0x7ED322899C8999D7ui64 },
						{ REX::Version(1, 6, 640, 0), 0x77C2AD2AEF8A9417ui64 },
						{ REX::Version(1, 6, 659, 0), 0xEFA49B8046A44D50ui64 },
						{ REX::Version(1, 6, 1170, 0), 0x0A6C2093652D2622ui64 },
						{ REX::Version(1, 6, 1179, 0), 0xE2D655E897B0D016ui64 }
					}
				})
			},
			{
				"F4SE"sv,
				std::make_shared<LoaderInfo>(LoaderInfo{
					.rootNames = { "version"s },
					.versionCrcMap = {
						{ REX::Version(1, 10, 163, 0), 0x9FACC538CC3422A1ui64 },
						{ REX::Version(1, 10, 984, 0), 0x7E4586F67B484062ui64 },
						{ REX::Version(1, 11, 159, 0), 0xAC7DF73ABF00FFEBui64 },
						{ REX::Version(1, 11, 191, 0), 0xB3991DE2AC1EB7F9ui64 }
					},
					.supportsStreaming = false
				})
			},
			{
				"SFSE"sv,
				std::make_shared<LoaderInfo>(LoaderInfo{
					.rootNames = { "versionlib"s },
					.versionCrcMap = {
						{ REX::Version(1, 16, 236, 0), 0x38F2B17245B91198ui64 }
					}
				})
			},
			{
				"OBSE"sv,
				std::make_shared<LoaderInfo>(LoaderInfo{
					.rootNames = { "versionlib"s },
					.versionCrcMap = {
						{ REX::Version(1, 512, 105, 0), 0x6FF49281899E8B89ui64 }
					}
				})
			},
			},
		  _formatInfoMap{
#if COMMONLIB_RUNTIME_VR == 1
			  { FormatVersion::kVR, std::make_shared<FormatInfoVR>() },
#endif
			  { FormatVersion::kV0, std::make_shared<FormatInfoV0>() },
			  { FormatVersion::kV1, std::make_shared<FormatInfoV1>() },
			  { FormatVersion::kV2, std::make_shared<FormatInfoV2>() },
			  { FormatVersion::kV5, std::make_shared<FormatInfoV5>() }
		  },
		  // clang-format on
		  _memoryMap(std::make_shared<REX::MemoryMap>())
	{
	}

	Iddb::~Iddb() noexcept = default;

	std::string Iddb::GetMemoryMapName(REX::Version a_version)
	{
		return REX::Format("COMMONLIB_IDDB_OFFSETS_{}"sv, a_version.ToString('_'));
	}

	std::ptrdiff_t Iddb::GetOffset(std::uintptr_t a_id) const noexcept
	{
		if (!_currentFormatInfo) [[unlikely]] {
			REX::Fail("Failed to get Address Library offset due to missing format info."sv);
		}

		return _currentFormatInfo->GetOffset(a_id);
	}

	void Iddb::Load()
	{
		auto pluginPathBuffer = std::array<wchar_t, REX::W32::MAX_PATH>();
		REX::W32::GetModuleFileNameW(REX::W32::GetCurrentModule(), pluginPathBuffer.data(), static_cast<std::uint32_t>(pluginPathBuffer.size()));

		const auto pluginPath = std::filesystem::path(pluginPathBuffer.data(), std::filesystem::path::generic_format);
		const auto loaderName = pluginPath.parent_path().parent_path().filename().generic_string();

		const auto loaderIt = _loaderInfoMap.find(REX::ToUpper(loaderName));
		if (loaderIt == _loaderInfoMap.end()) [[unlikely]] {
			REX::Fail(
				"Failed to determine Address Library loader.\n"
				"File Loader: \"{}\""sv,
				loaderName);
		}

		const auto loaderInfo = loaderIt->second;

		const auto& module = REL::Module::GetSingleton();
		const auto moduleVersion = module->GetVersion().ToString('-');
		const auto moduleFileExtension = module->GetIsRuntimeVR() ? ".csv"sv : ".bin"sv;

		for (const auto& rootName : loaderInfo->rootNames) {
			const auto fullLoaderName = REX::Format("{}-{}{}"sv, rootName, moduleVersion, moduleFileExtension);

			auto isFileError = REX::SystemError();
			auto fullLoaderPath = pluginPath.parent_path() / fullLoaderName;

			if (!std::filesystem::is_regular_file(fullLoaderPath, isFileError)) {
				continue;
			}

			_path = std::move(fullLoaderPath);
			break;
		}

		if (_path.empty()) [[unlikely]] {
			REX::Fail(
				"Failed to determine Address Library path.\n"
				"File Loader: \"{}\"\n"
				"Module Version: {}"sv,
				loaderName,
				moduleVersion);
		}

		_currentLoaderInfo = loaderInfo.get();

		auto stream = Stream();
		auto formatVersion = FormatVersion::kNone;

		if (module->GetIsRuntimeVR())
#if COMMONLIB_RUNTIME_VR == 0
			[[unlikely]]
#endif
		{
#if COMMONLIB_RUNTIME_VR == 1
			formatVersion = FormatVersion::kVR;
#else
			REX::Fail("Failed to initialize Address Library due to VR not being supported in this build."sv);
#endif
		}
		else if (!_currentLoaderInfo->supportsStreaming) {
			formatVersion = FormatVersion::kV0;
		}
		else {
			try {
				stream.Open(_path, std::ios::in | std::ios::binary);
				formatVersion = static_cast<FormatVersion>(stream.ReadOut<std::uint32_t>());
			}
			catch (const std::ios::failure& error) {
				REX::Fail(
					"Failed to read Address Library format version.\n"
					"Exception Error: {}"sv,
					error.what());
			}

			if (formatVersion <= FormatVersion::kV0 || formatVersion > FormatVersion::kV5) [[unlikely]] {
				REX::Fail(
					"Unsupported Address Library format version.\n"
					"Format Version: {}"sv,
					std::to_underlying(formatVersion));
			}
		}

		const auto formatIt = _formatInfoMap.find(formatVersion);
		if (formatIt == _formatInfoMap.end()) [[unlikely]] {
			REX::Fail(
				"Failed to find Address Library format info.\n"
				"Format Version: {}"sv,
				std::to_underlying(formatVersion));
		}

		_currentFormatInfo = formatIt->second.get();

		auto loadContext = IFormatInfo::LoadContext{
			.path = _path,
			.stream = std::move(stream),
			.loaderInfo = _currentLoaderInfo,
			.memoryMap = _memoryMap
		};

		_currentFormatInfo->Load(loadContext);
	}
}
