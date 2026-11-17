#pragma once

#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/M/MOVABLE_STATIC_DATA.hpp"
#include "RE/T/TESObjectSTAT.hpp"

namespace RE
{
	class __declspec(novtable) BGSMovableStatic :
		public TESObjectSTAT,			  // 0x000
		public BGSDestructibleObjectForm, // 0x0E8
		public BGSKeywordForm			  // 0x0F8
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSMovableStatic;
		inline static constexpr const auto& VTABLE = VTABLE::BGSMovableStatic;
		inline static constexpr auto FORM_TYPE = FormType::MovableStatic;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				MustUpdateAnims = 1 << 8,
				HiddenFromLocalMap = 1 << 9,
				Ignored = 1 << 12,
				HasDistantLOD = 1 << 15,
				RandomAnimStart = 1 << 16,
				HasCurrents = 1 << 19,
				Obstacle = 1 << 25,
				NavMeshGeneration_Filter = 1 << 26,
				NavMeshGeneration_BoundingBox = 1 << 27,
				NavMeshGeneration_Ground = 1 << 30
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		~BGSMovableStatic() override; // 0x00

		// members
		BGSSoundDescriptorForm* soundLoop; // 0x118
		MOVABLE_STATIC_DATA movableData;   // 0x120
	};

	static_assert(sizeof(BGSMovableStatic) == 0x128);
}
