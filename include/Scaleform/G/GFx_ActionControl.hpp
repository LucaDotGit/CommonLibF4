#pragma once

#include "Scaleform/G/GFx_State.hpp"

namespace Scaleform::GFx
{
	class __declspec(novtable) ActionControl
		: public State // 00
	{
	public:
		inline static constexpr auto STATE_TYPE{ StateType::kActionControl };

		enum class ActionControlFlags : std::uint32_t
		{
			kNone = 0,
			kVerbose = 1 << 0,
			kErrorSuppress = 1 << 1,
			kLogRootFilenames = 1 << 2,
			kLogChildFilenames = 1 << 3,
			kLogAllFilenames = kLogRootFilenames | kLogChildFilenames,
			kLongFilenames = 1 << 4
		};

		ActionControl(REX::EnumSet<ActionControlFlags, std::uint32_t> a_actionFlags = ActionControlFlags::kLogChildFilenames)
			: State(STATE_TYPE),
			  actionFlags(a_actionFlags)
		{
			// REL::EmplaceVtable(this);
		}

		~ActionControl() override; // 01

		// members
		REX::EnumSet<ActionControlFlags, std::uint32_t> actionFlags; // 18
	};
	static_assert(sizeof(ActionControl) == 0x20);
}
