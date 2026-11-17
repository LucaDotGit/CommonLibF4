#pragma once

#include "Scaleform/G/GFx_State.hpp"

namespace Scaleform::GFx
{
	class Event;
	class Movie;

	class __declspec(novtable) FSCommandHandler : public State // 0x00
	{
	public:
		inline static constexpr auto STATE_TYPE = StateType::FSCommandHandler;

		FSCommandHandler() :
			State(STATE_TYPE)
		{
			// REL::EmplaceVtable(this);
		}

		~FSCommandHandler() override; // 0x00

		// add
		virtual void HandleEvent(Movie* a_movie, const Event& a_event) = 0; // 0x01
	};

	static_assert(sizeof(FSCommandHandler) == 0x18);
}
