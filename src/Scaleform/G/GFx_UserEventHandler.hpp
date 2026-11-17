#pragma once

#include "Scaleform/G/GFx_State.hpp"

namespace Scaleform::GFx
{
	class Event;
	class Movie;

	class __declspec(novtable) UserEventHandler : public State // 0x00
	{
	public:
		inline static constexpr auto STATE_TYPE = StateType::UserEventHandler;

		UserEventHandler() :
			State(STATE_TYPE)
		{
			// REL::EmplaceVtable(this);
		}

		// add
		virtual void HandleEvent(Movie* a_movie, const Event& a_event) = 0;
	};

	static_assert(sizeof(UserEventHandler) == 0x18);
}
