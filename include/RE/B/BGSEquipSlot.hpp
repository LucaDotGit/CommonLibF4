#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSEquipSlot
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEquipSlot };
		inline static constexpr auto VTABLE{ VTABLE::BGSEquipSlot };
		inline static constexpr auto FORM_TYPE{ FormType::kEquipSlot };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kUseAllParents = 1 << 0,
			kParentsOptional = 1 << 1,
			kItemSlot = 1 << 2
		};

		// members
		BSTArray<BGSEquipSlot*> parentSlots;	  // 20
		REX::EnumSet<Flags, std::uint32_t> flags; // 38
		ActorValueInfo* conditionActorValue;	  // 40
	};
	static_assert(sizeof(BGSEquipSlot) == 0x48);
}
