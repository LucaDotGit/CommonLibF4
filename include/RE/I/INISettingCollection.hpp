#pragma once

#include "RE/S/Setting.hpp"
#include "RE/S/SettingCollectionList.hpp"

namespace RE
{
	class __declspec(novtable) INISettingCollection
		: public SettingCollectionList<Setting> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::INISettingCollection };
		inline static constexpr auto VTABLE{ VTABLE::INISettingCollection };

		~INISettingCollection() override; // 00

		// override (SettingCollection<Setting>)
		void Add(Setting* a_setting) override;			// 01
		void Remove(Setting* a_setting) override;		// 02
		bool WriteSetting(Setting& a_setting) override; // 03
		bool ReadSetting(Setting& a_setting) override;	// 04
		bool Open(bool a_write) override;				// 05
		bool Close() override;							// 06
		bool ReadSettingsFromProfile() override;		// 07
		bool WriteSettings() override;					// 08
		bool ReadSettings() override;					// 09

		[[nodiscard]] static INISettingCollection* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<INISettingCollection**>{ ID::INISettingCollection::Singleton };
			return *SINGLETON;
		}
	};
	static_assert(sizeof(INISettingCollection) == 0x128);
}
