#pragma once

#include "Scaleform/G/GFx_State.hpp"

namespace Scaleform::GFx
{
	class __declspec(novtable) MultitouchInterface
		: public State // 00
	{
	public:
		inline static constexpr auto STATE_TYPE{ StateType::kMultitouchInterface };

		enum class MultitouchInputMode : std::int32_t
		{
			kNone = 0,
			kTouchPoint = 1,
			kGesture = 2,
			kMixed = (kTouchPoint | kGesture)
		};

		enum GestureMask : std::int32_t
		{
			kMTG_None = 0,
			kMTG_Pan = 1 << 0,
			kMTG_Zoom = 1 << 1,
			kMTG_Rotate = 1 << 2,
			kMTG_Swipe = 1 << 3
		};

		MultitouchInterface()
			: State(STATE_TYPE)
		{
			// REL::EmplaceVtable(this);
		}

		~MultitouchInterface() override; // 01

		// add
		virtual std::uint32_t GetMaxTouchPoints() const = 0;
		virtual std::uint32_t GetSupportedGesturesMask() const = 0;
		virtual bool SetMultitouchInputMode(MultitouchInputMode a_inputMode) = 0;
	};
}
