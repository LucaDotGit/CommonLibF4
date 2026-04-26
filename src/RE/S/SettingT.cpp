#include "RE/S/SettingT.hpp"

namespace RE
{
	template class SettingT<GameSettingCollection>;
	static_assert(sizeof(SettingT<GameSettingCollection>) == 0x18);

	template class SettingT<INIPrefSettingCollection>;
	static_assert(sizeof(SettingT<INIPrefSettingCollection>) == 0x18);

	template class SettingT<INISettingCollection>;
	static_assert(sizeof(SettingT<INISettingCollection>) == 0x18);

	template class SettingT<LipSynchroSettingCollection>;
	static_assert(sizeof(SettingT<LipSynchroSettingCollection>) == 0x18);

	template class SettingT<RegSettingCollection>;
	static_assert(sizeof(SettingT<RegSettingCollection>) == 0x18);
}
