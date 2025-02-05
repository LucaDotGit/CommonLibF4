#pragma once

#include "RE/Bethesda/BSFixedString.hpp"

namespace RE::BGSBodyPartDefs
{
	struct LIMB_ENUMS
	{
		enum LIMB_ENUM
		{
			kNone = static_cast<std::underlying_type_t<LIMB_ENUM>>(-1),
			kTorso = 0,
			kHead,
			kEye,
			kLookAt,
			kFlyGrab,
			kSaddle,

			kTotal
		};
	};
	using LIMB_ENUM = LIMB_ENUMS::LIMB_ENUM;

	struct HitReactionData
	{
	public:
		// members
		BSFixedString chainStart; // 00
		BSFixedString chainEnd;	  // 08
		BSFixedString variableX;  // 10
		BSFixedString variableY;  // 18
		BSFixedString variableZ;  // 20
	};
	static_assert(sizeof(HitReactionData) == 0x28);
}
