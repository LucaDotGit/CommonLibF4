#pragma once

#include "REX/Comparison.hpp"
#include "REX/NotNull.hpp"
#include "REX/Singleton.hpp"

namespace REX
{
	class FileMemoryMap;
	class Version;
}

namespace REL
{
	class Iddb final : public REX::Singleton<Iddb>
	{
	public:
		Iddb();
		~Iddb() noexcept;

		Iddb(const Iddb&) = delete;
		Iddb(Iddb&&) = delete;

		auto operator=(const Iddb&) -> Iddb& = delete;
		auto operator=(Iddb&&) -> Iddb& = delete;

		[[nodiscard]]
		auto GetFilePath() const noexcept -> const std::filesystem::path&
		{
			return _filePath;
		}

		[[nodiscard]]
		auto GetOffset(std::uintptr_t a_id) const noexcept -> std::ptrdiff_t;

		void Setup();

	private:
		enum class FormatVersion : std::int32_t;

		class Mapping;

		class IHeader;
		class HeaderV2;
		class HeaderV5;

		class LoaderInfo;

		class IFormatInfo;
		class FormatInfoZero;
		class FormatInfoOne;
		class FormatInfoTwo;
		class FormatInfoFive;
#if (COMMONLIB_RUNTIME_VR == 1)
		class FormatInfoVR;
#endif

		[[nodiscard]]
		static auto GetMemoryMapName(REX::Version a_version) -> std::string;

		std::filesystem::path _filePath;
		std::flat_map<std::string, REX::NotNull<std::shared_ptr<LoaderInfo>>, REX::StringLess<char>> _loaderInfoMap;
		std::flat_map<FormatVersion, REX::NotNull<std::shared_ptr<IFormatInfo>>> _formatInfoMap;
		std::shared_ptr<LoaderInfo> _currentLoaderInfo;
		std::shared_ptr<IFormatInfo> _currentFormatInfo;
		REX::NotNull<std::shared_ptr<REX::FileMemoryMap>> _memoryMap;
	};
}
