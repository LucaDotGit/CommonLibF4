#pragma once

#include "RE/S/Setting.hpp"

namespace RE
{
	template <class T>
	class __declspec(novtable) SettingT
		: public Setting // 00
	{
	public:
	};

	class GameSettingCollection;
	class INIPrefSettingCollection;
	class INISettingCollection;
	class LipSynchroSettingCollection; // unused
	class RegSettingCollection;		   // unused

	extern template class SettingT<GameSettingCollection>;
	extern template class SettingT<INIPrefSettingCollection>;
	extern template class SettingT<INISettingCollection>;
	extern template class SettingT<LipSynchroSettingCollection>;
	extern template class SettingT<RegSettingCollection>;

	using GameSetting = SettingT<GameSettingCollection>;
	using INIPrefSetting = SettingT<INIPrefSettingCollection>;
	using INISetting = SettingT<INISettingCollection>;
	using LipSynchroSetting = SettingT<LipSynchroSettingCollection>;
	using RegSetting = SettingT<RegSettingCollection>;
}
