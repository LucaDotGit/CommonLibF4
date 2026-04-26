#pragma once

#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSPickupPutdownSounds.hpp"
#include "RE/S/SpellItem.hpp"
#include "RE/T/TESValueForm.hpp"
#include "RE/T/TESWeightForm.hpp"

namespace RE
{
	class __declspec(novtable) ScrollItem
		: public SpellItem,					// 000
		  public BGSModelMaterialSwap,		// 130
		  public BGSDestructibleObjectForm, // 170
		  public BGSPickupPutdownSounds,	// 180
		  public TESWeightForm,				// 198
		  public TESValueForm				// 1A8
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ScrollItem };
		inline static constexpr auto VTABLE{ VTABLE::ScrollItem };
		inline static constexpr auto FORM_TYPE{ FormType::kScroll };
	};
	static_assert(sizeof(ScrollItem) == 0x1B8);
}
