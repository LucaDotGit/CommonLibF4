#pragma once

#if __has_include(<glaze/glaze.hpp>)

#include "REX/Error.hpp"
#include "REX/Glaze/Utility.hpp"
#include "REX/SettingList.hpp"

namespace REX::Glaze
{
	template <glz::num_mode NumberMode, template <class> class MapType = REX::Glaze::MapType>
	class SettingGroup final : public REX::SettingList<glz::generic_json<NumberMode, MapType>>
	{
	private:
		using super = REX::SettingList<glz::generic_json<NumberMode, MapType>>;

	public:
		using entry_type = super::entry_type;

		explicit SettingGroup(std::string a_key) noexcept :
			_key(std::move(a_key))
		{
		}

		~SettingGroup() noexcept override = default;

		SettingGroup(const SettingGroup&) = delete;
		SettingGroup(SettingGroup&&) noexcept = default;

		auto operator=(const SettingGroup&) -> SettingGroup& = delete;
		auto operator=(SettingGroup&&) noexcept -> SettingGroup& = default;

		[[nodiscard]]
		auto GetKey() const noexcept -> std::string_view override
		{
			return _key;
		}

		auto LoadEntry(const entry_type& a_parent) -> REX::SystemError
		{
			if (!a_parent.is_object()) [[unlikely]] {
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			const auto& parentObject = a_parent.get_object();

			const auto groupIt = parentObject.find(_key);
			if (groupIt == parentObject.end()) [[unlikely]] {
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			for (auto&& [_, value] : this->_settings) {
				const auto loadError = value->LoadEntry(groupIt->second);
				if (loadError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return loadError;
				}
			}

			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		auto SaveEntry(entry_type& a_parent) const -> REX::SystemError
		{
			if (!a_parent.is_object()) [[unlikely]] {
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			auto& currentObject = a_parent.get_object()[_key];

			for (auto&& [_, value] : this->_settings) {
				const auto saveError = value->SaveEntry(currentObject);
				if (saveError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return saveError;
				}
			}

			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

	private:
		std::string _key;
	};
}

#endif
