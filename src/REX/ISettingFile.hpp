#pragma once

#include "REX/Error.hpp"
#include "REX/ISettingList.hpp"

namespace REX
{
	template <class Entry>
	class ISettingFile : public ISettingList<Entry>
	{
	public:
		using entry_type = Entry;

		ISettingFile() noexcept = default;
		~ISettingFile() noexcept override = default;

		ISettingFile(const ISettingFile&) = delete;
		ISettingFile(ISettingFile&&) noexcept = default;

		auto operator=(const ISettingFile&) -> ISettingFile& = delete;
		auto operator=(ISettingFile&&) noexcept -> ISettingFile& = default;

		[[nodiscard]]
		virtual auto GetFilePath() const noexcept -> const std::filesystem::path& = 0;

		virtual auto Load() -> REX::SystemError = 0;
		virtual auto Save() const -> REX::SystemError = 0;
	};
}
