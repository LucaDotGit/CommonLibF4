#pragma once

#include "Scaleform/G/GFx_LogBase.hpp"
#include "Scaleform/G/GFx_State.hpp"
#include "Scaleform/L/Log.hpp"
#include "Scaleform/L/LogMessageId.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace Scaleform::GFx
{
	class __declspec(novtable) LogState :
		public State,			 // 0x00
		public LogBase<LogState> // 0x18
	{
	public:
		inline static constexpr auto STATE_TYPE = StateType::Log;

		LogState() :
			State(STATE_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~LogState() override; // 0x00

		// add
		virtual void LogMessageVarg(LogMessageId a_messageId, const char* a_format, std::va_list a_args); // 0x02

		// members
		Scaleform::Ptr<Scaleform::Log> log; // 0x20
	};

	static_assert(sizeof(LogState) == 0x28);
}
