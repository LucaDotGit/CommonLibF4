#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTBTree.hpp"
#include "RE/S/SettingCollection.hpp"

namespace RE::Impl
{
	struct SettingCollectionMapCompare
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(const RE::BSFixedString& a_lhs, const RE::BSFixedString& a_rhs) const noexcept -> bool
		{
			return a_lhs.data() < a_rhs.data();
		}
	};
}

namespace RE
{
	class Setting;

	template <class T>
	class __declspec(novtable) SettingCollectionMap : public SettingCollection<T> // 0x00
	{
	public:
		~SettingCollectionMap() override = default; // 0x00

		[[nodiscard]]
		auto GetSetting(std::string_view a_name) const noexcept -> T*
		{
			const auto settingIt = settings.find(BSFixedString(a_name));
			if (settingIt == settings.end()) {
				return nullptr;
			}

			return settingIt->second;
		}

		[[nodiscard]]
		auto GetSetting(const BSFixedString& a_name) const noexcept -> T*
		{
			const auto settingIt = settings.find(a_name);
			if (settingIt == settings.end()) {
				return nullptr;
			}

			return settingIt->second;
		}

		// members
		BSTBTree<BSFixedString, T*, Impl::SettingCollectionMapCompare> settings; // 0x118
	};

	static_assert(sizeof(SettingCollectionMap<Setting>) == 0x138);
}
