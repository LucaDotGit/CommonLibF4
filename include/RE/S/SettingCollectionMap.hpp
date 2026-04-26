#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTBTree.hpp"
#include "RE/S/SettingCollection.hpp"

namespace RE::Impl
{
	struct SettingCollectionMapCompare
	{
	public:
		[[nodiscard]] constexpr bool operator()(const RE::BSFixedString& a_lhs, const RE::BSFixedString& a_rhs) const noexcept
		{
			return a_lhs.data() < a_rhs.data();
		}
	};
}

namespace RE
{
	template <class T>
	class __declspec(novtable) SettingCollectionMap
		: public SettingCollection<T> // 00
	{
	public:
		~SettingCollectionMap() override = default; // 00

		[[nodiscard]] T* GetSetting(std::string_view a_name) const noexcept
		{
			const auto settingIt = settings.find(BSFixedString(a_name));
			if (settingIt == settings.end()) {
				return nullptr;
			}

			return settingIt->second;
		}

		[[nodiscard]] T* GetSetting(const BSFixedString& a_name) const noexcept
		{
			const auto settingIt = settings.find(a_name);
			if (settingIt == settings.end()) {
				return nullptr;
			}

			return settingIt->second;
		}

		// members
		BSTBTree<BSFixedString, T*, Impl::SettingCollectionMapCompare> settings; // 118
	};

	extern template class SettingCollectionMap<Setting>;
}
