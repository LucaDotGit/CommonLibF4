#pragma once

#include "RE/B/BGSBodyPartDefs_HitReactionData.hpp"
#include "RE/B/BGSPreloadable.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class BGSBodyPart;

	class __declspec(novtable) BGSBodyPartData :
		public TESForm,		  // 0x000
		public TESModel,	  // 0x020
		public BGSPreloadable // 0x050
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSBodyPartData;
		inline static constexpr const auto& VTABLE = VTABLE::BGSBodyPartData;
		inline static constexpr auto FORM_TYPE = FormType::BodyPartData;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class PartType : std::int32_t
		{
			Torso = 0,
			Head1 = 1,
			Eye = 2,
			LookAt = 3,
			FlyGrab = 4,
			Head2 = 5,
			LeftArm1 = 6,
			LeftArm2 = 7,
			RightArm1 = 8,
			RightArm2 = 9,
			LeftLeg1 = 10,
			LeftLeg2 = 11,
			LeftLeg3 = 12,
			RightLeg1 = 13,
			RightLeg2 = 14,
			RightLeg3 = 15,
			Brain = 16,
			Weapon = 17,
			Root = 18,
			COM = 19,
			Pelvis = 20,
			Camera = 21,
			OffsetRoot = 22,
			LeftFoot = 23,
			RightFoot = 24,
			FaceTargetSource = 25,

			_Count = 26
		};

		// members
		std::array<BGSBodyPart*, std::to_underlying(PartType::_Count)> partArray; // 0x058
		BGSBodyPartDefs::HitReactionData defaultHitReactionData;				  // 0x128
	};

	static_assert(sizeof(BGSBodyPartData) == 0x150);
}
