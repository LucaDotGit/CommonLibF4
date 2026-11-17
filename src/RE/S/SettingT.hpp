#pragma once

#include "RE/S/Setting.hpp"

namespace RE
{
	template <class T>
	class __declspec(novtable) SettingT : public Setting // 0x00
	{
	public:
	};

	class GameSettingCollection;
	class INIPrefSettingCollection;
	class INISettingCollection;
	class LipSynchroSettingCollection; // unused
	class RegSettingCollection;		   // unused

	using GameSetting = SettingT<GameSettingCollection>;
	static_assert(sizeof(GameSetting) == 0x18);

	using INIPrefSetting = SettingT<INIPrefSettingCollection>;
	static_assert(sizeof(INIPrefSetting) == 0x18);

	using INISetting = SettingT<INISettingCollection>;
	static_assert(sizeof(INISetting) == 0x18);

	using LipSynchroSetting = SettingT<LipSynchroSettingCollection>;
	static_assert(sizeof(LipSynchroSetting) == 0x18);

	using RegSetting = SettingT<RegSettingCollection>;
	static_assert(sizeof(RegSetting) == 0x18);
}
