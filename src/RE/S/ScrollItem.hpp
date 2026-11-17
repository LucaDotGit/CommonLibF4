#pragma once

#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSPickupPutdownSounds.hpp"
#include "RE/S/SpellItem.hpp"
#include "RE/T/TESValueForm.hpp"
#include "RE/T/TESWeightForm.hpp"

namespace RE
{
	class __declspec(novtable) ScrollItem :
		public SpellItem,				  // 0x000
		public BGSModelMaterialSwap,	  // 0x130
		public BGSDestructibleObjectForm, // 0x170
		public BGSPickupPutdownSounds,	  // 0x180
		public TESWeightForm,			  // 0x198
		public TESValueForm				  // 0x1A8
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ScrollItem;
		inline static constexpr const auto& VTABLE = VTABLE::ScrollItem;
		inline static constexpr auto FORM_TYPE = FormType::Scroll;

		~ScrollItem() override; // 0x00
	};

	static_assert(sizeof(ScrollItem) == 0x1B8);
}
