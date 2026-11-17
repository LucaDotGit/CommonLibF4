#pragma once

#include "Scaleform/G/GFx_State.hpp"

namespace Scaleform::GFx
{
	class __declspec(novtable) MultitouchInterface : public State // 0x00
	{
	public:
		inline static constexpr auto STATE_TYPE = StateType::MultitouchInterface;

		enum class MultitouchInputMode : std::int32_t
		{
			None = 0,
			TouchPoint = 1,
			Gesture = 2,
			Mixed = (TouchPoint | Gesture)
		};

		enum GestureMask : std::int32_t
		{
			MTG_None = 0,
			MTG_Pan = 1 << 0,
			MTG_Zoom = 1 << 1,
			MTG_Rotate = 1 << 2,
			MTG_Swipe = 1 << 3
		};

		MultitouchInterface() :
			State(STATE_TYPE)
		{
			// REL::EmplaceVtable(this);
		}

		~MultitouchInterface() override; // 0x00

		// add
		virtual auto GetMaxTouchPoints() const -> std::uint32_t = 0;					  // 0x01
		virtual auto GetSupportedGesturesMask() const -> std::uint32_t = 0;				  // 0x02
		virtual auto SetMultitouchInputMode(MultitouchInputMode a_inputMode) -> bool = 0; // 0x03
	};
}
