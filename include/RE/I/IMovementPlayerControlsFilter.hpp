#pragma once

#include "RE/I/IMovementInterface.hpp"

namespace RE
{
	class MovementData;

	class __declspec(novtable) IMovementPlayerControlsFilter
		: public IMovementInterface // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IMovementPlayerControlsFilter };
		inline static constexpr auto VTABLE{ VTABLE::IMovementPlayerControlsFilter };

		// add
		virtual void FilterControllerOutput(const MovementData& a_previousFrameData, MovementData& a_inOutData, REX::Float32 a_timeDelta) const = 0; // 01
		virtual bool ShouldPlayLargeDeltas() const = 0;																								 // 02
		virtual bool IsInCombatStance() const = 0;																									 // 03
		virtual bool DampenRotationInput() const = 0;																								 // 04
		virtual bool DampenInput(REX::Float32& a_acceleration, REX::Float32& a_deceleration) const = 0;												 // 05
		virtual bool IsInThirdPerson() const = 0;																									 // 06
		virtual void FilterDampenedOutput(const MovementData&, MovementData& a_inOutData) const = 0;												 // 07
		virtual bool ForceWalkBeforeRun() const = 0;																								 // 08
		virtual REX::Float32 GetNormalizedAngleAccelerationMultiplier() const = 0;																	 // 09
	};
	static_assert(sizeof(IMovementPlayerControlsFilter) == 0x08);
}
