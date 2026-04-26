#pragma once

#include "RE/B/BGSBodyPartDefs_HitReactionData.hpp"
#include "RE/B/BGSPreloadable.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class BGSBodyPart;

	class __declspec(novtable) BGSBodyPartData
		: public TESForm,		// 000
		  public TESModel,		// 020
		  public BGSPreloadable // 050
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSBodyPartData };
		inline static constexpr auto VTABLE{ VTABLE::BGSBodyPartData };
		inline static constexpr auto FORM_TYPE{ FormType::kBodyPartData };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class PartType : std::int32_t
		{
			kTorso = 0,
			kHead1 = 1,
			kEye = 2,
			kLookAt = 3,
			kFlyGrab = 4,
			kHead2 = 5,
			kLeftArm1 = 6,
			kLeftArm2 = 7,
			kRightArm1 = 8,
			kRightArm2 = 9,
			kLeftLeg1 = 10,
			kLeftLeg2 = 11,
			kLeftLeg3 = 12,
			kRightLeg1 = 13,
			kRightLeg2 = 14,
			kRightLeg3 = 15,
			kBrain = 16,
			kWeapon = 17,
			kRoot = 18,
			kCOM = 19,
			kPelvis = 20,
			kCamera = 21,
			kOffsetRoot = 22,
			kLeftFoot = 23,
			kRightFoot = 24,
			kFaceTargetSource = 25,

			kTotal = 26
		};

		// members
		std::array<BGSBodyPart*, std::to_underlying(PartType::kTotal)> partArray; // 058
		BGSBodyPartDefs::HitReactionData defaultHitReactionData;				  // 128
	};
	static_assert(sizeof(BGSBodyPartData) == 0x150);
}
