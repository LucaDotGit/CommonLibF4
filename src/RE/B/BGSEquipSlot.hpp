#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSEquipSlot : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSEquipSlot;
		inline static constexpr const auto& VTABLE = VTABLE::BGSEquipSlot;
		inline static constexpr auto FORM_TYPE = FormType::EquipSlot;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			None = 0,
			UseAllParents = 1 << 0,
			ParentsOptional = 1 << 1,
			ItemSlot = 1 << 2
		};

		// members
		BSTArray<BGSEquipSlot*> parentSlots;	  // 0x20
		REX::EnumSet<Flags, std::uint32_t> flags; // 0x38
		ActorValueInfo* conditionActorValue;	  // 0x40
	};

	static_assert(sizeof(BGSEquipSlot) == 0x48);
}
