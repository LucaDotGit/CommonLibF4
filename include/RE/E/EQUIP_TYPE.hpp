#pragma once

namespace RE
{
	enum class EQUIP_TYPE : std::int32_t
	{
		kNone = 0,
		kEquipped = 1,
		kLeftHandEquip = 2,
		kRightHandEquip = 3,
		kBothHandEquip = 4,
		kWillEquipAgain = 5
	};
}
