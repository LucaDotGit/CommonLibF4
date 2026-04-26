#pragma once

#include "Scaleform/G/GFx_State.hpp"

namespace Scaleform::GFx
{
	class Event;
	class Movie;

	class __declspec(novtable) UserEventHandler
		: public State // 00
	{
	public:
		inline static constexpr auto STATE_TYPE{ StateType::kUserEventHandler };

		UserEventHandler()
			: State(STATE_TYPE)
		{
		}

		// add
		virtual void HandleEvent(Movie* a_movie, const Event& a_event) = 0;
	};
	static_assert(sizeof(UserEventHandler) == 0x18);
}
