#pragma once

#include "RE/I/IMovementInterface.hpp"

namespace RE
{
	class MovementData;

	class __declspec(novtable) IMovementPlayerControlsFilter : public IMovementInterface // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IMovementPlayerControlsFilter;
		inline static constexpr const auto& VTABLE = VTABLE::IMovementPlayerControlsFilter;

		~IMovementPlayerControlsFilter() override = default; // 0x00

		// add
		virtual void FilterControllerOutput(
			const MovementData& a_previousFrameData,
			MovementData& a_inOutData,
			REX::Float32 a_deltaTime) const = 0;																// 0x01
		virtual auto ShouldPlayLargeDeltas() const -> bool = 0;													// 0x02
		virtual auto IsInCombatStance() const -> bool = 0;														// 0x03
		virtual auto DampenRotationInput() const -> bool = 0;													// 0x04
		virtual auto DampenInput(REX::Float32& a_acceleration, REX::Float32& a_deceleration) const -> bool = 0; // 0x05
		virtual auto IsInThirdPerson() const -> bool = 0;														// 0x06
		virtual void FilterDampenedOutput(const MovementData&, MovementData& a_inOutData) const = 0;			// 0x07
		virtual auto ForceWalkBeforeRun() const -> bool = 0;													// 0x08
		virtual auto GetNormalizedAngleAccelerationMultiplier() const -> REX::Float32 = 0;						// 0x09
	};

	static_assert(sizeof(IMovementPlayerControlsFilter) == 0x08);
}
