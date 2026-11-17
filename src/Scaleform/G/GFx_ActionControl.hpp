#pragma once

#include "Scaleform/G/GFx_State.hpp"

namespace Scaleform::GFx
{
	class __declspec(novtable) ActionControl : public State // 0x00
	{
	public:
		inline static constexpr auto STATE_TYPE = StateType::ActionControl;

		enum class ActionControlFlags : std::uint32_t
		{
			None = 0,
			Verbose = 1 << 0,
			ErrorSuppress = 1 << 1,
			LogRootFilenames = 1 << 2,
			LogChildFilenames = 1 << 3,
			LogAllFilenames = LogRootFilenames | LogChildFilenames,
			LongFilenames = 1 << 4
		};

		explicit ActionControl(ActionControlFlags a_actionFlags = ActionControlFlags::LogChildFilenames) :
			State(STATE_TYPE),
			actionFlags(a_actionFlags)
		{
			// REL::EmplaceVtable(this);
		}

		~ActionControl() override; // 0x00

		// members
		REX::EnumSet<ActionControlFlags, std::uint32_t> actionFlags; // 0x18
	};

	static_assert(sizeof(ActionControl) == 0x20);
}
