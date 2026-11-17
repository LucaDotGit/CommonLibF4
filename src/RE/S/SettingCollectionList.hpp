#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/S/SettingCollection.hpp"

namespace RE
{
	class Setting;

	template <class T>
	class __declspec(novtable) SettingCollectionList : public SettingCollection<T> // 0x00
	{
	public:
		~SettingCollectionList() override = default; // 0x00

		[[nodiscard]]
		auto GetSetting(std::string_view a_name) const noexcept -> T*
		{
			for (auto* setting : settings) {
				if (REX::EqualsIgnoreCase(std::string_view(setting->GetKey()), a_name)) {
					return setting;
				}
			}

			return nullptr;
		}

		// members
		BSSimpleList<T*> settings; // 0x118
	};

	static_assert(sizeof(SettingCollectionList<Setting>) == 0x128);
}
