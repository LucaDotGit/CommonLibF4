#pragma once

#if __has_include(<glaze/glaze.hpp>)

#include "REX/Error.hpp"
#include "REX/Glaze/Utility.hpp"
#include "REX/SettingList.hpp"

namespace REX::Glaze
{
	template <glz::num_mode NumberMode, template <class> class MapType = REX::Glaze::MapType>
	class SettingList final : public REX::SettingList<glz::generic_json<NumberMode, MapType>>
	{
	private:
		using super = REX::SettingList<glz::generic_json<NumberMode, MapType>>;

	public:
		using entry_type = super::entry_type;

		SettingList() noexcept = default;
		~SettingList() noexcept override = default;

		SettingList(const SettingList&) = delete;
		SettingList(SettingList&&) noexcept = default;

		auto operator=(const SettingList&) -> SettingList& = delete;
		auto operator=(SettingList&&) noexcept -> SettingList& = default;

		[[nodiscard]]
		auto GetKey() const noexcept -> std::string_view override
		{
			return {};
		}

		auto LoadEntry(const entry_type& a_parent) -> REX::SystemError override
		{
			if (!a_parent.is_object()) [[unlikely]] {
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			for (auto&& [_, value] : this->_settings) {
				const auto loadError = value->LoadEntry(a_parent);
				if (loadError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return loadError;
				}
			}

			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		auto SaveEntry(entry_type& a_parent) const -> REX::SystemError override
		{
			if (!a_parent.is_object()) [[unlikely]] {
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			for (auto&& [_, value] : this->_settings) {
				const auto saveError = value->SaveEntry(a_parent);
				if (saveError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return saveError;
				}
			}

			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}
	};
}

#endif
