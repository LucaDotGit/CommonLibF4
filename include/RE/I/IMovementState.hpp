#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/I/IMovementInterface.hpp"
#include "RE/M/Movement_MaxSpeeds.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class BSPathingLocation;
	class BSPathingRequest;
	class IMovementParameters;

	class __declspec(novtable) IMovementState
		: public IMovementInterface // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IMovementState };
		inline static constexpr auto VTABLE{ VTABLE::IMovementState };

		enum class CHARACTER_STATE : std::int32_t
		{
			kOnGround = 0,
			kJumping = 1,
			kInAir = 2,
			kClimbing = 3,
			kFlying = 4,
			kSwimming = 5,
			kFloating = 6
		};

		~IMovementState() override; // 00

		// add
		virtual std::uint32_t DoGetNumericID() const = 0;																		 // 01
		virtual void DoGetPathingLocation(BSPathingLocation& a_outLocation) const = 0;											 // 02
		virtual void DoGetLocation(NiPoint3& a_outLocation) const = 0;															 // 03
		virtual void DoGetEulerAngles(NiPoint3& a_outAngles) const = 0;															 // 04
		virtual REX::Float32 DoGetMovementSpeed() const = 0;																	 // 05
		virtual REX::Float32 DoGetAnimationSpeed() const = 0;																	 // 06
		virtual REX::Float32 DoGetCurrentSpeed() const = 0;																		 // 07
		virtual void DoGetRotationSpeed(NiPoint3& a_outRotationSpeed) const = 0;												 // 08
		virtual void DoGetMovementRotation(NiPoint3& a_outMovementRotation) const = 0;											 // 09
		virtual bool DoGetCurrentMaxSpeeds(Movement::MaxSpeeds& a_outMaxSpeeds) const = 0;										 // 0A
		virtual REX::Float32 DoGetMovementRadius() const = 0;																	 // 0B
		virtual REX::Float32 DoGetMovementWidth() const = 0;																	 // 0C
		virtual REX::Float32 DoGetMovementLength() const = 0;																	 // 0D
		virtual REX::Float32 DoGetMovementHeight() const = 0;																	 // 0E
		virtual REX::Float32 DoGetMovementPitch() const = 0;																	 // 0F
		virtual REX::Float32 DoGetLookingHeight() const = 0;																	 // 10
		virtual REX::Float32 DoGetPathingRadius() const = 0;																	 // 11
		virtual bool DoMakeDefaultMovementParameters(BSTSmartPointer<IMovementParameters>& a_parameters) const = 0;				 // 12
		virtual const IMovementParameters& DoGetDefaultMovementParameters() const = 0;											 // 13
		virtual REX::Float32 DoGetFlightAngleGain() const = 0;																	 // 14
		virtual CHARACTER_STATE DoGetCharacterState() const = 0;																 // 15
		virtual bool DoGetUseVelocityObstacles() const = 0;																		 // 16
		virtual std::uint32_t DoGetCollisionFilter() const = 0;																	 // 17
		virtual bool DoCanRotate() const = 0;																					 // 18
		virtual bool DoUpdatePathingRequest(const BSTSmartPointer<BSPathingRequest>& a_request) const = 0;						 // 19
		virtual void DoGetFaceTargetSource(NiPoint3& a_location, NiPoint3& a_orientation) const = 0;							 // 1A
		virtual bool DoGetFaceTargetAllowRoll() const = 0;																		 // 1B
		virtual bool DoShouldDecelerateToStop(REX::Float32 a_currentSpeed, REX::Float32& a_nonDecelerateStopDistance) const = 0; // 1C
		virtual void DoGetMaxAngles(NiPoint3& a_maxAngles) const = 0;															 // 1D
		virtual void DoGetLookingLocation(NiPoint3& a_location) const = 0;														 // 1E
		virtual bool DoGetSprinting() const = 0;																				 // 1F
		virtual bool DoIsHovering() const = 0;																					 // 20
	};
	static_assert(sizeof(IMovementState) == 0x08);
}
