#pragma once

#include "Scaleform/G/GFx_State.hpp"

namespace Scaleform::GFx
{
	class Event;
	class Movie;

	class __declspec(novtable) FSCommandHandler
		: public State // 00
	{
	public:
		inline static constexpr auto STATE_TYPE{ StateType::kFSCommandHandler };

		FSCommandHandler()
			: State(STATE_TYPE)
		{
			// REL::EmplaceVtable(this);
		}

		~FSCommandHandler() override; // 01

		// add
		virtual void HandleEvent(Movie* a_movie, const Event& a_event) = 0;
	};
	static_assert(sizeof(FSCommandHandler) == 0x18);
}
