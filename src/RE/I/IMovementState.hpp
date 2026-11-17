#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/I/IMovementInterface.hpp"
#include "RE/M/Movement_MaxSpeeds.hpp"

namespace RE
{
	class BSPathingLocation;
	class BSPathingRequest;
	class IMovementParameters;
	class NiPoint3;

	class __declspec(novtable) IMovementState : public IMovementInterface // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IMovementState;
		inline static constexpr const auto& VTABLE = VTABLE::IMovementState;

		enum class CHARACTER_STATE : std::int32_t
		{
			OnGround = 0,
			Jumping = 1,
			InAir = 2,
			Climbing = 3,
			Flying = 4,
			Swimming = 5,
			Floating = 6
		};

		~IMovementState() override = default; // 0x00

		// add
		virtual auto DoGetNumericID() const -> std::uint32_t = 0;								   // 0x01
		virtual void DoGetPathingLocation(BSPathingLocation& a_outLocation) const = 0;			   // 0x02
		virtual void DoGetLocation(NiPoint3& a_outLocation) const = 0;							   // 0x03
		virtual void DoGetEulerAngles(NiPoint3& a_outAngles) const = 0;							   // 0x04
		virtual auto DoGetMovementSpeed() const -> REX::Float32 = 0;							   // 0x05
		virtual auto DoGetAnimationSpeed() const -> REX::Float32 = 0;							   // 0x06
		virtual auto DoGetCurrentSpeed() const -> REX::Float32 = 0;								   // 0x07
		virtual void DoGetRotationSpeed(NiPoint3& a_outRotationSpeed) const = 0;				   // 0x08
		virtual void DoGetMovementRotation(NiPoint3& a_outMovementRotation) const = 0;			   // 0x09
		virtual auto DoGetCurrentMaxSpeeds(Movement::MaxSpeeds& a_outMaxSpeeds) const -> bool = 0; // 0x0A
		virtual auto DoGetMovementRadius() const -> REX::Float32 = 0;							   // 0x0B
		virtual auto DoGetMovementWidth() const -> REX::Float32 = 0;							   // 0x0C
		virtual auto DoGetMovementLength() const -> REX::Float32 = 0;							   // 0x0D
		virtual auto DoGetMovementHeight() const -> REX::Float32 = 0;							   // 0x0E
		virtual auto DoGetMovementPitch() const -> REX::Float32 = 0;							   // 0x0F
		virtual auto DoGetLookingHeight() const -> REX::Float32 = 0;							   // 0x10
		virtual auto DoGetPathingRadius() const -> REX::Float32 = 0;							   // 0x11
		virtual auto DoMakeDefaultMovementParameters(BSTSmartPointer<IMovementParameters>& a_parameters) const
			-> bool = 0;																	   // 0x12
		virtual auto DoGetDefaultMovementParameters() const -> const IMovementParameters& = 0; // 0x13
		virtual auto DoGetFlightAngleGain() const -> REX::Float32 = 0;						   // 0x14
		virtual auto DoGetCharacterState() const -> CHARACTER_STATE = 0;					   // 0x15
		virtual auto DoGetUseVelocityObstacles() const -> bool = 0;							   // 0x16
		virtual auto DoGetCollisionFilter() const -> std::uint32_t = 0;						   // 0x17
		virtual auto DoCanRotate() const -> bool = 0;										   // 0x18
		virtual auto DoUpdatePathingRequest(const BSTSmartPointer<BSPathingRequest>& a_request) const
			-> bool = 0;																			 // 0x19
		virtual void DoGetFaceTargetSource(NiPoint3& a_location, NiPoint3& a_orientation) const = 0; // 0x1A
		virtual auto DoGetFaceTargetAllowRoll() const -> bool = 0;									 // 0x1B
		virtual auto DoShouldDecelerateToStop(REX::Float32 a_currentSpeed, REX::Float32& a_nonDecelerateStopDistance)
			const -> bool = 0;											   // 0x1C
		virtual void DoGetMaxAngles(NiPoint3& a_maxAngles) const = 0;	   // 0x1D
		virtual void DoGetLookingLocation(NiPoint3& a_location) const = 0; // 0x1E
		virtual auto DoGetSprinting() const -> bool = 0;				   // 0x1F
		virtual auto DoIsHovering() const -> bool = 0;					   // 0x20
	};

	static_assert(sizeof(IMovementState) == 0x08);
}
