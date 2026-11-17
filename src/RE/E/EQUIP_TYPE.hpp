#pragma once

namespace RE
{
	enum class EQUIP_TYPE : std::int32_t
	{
		None = 0,
		Equipped = 1,
		LeftHandEquip = 2,
		RightHandEquip = 3,
		BothHandEquip = 4,
		WillEquipAgain = 5
	};
}
