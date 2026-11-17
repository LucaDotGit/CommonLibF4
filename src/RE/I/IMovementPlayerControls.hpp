#pragma once

#include "RE/I/IMovementInterface.hpp"

namespace RE
{
	class PlayerControlsMovementData;

	class __declspec(novtable) IMovementPlayerControls : public IMovementInterface // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IMovementPlayerControls;
		inline static constexpr const auto& VTABLE = VTABLE::IMovementPlayerControls;

		// add
		virtual void GetControllerOutput(
			std::uint32_t a_numericID,
			PlayerControlsMovementData& a_normalizedOutputData) = 0; // 0x01
	};

	static_assert(sizeof(IMovementPlayerControls) == 0x08);
}
