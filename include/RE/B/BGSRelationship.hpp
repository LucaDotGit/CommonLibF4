#pragma once

#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSRelationship
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSRelationship };
		inline static constexpr auto VTABLE{ VTABLE::BGSRelationship };
		inline static constexpr auto FORM_TYPE{ FormType::kRelationship };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kData = 1 << 1
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		TESNPC* npc01;						 // 20
		TESNPC* npc02;						 // 28
		BGSAssociationType* associationType; // 30
		std::uint32_t packedData;			 // 38
	};
	static_assert(sizeof(BGSRelationship) == 0x40);
}
