#pragma once

#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESImageSpaceModifiableForm.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSCameraShot :
		public TESForm,					   // 0x00
		public TESModel,				   // 0x20
		public TESImageSpaceModifiableForm // 0x50
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSCameraShot;
		inline static constexpr const auto& VTABLE = VTABLE::BGSCameraShot;
		inline static constexpr auto FORM_TYPE = FormType::CameraShot;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class CAM_ACTION : std::int32_t
		{
			Shoot = 0,
			Fly = 1,
			Hit = 2,
			Zoom = 3,

			_Count = 4
		};

		enum class CAM_OBJECT : std::int32_t
		{
			Attacker = 0,
			Projectile = 1,
			Target = 2,
			LeadActor = 3,

			_Count = 4
		};

		enum class CAM_USER : std::int32_t
		{
			None = 0,
			VATS = 1,
			Dialogue = 2,

			_Count = 3
		};

		enum class CAM_ZOOM : std::int32_t
		{
			Default = 0,
			ZoomIn = 1,
			ZoomOut = 2,

			_Count = 3
		};

		class CAMERA_SHOT_DATA
		{
		public:
			// members
			REX::Enum<CAM_ACTION, std::int32_t> cameraAction; // 0x00
			REX::Enum<CAM_OBJECT, std::int32_t> location;	  // 0x04
			REX::Enum<CAM_OBJECT, std::int32_t> target;		  // 0x08
			std::uint32_t flags;							  // 0x0C
			REX::Float32 playerTimeMult;					  // 0x10
			REX::Float32 targetTimeMult;					  // 0x14
			REX::Float32 globalTimeMult;					  // 0x18
			REX::Float32 maxTime;							  // 0x1C
			REX::Float32 minTime;							  // 0x20
			REX::Float32 targetPercentBetweenActors;		  // 0x24
			REX::Float32 nearTargetDistance;				  // 0x28
			REX::Float32 locationSpring;					  // 0x2C
			REX::Float32 targetSpring;						  // 0x30
			REX::Float32 rotationOffsetX;					  // 0x34
			REX::Float32 rotationOffsetY;					  // 0x38
			REX::Float32 rotationOffsetZ;					  // 0x3C
		};

		static_assert(sizeof(CAMERA_SHOT_DATA) == 0x40);

		// members
		CAMERA_SHOT_DATA data;	 // 0x60
		TESCondition conditions; // 0xA0
	};

	static_assert(sizeof(BGSCameraShot) == 0xA8);
}
