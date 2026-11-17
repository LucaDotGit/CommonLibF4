#pragma once

#include "RE/B/BSBound.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/bhkNPCollisionObjectUnlinked.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkStepInfo.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpCharacterContext.hpp"
#include "RE/H/hknpCharacterState.hpp"
#include "RE/H/hknpCharacterSurfaceInfo.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	enum class COL_LAYER : std::int32_t;
	enum class SHAPE_TYPES : std::int32_t;

	class bhkCharacterControllerCinfo;
	class bhkCharacterMoveFinishEvent;
	class bhkCharacterStateChangeEvent;
	class bhkICharOrientationController;
	class bhkNonSupportContactEvent;
	class bhkWorld;
	class DamageImpactData;
	class MoveData;

	class __declspec(novtable) bhkCharacterController :
		public bhkNPCollisionObjectUnlinked,				// 0x000
		public BSTEventSource<bhkCharacterMoveFinishEvent>, // 0x030
		public BSTEventSource<bhkNonSupportContactEvent>,	// 0x088
		public BSTEventSource<bhkCharacterStateChangeEvent> // 0x0E0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::bhkCharacterController;
		inline static constexpr const auto& VTABLE = VTABLE::bhkCharacterController;

		enum class ControllerFlags : std::uint32_t; // To-Do

		enum class CHARACTER_SIZE : std::int32_t
		{
			Normal = 0,
			Sized = 1,
			Sizing = 2
		};

		class CheckGoodType
		{
		public:
			// members
			bool checkDangerous;	   // 0x00
			bool checkActors;		   // 0x01
			bool checkGround;		   // 0x02
			bool checkEnvironment;	   // 0x03
			bool useHitToleranceCheck; // 0x04
		};

		static_assert(sizeof(CheckGoodType) == 0x05);

		// add
		virtual auto GetKeepDistanceImpl() const -> REX::Float32 = 0;							 // 0x31
		virtual void InitPhysicsSystemImpl(const bhkCharacterControllerCinfo& a_info) = 0;		 // 0x32
		virtual void GetPositionImpl(hkVector4& a_position, bool a_applyCenterOffset) const = 0; // 0x33
		virtual void SetPositionImpl(
			const hkVector4& a_position,
			bool a_applyCenterOffset,
			bool a_forceWarp) = 0;																		  // 0x34
		virtual void GetPredictedPositionImpl(hkVector4& a_position, bool a_applyCenterOffset) const = 0; // 0x35
		virtual void ClearPreviousStepCachedDataImpl() = 0;												  // 0x36
		virtual void GetTransformImpl(hkTransform& a_transform) const = 0;								  // 0x37
		virtual void SetTransformImpl(const hkTransform& a_transform) = 0;								  // 0x38
		virtual void GetLinearVelocityImpl(hkVector4& a_linVel) const = 0;								  // 0x39
		virtual void SetLinearVelocityImpl(const hkVector4& a_linVel) = 0;								  // 0x3A
		virtual auto CheckPenetrationImpl() -> bool = 0;												  // 0x3B
		virtual auto IntegrateStepImpl(BSTArray<NiPointer<bhkNPCollisionObject>>* a_deferredReleaseColObjs)
			-> bool = 0;																		  // 0x3C
		virtual void FinishMoveImpl(const MoveData& a_moveData) = 0;							  // 0x3D
		virtual void CheckSupportImpl() = 0;													  // 0x3E
		virtual void SetWorldImpl(bhkWorld* a_newWorld) = 0;									  // 0x3F
		virtual auto GetWorldImpl() const -> bhkWorld* = 0;										  // 0x40
		virtual auto GetBodyIdImpl() const -> hknpBodyId = 0;									  // 0x41
		virtual auto GetBodyImpl() const -> const hknpBody* = 0;								  // 0x42
		virtual auto SetShapeImpl(hknpShape* a_shape, const hkVector4&) -> bool = 0;			  // 0x43
		virtual auto GetVDBAlpha() const -> REX::Float32 = 0;									  // 0x44
		virtual auto GetCurrentCollisionsImpl(BSScrapArray<const hknpBody*>& a_cols) -> bool = 0; // 0x45
		virtual auto HasPhysicsStepSubscriptionsImpl() const -> bool = 0;						  // 0x46
		virtual auto AddPhysicsStepSubscriptionsImpl() -> bool = 0;								  // 0x47
		virtual auto RemovePhysicsStepSubscriptionsImpl() -> bool = 0;							  // 0x48
		virtual void RotateImpl(const hkTransform& a_transf, bool a_forceWarp) = 0;				  // 0x49
		virtual void SendEventOnNonSupportContactsImpl(
			BSTEventSink<bhkNonSupportContactEvent>& a_sink,
			bool a_receiveEvent) = 0;			   // 0x4A
		virtual void ApplyMoveImmediately() = 0;   // 0x4B
		virtual void ClearCollectorDataImpl() = 0; // 0x4C

		void Jump(REX::Float32 a_height)
		{
			using FuncType = decltype(&bhkCharacterController::Jump);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkCharacterController::Jump);
			std::invoke(FUNC, this, a_height);
		}

		// members
		hkVector4 forwardVec;														   // 0x140
		hkStepInfo stepInfo;														   // 0x150
		hkVector4 outVelocity;														   // 0x160
		hkVector4 initialVelocity;													   // 0x170
		hkVector4 velocityMod;														   // 0x180
		hkVector4 direction;														   // 0x190
		hkVector4 rotCenter;														   // 0x1A0
		hkVector4 pushDelta;														   // 0x1B0
		hkVector4 fakeSupportStart;													   // 0x1C0
		hkVector4 up;																   // 0x1D0
		hkVector4 supportNorm;														   // 0x1E0
		BSBound collisionBound;														   // 0x1F0
		BSBound bumperCollisionBound;												   // 0x220
		NiPoint3 cachedLinearVelocity;												   // 0x250
		NiPoint3 remainderDeltaWS;													   // 0x24C
		bhkICharOrientationController* orientationCtrl;								   // 0x268
		hknpCharacterSurfaceInfo surfaceInfo;										   // 0x270
		hknpCharacterContext context;												   // 0x2A0
		REX::EnumSet<ControllerFlags, std::uint32_t> controllerFlags;				   // 0x300
		REX::Enum<hknpCharacterState::hknpCharacterStateType, std::int32_t> wantState; // 0x304
		REX::Float32 velocityTime;													   // 0x308
		REX::Float32 rotMod;														   // 0x30C
		REX::Float32 rotModTime;													   // 0x310
		REX::Float32 calculatePitchTimer;											   // 0x314
		REX::Float32 acrobatics;													   // 0x318
		REX::Float32 center;														   // 0x31C
		REX::Float32 waterHeight;													   // 0x320
		REX::Float32 jumpHeight;													   // 0x324
		REX::Float32 fallStartHeight;												   // 0x328
		REX::Float32 fallTime;														   // 0x32C
		REX::Float32 gravity;														   // 0x330
		REX::Float32 pitchAngle;													   // 0x334
		REX::Float32 rollAngle;														   // 0x338
		REX::Float32 pitchMult;														   // 0x33C
		REX::Float32 scale;															   // 0x340
		REX::Float32 swimFloatHeight;												   // 0x344
		REX::Float32 actorHeight;													   // 0x348
		REX::Float32 speedPct;														   // 0x34C
		std::uint32_t pushCount;													   // 0x350
		REX::Enum<SHAPE_TYPES, std::int32_t> shapeType;								   // 0x354
		REX::Enum<SHAPE_TYPES, std::int32_t> sizedShapeType;						   // 0x358
		std::array<hkRefPtr<hknpShape>, 2> shapes;									   // 0x360
		REX::Float32 radius;														   // 0x370
		REX::Float32 height;														   // 0x374
		REX::Float32 destRadius;													   // 0x378
		REX::Float32 lodDistance;													   // 0x37C
		REX::Enum<CHARACTER_SIZE, std::int32_t> size;								   // 0x380
		std::uint32_t priority;														   // 0x384
		std::int32_t supportCount;													   // 0x388
		NiPointer<bhkNPCollisionObject> supportBody;								   // 0x390
		REX::Float32 bumpedForce;													   // 0x398
		NiPointer<bhkNPCollisionObject> bumpedBody;									   // 0x3A0
		NiPointer<bhkNPCollisionObject> bumpedCharCollisionObject;					   // 0x3A8
		BSTHashMap<std::uint32_t, REX::Float32> bumpedBodyIdExpirationM;			   // 0x3B0
		std::byte* userData;														   // 0x3E0
		BSTHashMap<bhkNPCollisionObject*, DamageImpactData*> damageImpacts;			   // 0x3E8
		REX::Float32 maxSlope;														   // 0x418
		std::uint32_t supportMaterial;												   // 0x41C
		REX::Enum<COL_LAYER, std::int32_t> supportLayer;							   // 0x420
		REX::Float32 stepHeight;													   // 0x424
		REX::Float32 stepHeightMod;													   // 0x428
		REX::Float32 stepHeightModTimer;											   // 0x42C
		REX::Float32 castDepthC;													   // 0x430
		std::uint32_t numCollisions;												   // 0x434
		std::uint32_t stickyCollisionGroup;											   // 0x438
		bool allSurfacesStopped;													   // 0x43C
		bool stickyCollisions;														   // 0x43D
		bool fakeSupport;															   // 0x43E
		bool calculatePitch;														   // 0x43F
		bool useBumper;																   // 0x440
		bool hasBumper;																   // 0x441
		bool inAirPreMove;															   // 0x442
	};

	static_assert(sizeof(bhkCharacterController) == 0x450);
}
