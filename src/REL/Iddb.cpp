#include "REL/Iddb.hpp"

#include "REL/Module.hpp"
#include "REL/Runtime.hpp"
#include "REX/Crc.hpp"
#include "REX/Error.hpp"
#include "REX/FileMemoryMap.hpp"
#include "REX/FileStream.hpp"
#include "REX/Formatting.hpp"
#include "REX/Localization.hpp"
#include "REX/Message.hpp"
#include "REX/NotNull.hpp"
#include "REX/StaticString.hpp"
#include "REX/System.hpp"
#include "REX/Version.hpp"

#if (COMMONLIB_RUNTIME_VR == 1)
#include "REX/Conversion.hpp"
#endif

namespace REL
{
	enum class Iddb::FormatVersion : std::int32_t
	{
		None = std::numeric_limits<std::underlying_type_t<FormatVersion>>::min(),
		VR = -1,

		Zero = 0,
		One = 1,
		Two = 2,
		Five = 5,

		_Min = Zero,
		_Max = Five,

		_Count = _Max - 1
	};

	class Iddb::Mapping final
	{
	public:
		std::uintptr_t id;
		std::ptrdiff_t offset;
	};

	class Iddb::IHeader
	{
	public:
		IHeader() = default;
		virtual ~IHeader() noexcept = default;

		IHeader(const IHeader&) = delete;
		IHeader(IHeader&&) noexcept = default;

		auto operator=(const IHeader&) -> IHeader& = delete;
		auto operator=(IHeader&&) noexcept -> IHeader& = default;

		[[nodiscard]]
		virtual auto GetName() const noexcept -> std::string_view = 0;
		[[nodiscard]]
		virtual auto GetPointerSize() const noexcept -> std::size_t = 0;
		[[nodiscard]]
		virtual auto GetAddressCount() const noexcept -> std::size_t = 0;
		[[nodiscard]]
		virtual auto GetGameVersion() const noexcept -> REX::Version = 0;

		[[nodiscard]]
		virtual auto LoadStream(REX::FileStream& a_stream) noexcept -> REX::SystemError = 0;
	};

	class Iddb::HeaderV2 final : public IHeader
	{
	public:
		HeaderV2() = default;
		~HeaderV2() noexcept override = default;

		HeaderV2(const HeaderV2&) = delete;
		HeaderV2(HeaderV2&&) noexcept = default;

		auto operator=(const HeaderV2&) -> HeaderV2& = delete;
		auto operator=(HeaderV2&&) noexcept -> HeaderV2& = default;

		[[nodiscard]]
		auto GetName() const noexcept -> std::string_view override
		{
			return {_name.data(), _nameSize};
		}

		[[nodiscard]]
		auto GetPointerSize() const noexcept -> std::size_t override
		{
			return static_cast<std::size_t>(_pointerSize);
		}

		[[nodiscard]]
		auto GetAddressCount() const noexcept -> std::size_t override
		{
			return static_cast<std::size_t>(_addressCount);
		}

		[[nodiscard]]
		auto GetGameVersion() const noexcept -> REX::Version override
		{
			auto version = REX::Version();
			for (auto i = static_cast<decltype(version)::size_type>(0); i < version.size(); i++) {
				version[i] = static_cast<decltype(version)::value_type>(_gameVersion[i]);
			}

			return version;
		}

		auto LoadStream(REX::FileStream& a_stream) noexcept -> REX::SystemError override
		{
			const auto readGameVersionError = a_stream.Read(_gameVersion);
			if (readGameVersionError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return readGameVersionError;
			}

			const auto readNameSizeError = a_stream.Read(_nameSize);
			if (readNameSizeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return readNameSizeError;
			}

			const auto readNameError = a_stream.Read(std::span{_name.data(), _nameSize});
			if (readNameError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return readNameError;
			}

			const auto readPointerSizeError = a_stream.Read(_pointerSize);
			if (readPointerSizeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return readPointerSizeError;
			}

			const auto readAddressCountError = a_stream.Read(_addressCount);
			if (readAddressCountError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return readAddressCountError;
			}

			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

	private:
		std::array<std::uint32_t, 4> _gameVersion{0};
		std::uint32_t _nameSize{0};
		REX::StaticString<0x40> _name{REX::EMPTY_CHAR<char>};
		std::int32_t _pointerSize{0};
		std::int32_t _addressCount{0};
	};

	class Iddb::HeaderV5 final : public IHeader
	{
	public:
		HeaderV5() = default;
		~HeaderV5() noexcept override = default;

		HeaderV5(const HeaderV5&) = delete;
		HeaderV5(HeaderV5&&) noexcept = default;

		auto operator=(const HeaderV5&) -> HeaderV5& = delete;
		auto operator=(HeaderV5&&) noexcept -> HeaderV5& = default;

		[[nodiscard]]
		auto GetName() const noexcept -> std::string_view override
		{
			return _name.data();
		}

		[[nodiscard]]
		auto GetPointerSize() const noexcept -> std::size_t override
		{
			return static_cast<std::size_t>(_pointerSize);
		}

		[[nodiscard]]
		auto GetDataFormat() const noexcept -> std::int32_t
		{
			return _dataFormat;
		}

		[[nodiscard]]
		auto GetAddressCount() const noexcept -> std::size_t override
		{
			return static_cast<std::size_t>(_offsetCount);
		}

		[[nodiscard]]
		auto GetOffsetCount() const noexcept -> std::size_t
		{
			return static_cast<std::size_t>(_offsetCount);
		}

		[[nodiscard]]
		auto GetGameVersion() const noexcept -> REX::Version override
		{
			auto version = REX::Version();
			for (auto i = static_cast<decltype(version)::size_type>(0); i < version.size(); i++) {
				version[i] = static_cast<decltype(version)::value_type>(_gameVersion[i]);
			}

			return version;
		}

		auto LoadStream(REX::FileStream& a_stream) noexcept -> REX::SystemError override
		{
			const auto readGameVersionError = a_stream.Read(_gameVersion);
			if (readGameVersionError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return readGameVersionError;
			}

			const auto readNameError = a_stream.Read(_name);
			if (readNameError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return readNameError;
			}

			const auto readPointerSizeError = a_stream.Read(_pointerSize);
			if (readPointerSizeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return readPointerSizeError;
			}

			const auto readDataFormatError = a_stream.Read(_dataFormat);
			if (readDataFormatError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return readDataFormatError;
			}

			const auto readOffsetCountError = a_stream.Read(_offsetCount);
			if (readOffsetCountError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return readOffsetCountError;
			}

			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

	private:
		std::array<std::uint32_t, 4> _gameVersion{0};
		REX::StaticString<0x40> _name{REX::EMPTY_CHAR<char>};
		std::int32_t _pointerSize{0};
		std::int32_t _dataFormat{0};
		std::int32_t _offsetCount{0};
	};

	class Iddb::LoaderInfo final
	{
	public:
		std::vector<std::string> rootNames;
		std::flat_map<REX::Version, std::uint64_t> versionCrcMap;
		bool supportsStreaming{true};
	};

	class Iddb::IFormatInfo : public std::enable_shared_from_this<IFormatInfo>
	{
	public:
		class LoadContext final
		{
		public:
			std::filesystem::path path;
			REX::FileStream fileStream;
			REX::NotNull<std::shared_ptr<LoaderInfo>> loaderInfo;
			REX::NotNull<std::shared_ptr<REX::FileMemoryMap>> memoryMap;
		};

		IFormatInfo() noexcept = default;
		virtual ~IFormatInfo() noexcept = default;

		IFormatInfo(const IFormatInfo&) = delete;
		IFormatInfo(IFormatInfo&&) = delete;

		auto operator=(const IFormatInfo&) -> IFormatInfo& = delete;
		auto operator=(IFormatInfo&&) -> IFormatInfo& = delete;

		[[nodiscard]]
		virtual auto GetOffset(std::uintptr_t a_id) const noexcept -> std::optional<std::ptrdiff_t> = 0;

		virtual auto Load(LoadContext& a_context) -> std::optional<std::string> = 0;

	protected:
		static auto ValidateFile(
			const REX::NotNull<std::shared_ptr<LoaderInfo>>& a_loaderInfo,
			const REX::NotNull<std::shared_ptr<REX::FileMemoryMap>>& a_memoryMap) noexcept -> std::optional<std::string>
		{
			const auto moduleVersion = REL::Module::GetSingleton().GetVersion();

			const auto crcHashIt = a_loaderInfo->versionCrcMap.find(moduleVersion);
			if (crcHashIt == a_loaderInfo->versionCrcMap.end()) {
				return std::nullopt;
			}

			const auto expectedHash = crcHashIt->second;
			const auto actualHash = REX::HashCrc64(std::span<const std::byte>(*(a_memoryMap.get())));

			if (expectedHash != actualHash) [[unlikely]] {
				return REX::Format(
					"Failed to load Address Library.\n"
					"The database is not compatible with the current module version.\n"
					"Module Version: {}\n"
					"Expected Hash: 0x{:016X}\n"
					"Actual Hash: 0x{:016X}"sv,
					REL::Module::GetSingleton().GetVersion(),
					expectedHash,
					actualHash);
			}

			return std::nullopt;
		}
	};

	class Iddb::FormatInfoZero : public IFormatInfo
	{
	public:
		FormatInfoZero() noexcept = default;
		~FormatInfoZero() noexcept override = default;

		FormatInfoZero(const FormatInfoZero&) = delete;
		FormatInfoZero(FormatInfoZero&&) = delete;

		auto operator=(const FormatInfoZero&) -> FormatInfoZero& = delete;
		auto operator=(FormatInfoZero&&) -> FormatInfoZero& = delete;

		[[nodiscard]]
		auto GetOffset(std::uintptr_t a_id) const noexcept -> std::optional<std::ptrdiff_t> override
		{
			if (_mapping.empty()) {
				return std::nullopt;
			}

			const auto mappingElement = Mapping{.id = a_id, .offset = 0};

			const auto mappingIt = std::ranges::lower_bound(
				_mapping,
				mappingElement,
				[](const Mapping& a_lhs, const Mapping& a_rhs) noexcept -> bool {
					return a_lhs.id < a_rhs.id;
				});

			if (mappingIt == _mapping.end() || mappingIt->id != a_id) {
				return std::nullopt;
			}

			return mappingIt->offset;
		}

		auto Load(LoadContext& a_context) -> std::optional<std::string> override
		{
			const auto mapName = GetMemoryMapName(REL::Module::GetSingleton().GetVersion());

			const auto createError =
				a_context.memoryMap->Create(a_context.path, mapName, REX::FileMemoryMap::Options::Read);
			if (createError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return REX::Format(
					"Failed to load Address Library.\n"
					"The database memory map could not be created.\n"
					"File Path: \"{}\"\n"
					"System Error (0x{:08X}): {}"sv,
					a_context.path.generic_string(),
					createError.value(),
					createError.message());
			}

			auto validateError = ValidateFile(a_context.loaderInfo, a_context.memoryMap);
			if (validateError.has_value()) [[unlikely]] {
				return validateError;
			}

			_mapping = {
				reinterpret_cast<Mapping*>(a_context.memoryMap->data() + sizeof(std::uintptr_t)),
				*reinterpret_cast<std::uintptr_t*>(a_context.memoryMap->data())
			};

			return std::nullopt;
		}

	protected:
		std::span<Mapping> _mapping;
	};

	class Iddb::FormatInfoOne final : public FormatInfoZero
	{
	public:
		FormatInfoOne() noexcept = default;
		~FormatInfoOne() noexcept override = default;

		FormatInfoOne(const FormatInfoOne&) = delete;
		FormatInfoOne(FormatInfoOne&&) = delete;

		auto operator=(const FormatInfoOne&) -> FormatInfoOne& = delete;
		auto operator=(FormatInfoOne&&) -> FormatInfoOne& = delete;
	};

	class Iddb::FormatInfoTwo final : public FormatInfoZero
	{
	public:
		FormatInfoTwo() noexcept = default;
		~FormatInfoTwo() noexcept override = default;

		FormatInfoTwo(const FormatInfoTwo&) = delete;
		FormatInfoTwo(FormatInfoTwo&&) = delete;

		auto operator=(const FormatInfoTwo&) -> FormatInfoTwo& = delete;
		auto operator=(FormatInfoTwo&&) -> FormatInfoTwo& = delete;

		auto Load(LoadContext& a_context) -> std::optional<std::string> override
		{
			auto header = HeaderV2();

			const auto loadError = header.LoadStream(a_context.fileStream);
			if (loadError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return REX::Format(
					"Failed to load Address Library.\n"
					"The database file could not be loaded.\n"
					"File Path: \"{}\"\n"
					"System Error (0x{:08X}): {}"sv,
					a_context.path.generic_string(),
					loadError.value(),
					loadError.message());
			}

			if (header.GetGameVersion() != REL::Module::GetSingleton().GetVersion()) [[unlikely]] {
				return REX::Format(
					"Failed to load Address Library.\n"
					"The database is not compatible with the current module version.\n"
					"File Path: \"{}\"\n"
					"Expected Version: {}\n"
					"Actual Version: {}"sv,
					a_context.path.generic_string(),
					REL::Module::GetSingleton().GetVersion(),
					header.GetGameVersion());
			}

			const auto mapName = GetMemoryMapName(REL::Module::GetSingleton().GetVersion());
			const auto byteSize = header.GetAddressCount() * sizeof(Mapping);

			if (!a_context.memoryMap->Create(mapName, REX::FileMemoryMap::Options::ReadWrite, byteSize)) [[unlikely]] {
				const auto currentError = REX::GetCurrentSystemError();
				return REX::Format(
					"Failed to load Address Library.\n"
					"The database memory map could not be created.\n"
					"File Path: \"{}\"\n"
					"System Error (0x{:08X}): {}"sv,
					a_context.path.generic_string(),
					currentError.value(),
					currentError.message());
			}

			auto validateError = ValidateFile(a_context.loaderInfo, a_context.memoryMap);
			if (validateError.has_value()) [[unlikely]] {
				return validateError;
			}

			_mapping = {reinterpret_cast<Mapping*>(a_context.memoryMap->data()), header.GetAddressCount()};

			if (!a_context.memoryMap->IsOwner()) {
				return std::nullopt;
			}

			const auto unpackError = UnpackFile(a_context.fileStream, header);
			if (unpackError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return REX::Format(
					"Failed to load Address Library.\n"
					"The database file could not be unpacked.\n"
					"File Path: \"{}\"\n"
					"System Error (0x{:08X}): {}"sv,
					a_context.path.generic_string(),
					unpackError.value(),
					unpackError.message());
			}

			std::sort(
				std::execution::par_unseq,
				_mapping.begin(),
				_mapping.end(),
				[](const Mapping& a_lhs, const Mapping& a_rhs) noexcept -> bool {
					return a_lhs.id < a_rhs.id;
				});

			return std::nullopt;
		}

	private:
		auto UnpackFile(REX::FileStream& a_stream, const HeaderV2& a_header) -> REX::SystemError
		{
			auto type = static_cast<std::uint8_t>(0);
			auto currentId = static_cast<std::uintptr_t>(0);
			auto currentOffset = static_cast<std::ptrdiff_t>(0);
			auto previousId = static_cast<std::uintptr_t>(0);
			auto previousOffset = static_cast<std::ptrdiff_t>(0);

			for (auto& mapping : _mapping) {
				const auto readTypeError = a_stream.Read(type);
				if (readTypeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return readTypeError;
				}

				const auto lowPart = static_cast<std::uint8_t>(type & 0x0F);
				const auto highPart = static_cast<std::uint8_t>(type >> 4);

				const auto handlePart = []<typename T>(
											REX::FileStream& a_stream,
											T& a_outValue,
											T a_previousValue,
											std::uint8_t a_delta) -> REX::SystemError {
					switch (a_delta) {
						case 0: {
							const auto readValueError = a_stream.Read(a_outValue);
							if (readValueError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
								return readValueError;
							}

							break;
						}
						case 1: {
							a_outValue = a_previousValue + 1;
							break;
						}
						case 2: {
							const auto readDeltaError = a_stream.Read<std::uint8_t>();
							if (!readDeltaError.has_value()) [[unlikely]] {
								return readDeltaError.error();
							}

							a_outValue = a_previousValue + readDeltaError.value();
							break;
						}
						case 3: {
							const auto readDeltaError = a_stream.Read<std::uint8_t>();
							if (!readDeltaError.has_value()) [[unlikely]] {
								return readDeltaError.error();
							}

							a_outValue = a_previousValue - readDeltaError.value();
							break;
						}
						case 4: {
							const auto readDeltaError = a_stream.Read<std::uint16_t>();
							if (!readDeltaError.has_value()) [[unlikely]] {
								return readDeltaError.error();
							}

							a_outValue = a_previousValue + readDeltaError.value();
							break;
						}
						case 5: {
							const auto readDeltaError = a_stream.Read<std::uint16_t>();
							if (!readDeltaError.has_value()) [[unlikely]] {
								return readDeltaError.error();
							}

							a_outValue = a_previousValue - readDeltaError.value();
							break;
						}
						case 6: {
							const auto readValueError = a_stream.Read<std::uint16_t>();
							if (!readValueError.has_value()) [[unlikely]] {
								return readValueError.error();
							}

							a_outValue = readValueError.value();
							break;
						}
						case 7: {
							const auto readValueError = a_stream.Read<std::uint32_t>();
							if (!readValueError.has_value()) [[unlikely]] {
								return readValueError.error();
							}

							a_outValue = readValueError.value();
							break;
						}
						[[unlikely]]
						default: {
							break;
						}
					}

					return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
				};

				const auto lowPartError = handlePart(a_stream, currentId, previousId, lowPart);
				if (lowPartError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return lowPartError;
				}

				const auto tempValue = (highPart & 8) != 0 ?
										   (previousOffset / static_cast<std::ptrdiff_t>(a_header.GetPointerSize())) :
										   previousOffset;

				const auto highPartError = handlePart(a_stream, currentOffset, tempValue, highPart & 7);
				if (highPartError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return highPartError;
				}

				if ((highPart & 8) != 0) {
					currentOffset *= static_cast<std::ptrdiff_t>(a_header.GetPointerSize());
				}

				mapping = {.id = currentId, .offset = currentOffset};
				previousOffset = currentOffset;
				previousId = currentId;
			}

			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}
	};

	class Iddb::FormatInfoFive final : public IFormatInfo
	{
	public:
		FormatInfoFive() noexcept = default;
		~FormatInfoFive() noexcept override = default;

		FormatInfoFive(const FormatInfoFive&) = delete;
		FormatInfoFive(FormatInfoFive&&) = delete;

		auto operator=(const FormatInfoFive&) -> FormatInfoFive& = delete;
		auto operator=(FormatInfoFive&&) -> FormatInfoFive& = delete;

		[[nodiscard]]
		auto GetOffset(std::uintptr_t a_id) const noexcept -> std::optional<std::ptrdiff_t> override
		{
			if (_mapping.empty()) {
				return std::nullopt;
			}

			const auto offset = static_cast<std::ptrdiff_t>(_mapping[a_id]);
			if (offset == 0) {
				return std::nullopt;
			}

			return offset;
		}

		auto Load(LoadContext& a_context) -> std::optional<std::string> override
		{
			auto header = HeaderV5();

			const auto loadError = header.LoadStream(a_context.fileStream);
			if (loadError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return REX::Format(
					"Failed to load Address Library.\n"
					"The database file could not be loaded.\n"
					"File Path: \"{}\"\n"
					"System Error (0x{:08X}): {}"sv,
					a_context.path.generic_string(),
					loadError.value(),
					loadError.message());
			}

			if (header.GetGameVersion() != REL::Module::GetSingleton().GetVersion()) [[unlikely]] {
				return REX::Format(
					"Failed to load Address Library.\n"
					"The database is not compatible with the current module version.\n"
					"File Path: \"{}\"\n"
					"Expected Version: {}\n"
					"Actual Version: {}"sv,
					a_context.path.generic_string(),
					REL::Module::GetSingleton().GetVersion(),
					header.GetGameVersion());
			}

			const auto mapName = GetMemoryMapName(REL::Module::GetSingleton().GetVersion());

			const auto createError =
				a_context.memoryMap->Create(a_context.path, mapName, REX::FileMemoryMap::Options::Read);
			if (createError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return REX::Format(
					"Failed to load Address Library.\n"
					"The database memory map could not be created.\n"
					"File Path: \"{}\"\n"
					"System Error (0x{:08X}): {}"sv,
					a_context.path.generic_string(),
					createError.value(),
					createError.message());
			}

			auto validateError = ValidateFile(a_context.loaderInfo, a_context.memoryMap);
			if (validateError) {
				return validateError;
			}

			_mapping = {
				reinterpret_cast<std::uint32_t*>(a_context.memoryMap->data() + sizeof(HeaderV5)),
				header.GetOffsetCount()
			};

			return std::nullopt;
		}

	private:
		std::span<std::uint32_t> _mapping;
	};

#if (COMMONLIB_RUNTIME_VR == 1)
	class Iddb::FormatInfoVR final : public IFormatInfo
	{
	public:
		FormatInfoVR() noexcept = default;
		~FormatInfoVR() noexcept override = default;

		FormatInfoVR(const FormatInfoVR&) = delete;
		FormatInfoVR(FormatInfoVR&&) = delete;

		auto operator=(const FormatInfoVR&) -> FormatInfoVR& = delete;
		auto operator=(FormatInfoVR&&) -> FormatInfoVR& = delete;

		[[nodiscard]]
		auto GetOffset(std::uintptr_t a_id) const noexcept -> std::optional<std::ptrdiff_t> override
		{
			if (_mapping.empty()) {
				return std::nullopt;
			}

			const auto mappingElement = Mapping{.id = a_id, .offset = 0};

			const auto mappingIt = std::ranges::lower_bound(
				_mapping,
				mappingElement,
				[](const Mapping& a_lhs, const Mapping& a_rhs) noexcept -> bool {
					return a_lhs.id < a_rhs.id;
				});

			if (mappingIt == _mapping.end() || mappingIt->id != a_id) {
				return std::nullopt;
			}

			return mappingIt->offset;
		}

		auto Load(LoadContext& a_context) -> std::optional<std::string> override
		{
			const auto fileContent = a_context.fileStream.ReadText();
			if (!fileContent.has_value()) [[unlikely]] {
				return REX::Format(
					"Failed to load Address Library VR.\n"
					"The database file could not be read.\n"
					"File Path: \"{}\"\n"
					"System Error (0x{:08X}): {}"sv,
					a_context.path.generic_string(),
					fileContent.error().value(),
					fileContent.error().message());
			}

			class Row
			{
			public:
				std::size_t number;
				std::string text;
			};

			constexpr auto OPTIONS = glz::opts_csv{.use_headers = false};

			auto rows = std::vector<Row>();

			const auto readError = glz::read<OPTIONS>(rows, fileContent.value());
			if (readError.ec != glz::error_code::none) [[unlikely]] {
				return REX::Format(
					"Failed to load Address Library VR.\n"
					"The database contains invalid CSV data.\n"
					"File Path: \"{}\"\n"
					"CSV Error: {}"sv,
					a_context.path.generic_string(),
					glz::format_error(readError, fileContent.value()));
			}

			if (rows.empty()) [[unlikely]] {
				return REX::Format(
					"Failed to load Address Library VR.\n"
					"The database contains no entries."sv);
			}

			const auto& metadata = rows.front();
			const auto addressCount = metadata.number;
			const auto& formatVersion = metadata.text;
			const auto actualEntryCount = rows.size() - 1;

			if (actualEntryCount > addressCount) [[unlikely]] {
				return REX::Format(
					"Failed to load Address Library VR.\n"
					"The database contains more entries than expected.\n"
					"Format Version: {}\n"
					"Expected Entries: {}\n"
					"Actual Entries: {}"sv,
					formatVersion,
					addressCount,
					actualEntryCount);
			}

			if (actualEntryCount < addressCount) [[unlikely]] {
				return REX::Format(
					"Failed to load Address Library VR.\n"
					"The database contains fewer entries than expected.\n"
					"Format Version: {}\n"
					"Expected Entries: {}\n"
					"Actual Entries: {}"sv,
					formatVersion,
					addressCount,
					actualEntryCount);
			}

			for (auto index = static_cast<std::size_t>(1); index < rows.size(); index++) {
				const auto& row = rows[index];

				const auto id = static_cast<std::uintptr_t>(row.number);
				const auto& offset = row.text;

				const auto offsetNumber = REX::FromString<std::ptrdiff_t>(offset, REX::IntFormat::Hexadecimal);

				if (!offsetNumber.has_value()) [[unlikely]] {
					return REX::Format(
						"Failed to load Address Library VR.\n"
						"The database contains an invalid offset entry.\n"
						"Format Version: {}\n"
						"Entry Index: {}\n"
						"Entry ID: {}\n"
						"Entry Offset: {}"sv,
						formatVersion,
						index,
						id,
						offset);
				}

				_mapping.emplace_back(id, offsetNumber.value());
			}

			std::sort(
				std::execution::par_unseq,
				_mapping.begin(),
				_mapping.end(),
				[](const Mapping& a_lhs, const Mapping& a_rhs) noexcept -> bool {
					return a_lhs.id < a_rhs.id;
				});

			return std::nullopt;
		}

	private:
		std::vector<Mapping> _mapping;
	};
#endif
}

namespace REL
{
	Iddb::Iddb() :
		// clang-format off
		_loaderInfoMap{
			{
				"SKSE"s,
				std::make_shared<LoaderInfo>(LoaderInfo{
					.rootNames = { "versionlib"s, "version"s },
					.versionCrcMap = {
						std::make_pair(REX::Version(1, 5, 97, 0), static_cast<std::uint64_t>(0x7ED3'2289'9C89'99D7)),
						std::make_pair(REX::Version(1, 6, 1'170, 0), static_cast<std::uint64_t>(0x0A6C'2093'652D'2622)),
						std::make_pair(REX::Version(1, 6, 1'179, 0), static_cast<std::uint64_t>(0xE2D6'55E8'97B0'D016)),
						std::make_pair(REX::Version(1, 7, 104, 0), static_cast<std::uint64_t>(0x16A8'8691'1F6C'0C84))
					}
				})
			},
			{
				"F4SE"s,
				std::make_shared<LoaderInfo>(LoaderInfo{
					.rootNames = { "version"s },
					.versionCrcMap = {
						std::make_pair(REX::Version(1, 10, 163, 0), static_cast<std::uint64_t>(0x9FAC'C538'CC34'22A1)),
						std::make_pair(REX::Version(1, 10, 984, 0), static_cast<std::uint64_t>(0x7E45'86F6'7B48'4062)),
						std::make_pair(REX::Version(1, 11, 240, 0), static_cast<std::uint64_t>(0xC205'D6B0'6926'6A04))
					},
					.supportsStreaming = false
				})
			},
			{
				"SFSE"s,
				std::make_shared<LoaderInfo>(LoaderInfo{
					.rootNames = { "versionlib"s },
					.versionCrcMap = {
						std::make_pair(REX::Version(1, 16, 244, 0), static_cast<std::uint64_t>(0x4675'C162'D17D'E844))
					}
				})
			},
			{
				"OBSE"s,
				std::make_shared<LoaderInfo>(LoaderInfo{
					.rootNames = { "versionlib"s },
					.versionCrcMap = {
						std::make_pair(REX::Version(1, 512, 105, 0), static_cast<std::uint64_t>(0x6FF4'9281'899E'8B89))
					}
				})
			}
		},
		// clang-format on
		_formatInfoMap{
#if (COMMONLIB_RUNTIME_VR == 1)
			std::make_pair(FormatVersion::VR, std::make_shared<FormatInfoVR>()),
#endif
			std::make_pair(FormatVersion::Zero, std::make_shared<FormatInfoZero>()),
			std::make_pair(FormatVersion::One, std::make_shared<FormatInfoOne>()),
			std::make_pair(FormatVersion::Two, std::make_shared<FormatInfoTwo>()),
			std::make_pair(FormatVersion::Five, std::make_shared<FormatInfoFive>())
		},
		_memoryMap(std::make_shared<REX::FileMemoryMap>())
	{
	}

	Iddb::~Iddb() noexcept = default;

	auto Iddb::GetMemoryMapName(REX::Version a_version) -> std::string
	{
		return REX::Format("COMMONLIB_IDDB_OFFSETS_{}"sv, a_version.ToString('_'));
	}

	auto Iddb::GetOffset(std::uintptr_t a_id) const noexcept -> std::ptrdiff_t
	{
		if (!_currentFormatInfo) [[unlikely]] {
			REX::Fail(
				"Failed to find the offset for an Address Library ID.\n"
				"The database has not been initialized.\n"
				"Requested ID: {}\n"
				"Module Version: {}"sv,
				a_id,
				REL::Module::GetSingleton().GetVersion());
		}

		const auto offset = _currentFormatInfo->GetOffset(a_id);
		if (!offset.has_value()) [[unlikely]] {
			REX::Fail(
				"Failed to find the offset for an Address Library ID.\n"
				"The ID is not present in the database.\n"
				"Requested ID: {}\n"
				"Module Version: {}"sv,
				a_id,
				REL::Module::GetSingleton().GetVersion());
		}

		return offset.value();
	}

	void Iddb::Setup()
	{
		const auto moduleFilePath = REX::GetModuleFilePath(REX::GetCurrentModuleHandle());
		if (!moduleFilePath.has_value()) [[unlikely]] {
			REX::Fail(
				"Failed to load Address Library.\n"
				"The module file path could not be retrieved.\n"
				"System Error (0x{:08X}): {}"sv,
				moduleFilePath.error().value(),
				moduleFilePath.error().message());
		}

		const auto loaderName = moduleFilePath->parent_path().parent_path().filename().generic_string();

		const auto loaderIt = _loaderInfoMap.find(REX::ToUpper(std::string_view(loaderName)));
		if (loaderIt == _loaderInfoMap.end()) [[unlikely]] {
			REX::Fail(
				"Failed to load Address Library.\n"
				"The database loader is not supported in this build.\n"
				"Loader Name: \"{}\""sv,
				loaderName);
		}

		_currentLoaderInfo = loaderIt->second.get();

		const auto moduleVersion = REL::Module::GetSingleton().GetVersion().ToString('-');
		const auto moduleFileExtension = REL::Module::GetSingleton().GetRuntime().GetFileExtension();

		for (const auto& loaderRootName : _currentLoaderInfo->rootNames) {
			const auto fullLoaderName = REX::Format("{}-{}{}"sv, loaderRootName, moduleVersion, moduleFileExtension);
			auto fullLoaderPath = moduleFilePath->parent_path() / fullLoaderName;

			auto isFileError = REX::SystemError();
			if (!std::filesystem::is_regular_file(fullLoaderPath, isFileError)) {
				continue;
			}

			_filePath = std::move(fullLoaderPath);
			break;
		}

		if (_filePath.empty()) [[unlikely]] {
			REX::Fail(
				"Failed to load Address Library.\n"
				"The database file could not be found.\n"
				"Loader Name: \"{}\"\n"
				"Module Version: {}"sv,
				loaderName,
				moduleVersion);
		}

		auto fileStream = REX::FileStream::Open(
			_filePath,
			REX::FileMode::Open,
			REX::FileAccess::Read,
			REX::FileShare::Read,
			REX::FileOptions::SequentialScan);
		if (!fileStream.has_value()) [[unlikely]] {
			REX::Fail(
				"Failed to load Address Library.\n"
				"The database file could not be opened for reading.\n"
				"File Path: \"{}\"\n"
				"System Error (0x{:08X}): {}"sv,
				_filePath.generic_string(),
				fileStream.error().value(),
				fileStream.error().message());
		}

		auto formatVersion = FormatVersion::None;

		if (moduleFileExtension == REL::DEFAULT_RUNTIME_FILE_EXTENSION_VR)
#if (COMMONLIB_RUNTIME_VR == 0)
			[[unlikely]]
#endif
		{
#if (COMMONLIB_RUNTIME_VR == 1)
			formatVersion = FormatVersion::VR;
#else
			REX::Fail(
				"Failed to load Address Library VR.\n"
				"The VR runtime is not supported in this build."sv);
#endif
		}
		else if (!_currentLoaderInfo->supportsStreaming) {
			formatVersion = FormatVersion::Zero;
		}
		else {
			const auto formatVersionError = fileStream->Read(formatVersion);
			if (formatVersionError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				REX::Fail(
					"Failed to load Address Library.\n"
					"The database format version could not be read.\n"
					"File Path: \"{}\"\n"
					"System Error (0x{:08X}): {}"sv,
					_filePath.generic_string(),
					formatVersionError.value(),
					formatVersionError.message());
			}

			if (formatVersion <= FormatVersion::_Min || formatVersion > FormatVersion::_Max) [[unlikely]] {
				REX::Fail(
					"Failed to load Address Library.\n"
					"The database format version is not supported in this build.\n"
					"Format Version: {}"sv,
					std::to_underlying(formatVersion));
			}
		}

		const auto formatIt = _formatInfoMap.find(formatVersion);
		if (formatIt == _formatInfoMap.end()) [[unlikely]] {
			REX::Fail(
				"Failed to load Address Library.\n"
				"The database format version is not supported in this build.\n"
				"Format Version: {}"sv,
				std::to_underlying(formatVersion));
		}

		_currentFormatInfo = formatIt->second.get();

		auto loadContext = IFormatInfo::LoadContext{
			.path = _filePath,
			.fileStream = std::move(fileStream).value(),
			.loaderInfo = _currentLoaderInfo,
			.memoryMap = _memoryMap
		};

		const auto loadError = _currentFormatInfo->Load(loadContext);
		if (loadError.has_value()) [[unlikely]] {
			REX::Fail(loadError.value());
		}
	}
}
