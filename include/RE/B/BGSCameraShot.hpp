#pragma once

#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESImageSpaceModifiableForm.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSCameraShot
		: public TESForm,					 // 00
		  public TESModel,					 // 20
		  public TESImageSpaceModifiableForm // 50
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSCameraShot };
		inline static constexpr auto VTABLE{ VTABLE::BGSCameraShot };
		inline static constexpr auto FORM_TYPE{ FormType::kCameraShot };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class CAM_ACTION : std::int32_t
		{
			kShoot = 0,
			kFly = 1,
			kHit = 2,
			kZoom = 3,

			kTotal = 4
		};

		enum class CAM_OBJECT : std::int32_t
		{
			kAttacker = 0,
			kProjectile = 1,
			kTarget = 2,
			kLeadActor = 3,

			kTotal = 4
		};

		enum class CAM_USER : std::int32_t
		{
			kNone = 0,
			kVATS = 1,
			kDialogue = 2,

			kTotal = 3
		};

		enum class CAM_ZOOM : std::int32_t
		{
			kDefault = 0,
			kZoomIn = 1,
			kZoomOut = 2,

			kTotal = 3
		};

		class CAMERA_SHOT_DATA
		{
		public:
			// members
			REX::Enum<CAM_ACTION, std::int32_t> cameraAction; // 00
			REX::Enum<CAM_OBJECT, std::int32_t> location;	  // 04
			REX::Enum<CAM_OBJECT, std::int32_t> target;		  // 08
			std::uint32_t flags;							  // 0C
			REX::Float32 playerTimeMult;					  // 10
			REX::Float32 targetTimeMult;					  // 14
			REX::Float32 globalTimeMult;					  // 18
			REX::Float32 maxTime;							  // 1C
			REX::Float32 minTime;							  // 20
			REX::Float32 targetPercentBetweenActors;		  // 24
			REX::Float32 nearTargetDistance;				  // 28
			REX::Float32 locationSpring;					  // 2C
			REX::Float32 targetSpring;						  // 30
			REX::Float32 rotationOffsetX;					  // 34
			REX::Float32 rotationOffsetY;					  // 38
			REX::Float32 rotationOffsetZ;					  // 3C
		};
		static_assert(sizeof(CAMERA_SHOT_DATA) == 0x40);

		// members
		CAMERA_SHOT_DATA data;	 // 60
		TESCondition conditions; // A0
	};
	static_assert(sizeof(BGSCameraShot) == 0xA8);
}
