#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/S/SettingCollection.hpp"

namespace RE
{
	template <class T>
	class __declspec(novtable) SettingCollectionList
		: public SettingCollection<T> // 00
	{
	public:
		~SettingCollectionList() override = default; // 00

		[[nodiscard]] T* GetSetting(std::string_view a_name) const noexcept
		{
			for (auto* setting : settings) {
				if (REX::EqualsIgnoreCase(std::string_view(setting->GetKey()), a_name)) {
					return setting;
				}
			}

			return nullptr;
		}

		// members
		BSSimpleList<T*> settings; // 118
	};

	extern template class SettingCollectionList<Setting>;
}
