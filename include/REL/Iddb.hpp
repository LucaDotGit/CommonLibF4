#pragma once

#include "REX/MemoryMap.hpp"
#include "REX/NotNull.hpp"
#include "REX/Singleton.hpp"
#include "REX/Version.hpp"

namespace REL
{
	class Iddb final
		: public REX::Singleton<Iddb>
	{
	public:
		Iddb();
		~Iddb() noexcept;

		Iddb(const Iddb&) = delete;
		Iddb(Iddb&&) = delete;

		Iddb& operator=(const Iddb&) = delete;
		Iddb& operator=(Iddb&&) = delete;

		[[nodiscard]] const std::filesystem::path& GetFilePath() const noexcept { return _filePath; }
		[[nodiscard]] std::ptrdiff_t GetOffset(std::uintptr_t a_id) const noexcept;

		void Init();

	private:
		enum class FormatVersion : std::int32_t;

		class Mapping;

		class Stream;
		class HeaderV2;
		class HeaderV5;

		class LoaderInfo;

		class IFormatInfo;
		class FormatInfoV0;
		class FormatInfoV1;
		class FormatInfoV2;
		class FormatInfoV5;
#if COMMONLIB_RUNTIME_VR == 1
		class FormatInfoVR;
#endif

		[[nodiscard]] static std::string GetMemoryMapName(REX::Version a_version);

		std::filesystem::path _filePath;
		std::unordered_map<std::string_view, REX::NotNull<std::shared_ptr<LoaderInfo>>> _loaderInfoMap;
		std::unordered_map<FormatVersion, REX::NotNull<std::shared_ptr<IFormatInfo>>> _formatInfoMap;
		std::shared_ptr<LoaderInfo> _currentLoaderInfo;
		std::shared_ptr<IFormatInfo> _currentFormatInfo;
		REX::NotNull<std::shared_ptr<REX::MemoryMap>> _memoryMap;
	};
}
