#pragma once

#include "Scaleform/G/GFx_LogBase.hpp"
#include "Scaleform/G/GFx_State.hpp"
#include "Scaleform/L/Log.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace Scaleform::GFx
{
	class __declspec(novtable) LogState
		: public State,			   // 00
		  public LogBase<LogState> // 18
	{
	public:
		inline static constexpr auto STATE_TYPE{ StateType::kLog };

		LogState()
			: State(STATE_TYPE)
		{
		}

		~LogState() override; // 01

		// members
		Scaleform::Ptr<Scaleform::Log> log; // 20
	};
	static_assert(sizeof(LogState) == 0x28);
}
