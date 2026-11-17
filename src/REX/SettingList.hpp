#pragma once

#include "REX/ISetting.hpp"
#include "REX/ISettingList.hpp"
#include "REX/NotNull.hpp"

namespace REX
{
	template <class Entry>
	class SettingList : public ISettingList<Entry>
	{
	public:
		using entry_type = Entry;

		SettingList() noexcept = default;
		~SettingList() noexcept override = default;

		SettingList(const SettingList&) = delete;
		SettingList(SettingList&&) noexcept = default;

		auto operator=(const SettingList&) -> SettingList& = delete;
		auto operator=(SettingList&&) noexcept -> SettingList& = default;

		[[nodiscard]]
		auto Contains(std::string_view a_key) const noexcept -> bool override
		{
			return _settings.contains(a_key);
		}

		[[nodiscard]]
		auto GetValue(std::string_view a_key) const noexcept -> std::shared_ptr<ISetting<entry_type>> override
		{
			const auto settingIt = _settings.find(a_key);
			if (settingIt == _settings.end()) {
				return nullptr;
			}

			return settingIt->second.get();
		}

		auto SetValue(REX::NotNull<std::shared_ptr<ISetting<entry_type>>> a_setting) -> bool override
		{
			_settings.insert_or_assign(a_setting->GetKey(), std::move(a_setting));
			return true;
		}

		auto Add(REX::NotNull<std::shared_ptr<ISetting<entry_type>>> a_setting) -> bool override
		{
			const auto&& [_, hasInserted] = _settings.emplace(a_setting->GetKey(), std::move(a_setting));
			return hasInserted;
		}

		void AddRange(std::span<const REX::NotNull<std::shared_ptr<ISetting<entry_type>>>> a_settings) override
		{
			for (const auto& setting : a_settings) {
				_settings.emplace(setting->GetKey(), setting);
			}
		}

		void AddRange(
			std::initializer_list<const REX::NotNull<std::shared_ptr<ISetting<entry_type>>>> a_settings) override
		{
			AddRange(std::span(a_settings));
		}

		auto Remove(std::string_view a_key) noexcept -> bool override
		{
			const auto settingIt = _settings.find(a_key);
			if (settingIt == _settings.end()) {
				return false;
			}

			_settings.erase(settingIt);
			return true;
		}

		void Clear() noexcept override
		{
			_settings.clear();
		}

	protected:
		std::map<std::string_view, REX::NotNull<std::shared_ptr<ISetting<entry_type>>>> _settings;
	};
}
