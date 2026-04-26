#include "RE/S/SettingCollection.hpp"

namespace RE
{
	template class SettingCollection<Setting>;
	static_assert(sizeof(SettingCollection<Setting>) == 0x118);
}
