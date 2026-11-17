#pragma once

#include "REX/ISetting.hpp"
#include "REX/NotNull.hpp"

namespace REX
{
	template <class Entry>
	class ISettingList : public ISetting<Entry>
	{
	public:
		using entry_type = Entry;

		ISettingList() noexcept = default;
		virtual ~ISettingList() noexcept = default;

		ISettingList(const ISettingList&) = delete;
		ISettingList(ISettingList&&) noexcept = default;

		auto operator=(const ISettingList&) -> ISettingList& = delete;
		auto operator=(ISettingList&&) noexcept -> ISettingList& = default;

		[[nodiscard]]
		virtual auto Contains(std::string_view a_key) const noexcept -> bool = 0;

		[[nodiscard]]
		virtual auto GetValue(std::string_view a_key) const noexcept -> std::shared_ptr<ISetting<entry_type>> = 0;

		virtual auto SetValue(REX::NotNull<std::shared_ptr<ISetting<entry_type>>> a_setting) -> bool = 0;

		virtual auto Add(REX::NotNull<std::shared_ptr<ISetting<entry_type>>> a_setting) -> bool = 0;
		virtual void AddRange(std::span<const REX::NotNull<std::shared_ptr<ISetting<entry_type>>>> a_settings) = 0;
		virtual void AddRange(
			std::initializer_list<const REX::NotNull<std::shared_ptr<ISetting<entry_type>>>> a_settings) = 0;

		virtual auto Remove(std::string_view a_key) noexcept -> bool = 0;
		virtual void Clear() noexcept = 0;
	};
}

namespace std
{
	template <class T>
		requires(std::derived_from<T, REX::ISettingList<typename T::entry_type>>)
	struct hash<T>
	{
	public:
		[[nodiscard]]
		auto operator()(const T& a_settingGroup) const noexcept -> std::size_t
		{
			return REX::Hash(a_settingGroup.GetKey());
		}
	};
}
