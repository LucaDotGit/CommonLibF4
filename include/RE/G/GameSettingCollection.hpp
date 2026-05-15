#pragma once

#include "RE/S/Setting.hpp"
#include "RE/S/SettingCollectionMap.hpp"

namespace RE
{
	class __declspec(novtable) GameSettingCollection
		: public SettingCollectionMap<Setting> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameSettingCollection };
		inline static constexpr auto VTABLE{ VTABLE::GameSettingCollection };

		~GameSettingCollection() override; // 00

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

		[[nodiscard]] static GameSettingCollection* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<GameSettingCollection**>{ ID::GameSettingCollection::Singleton };
			return *SINGLETON;
		}

		static void InitCollection()
		{
			using FuncType = decltype(&GameSettingCollection::InitCollection);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::GameSettingCollection::InitCollection };
			std::invoke(FUNC);
		}
	};
	static_assert(sizeof(GameSettingCollection) == 0x138);
}
