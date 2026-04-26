#pragma once

#include "RE/B/BSBound.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/bhkNPCollisionObjectUnlinked.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkStepInfo.hpp"
#include "RE/H/hkVector4f.hpp"
#include "RE/H/hknpCharacterContext.hpp"
#include "RE/H/hknpCharacterState.hpp"
#include "RE/H/hknpCharacterSurfaceInfo.hpp"
#include "RE/N/NiPoint.hpp"
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

	class __declspec(novtable) bhkCharacterController
		: public bhkNPCollisionObjectUnlinked,				  // 000
		  public BSTEventSource<bhkCharacterMoveFinishEvent>, // 030
		  public BSTEventSource<bhkNonSupportContactEvent>,	  // 088
		  public BSTEventSource<bhkCharacterStateChangeEvent> // 0E0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::bhkCharacterController };
		inline static constexpr auto VTABLE{ VTABLE::bhkCharacterController };

		enum class CHARACTER_SIZE : std::int32_t
		{
			kNormal = 0,
			kSized = 1,
			kSizing = 2
		};

		class CheckGoodType
		{
		public:
			// members
			bool checkDangerous;	   // 00
			bool checkActors;		   // 01
			bool checkGround;		   // 02
			bool checkEnvironment;	   // 03
			bool useHitToleranceCheck; // 04
		};
		static_assert(sizeof(CheckGoodType) == 0x05);

		// add
		virtual REX::Float32 GetKeepDistanceImpl() const = 0;																	  // 31
		virtual void InitPhysicsSystemImpl(const bhkCharacterControllerCinfo& a_info) = 0;										  // 32
		virtual void GetPositionImpl(hkVector4f& a_position, bool a_applyCenterOffset) const = 0;								  // 33
		virtual void SetPositionImpl(const hkVector4f& a_position, bool a_applyCenterOffset, bool a_forceWarp) = 0;				  // 34
		virtual void GetPredictedPositionImpl(hkVector4f& a_position, bool a_applyCenterOffset) const = 0;						  // 35
		virtual void ClearPreviousStepCachedDataImpl() = 0;																		  // 36
		virtual void GetTransformImpl(hkTransformf& a_transform) const = 0;														  // 37
		virtual void SetTransformImpl(const hkTransformf& a_transform) = 0;														  // 38
		virtual void GetLinearVelocityImpl(hkVector4f& a_linVel) const = 0;														  // 39
		virtual void SetLinearVelocityImpl(const hkVector4f& a_linVel) = 0;														  // 3A
		virtual bool CheckPenetrationImpl() = 0;																				  // 3B
		virtual bool IntegrateStepImpl(BSTArray<NiPointer<bhkNPCollisionObject>>* a_deferredReleaseColObjs) = 0;				  // 3C
		virtual void FinishMoveImpl(const MoveData& a_moveData) = 0;															  // 3D
		virtual void CheckSupportImpl() = 0;																					  // 3E
		virtual void SetWorldImpl(bhkWorld* a_newWorld) = 0;																	  // 3F
		virtual bhkWorld* GetWorldImpl() const = 0;																				  // 40
		virtual hknpBodyId GetBodyIdImpl() const = 0;																			  // 41
		virtual const hknpBody* GetBodyImpl() const = 0;																		  // 42
		virtual bool SetShapeImpl(hknpShape* a_shape, const hkVector4f&) = 0;													  // 43
		virtual REX::Float32 GetVDBAlpha() const = 0;																			  // 44
		virtual bool GetCurrentCollisionsImpl(BSScrapArray<const hknpBody*>& a_cols) = 0;										  // 45
		virtual bool HasPhysicsStepSubscriptionsImpl() const = 0;																  // 46
		virtual bool AddPhysicsStepSubscriptionsImpl() = 0;																		  // 47
		virtual bool RemovePhysicsStepSubscriptionsImpl() = 0;																	  // 48
		virtual void RotateImpl(const hkTransformf& a_transf, bool a_forceWarp) = 0;											  // 49
		virtual void SendEventOnNonSupportContactsImpl(BSTEventSink<bhkNonSupportContactEvent>& a_sink, bool a_receiveEvent) = 0; // 4A
		virtual void ApplyMoveImmediately() = 0;																				  // 4B
		virtual void ClearCollectorDataImpl() = 0;																				  // 4C

		void Jump(REX::Float32 a_height)
		{
			using FuncType = decltype(&bhkCharacterController::Jump);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkCharacterController::Jump };
			FUNC(this, a_height);
		}

		// members
		hkVector4f forwardVec;														   // 140
		hkStepInfo stepInfo;														   // 150
		hkVector4f outVelocity;														   // 160
		hkVector4f initialVelocity;													   // 170
		hkVector4f velocityMod;														   // 180
		hkVector4f direction;														   // 190
		hkVector4f rotCenter;														   // 1A0
		hkVector4f pushDelta;														   // 1B0
		hkVector4f fakeSupportStart;												   // 1C0
		hkVector4f up;																   // 1D0
		hkVector4f supportNorm;														   // 1E0
		BSBound collisionBound;														   // 1F0
		BSBound bumperCollisionBound;												   // 220
		NiPoint3 cachedLinearVelocity;												   // 250
		NiPoint3 remainderDeltaWS;													   // 24C
		bhkICharOrientationController* orientationCtrl;								   // 268
		hknpCharacterSurfaceInfo surfaceInfo;										   // 270
		hknpCharacterContext context;												   // 2A0
		std::uint32_t flags;														   // 300
		REX::Enum<hknpCharacterState::hknpCharacterStateType, std::int32_t> wantState; // 304
		REX::Float32 velocityTime;													   // 308
		REX::Float32 rotMod;														   // 30C
		REX::Float32 rotModTime;													   // 310
		REX::Float32 calculatePitchTimer;											   // 314
		REX::Float32 acrobatics;													   // 318
		REX::Float32 center;														   // 31C
		REX::Float32 waterHeight;													   // 320
		REX::Float32 jumpHeight;													   // 324
		REX::Float32 fallStartHeight;												   // 328
		REX::Float32 fallTime;														   // 32C
		REX::Float32 gravity;														   // 330
		REX::Float32 pitchAngle;													   // 334
		REX::Float32 rollAngle;														   // 338
		REX::Float32 pitchMult;														   // 33C
		REX::Float32 scale;															   // 340
		REX::Float32 swimFloatHeight;												   // 344
		REX::Float32 actorHeight;													   // 348
		REX::Float32 speedPct;														   // 34C
		std::uint32_t pushCount;													   // 350
		REX::Enum<SHAPE_TYPES, std::int32_t> shapeType;								   // 354
		REX::Enum<SHAPE_TYPES, std::int32_t> sizedShapeType;						   // 358
		std::array<hkRefPtr<hknpShape>, 2> shapes;									   // 360
		REX::Float32 radius;														   // 370
		REX::Float32 height;														   // 374
		REX::Float32 destRadius;													   // 378
		REX::Float32 lodDistance;													   // 37C
		REX::Enum<CHARACTER_SIZE, std::int32_t> size;								   // 380
		std::uint32_t priority;														   // 384
		std::int32_t supportCount;													   // 388
		NiPointer<bhkNPCollisionObject> supportBody;								   // 390
		REX::Float32 bumpedForce;													   // 398
		NiPointer<bhkNPCollisionObject> bumpedBody;									   // 3A0
		NiPointer<bhkNPCollisionObject> bumpedCharCollisionObject;					   // 3A8
		BSTHashMap<std::uint32_t, REX::Float32> bumpedBodyIdExpirationM;			   // 3B0
		std::byte* userData;														   // 3E0
		BSTHashMap<bhkNPCollisionObject*, DamageImpactData*> damageImpacts;			   // 3E8
		REX::Float32 maxSlope;														   // 418
		std::uint32_t supportMaterial;												   // 41C
		REX::Enum<COL_LAYER, std::int32_t> supportLayer;							   // 420
		REX::Float32 stepHeight;													   // 424
		REX::Float32 stepHeightMod;													   // 428
		REX::Float32 stepHeightModTimer;											   // 42C
		REX::Float32 castDepthC;													   // 430
		std::uint32_t numCollisions;												   // 434
		std::uint32_t stickyCollisionGroup;											   // 438
		bool allSurfacesStopped;													   // 43C
		bool stickyCollisions;														   // 43D
		bool fakeSupport;															   // 43E
		bool calculatePitch;														   // 43F
		bool useBumper;																   // 440
		bool hasBumper;																   // 441
		bool inAirPreMove;															   // 442
	};
	static_assert(sizeof(bhkCharacterController) == 0x450);
}
