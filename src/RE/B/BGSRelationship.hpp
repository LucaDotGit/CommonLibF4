#pragma once

#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSRelationship : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSRelationship;
		inline static constexpr const auto& VTABLE = VTABLE::BGSRelationship;
		inline static constexpr auto FORM_TYPE = FormType::Relationship;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				Data = 1 << 1
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		TESNPC* npc01;						 // 0x20
		TESNPC* npc02;						 // 0x28
		BGSAssociationType* associationType; // 0x30
		std::uint32_t packedData;			 // 0x38
	};

	static_assert(sizeof(BGSRelationship) == 0x40);
}
