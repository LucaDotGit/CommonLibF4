#pragma once

#include "Scaleform/G/GFx_State.hpp"

namespace Scaleform::GFx
{
	class Movie;
	class Value;

	class __declspec(novtable) ExternalInterface
		: public State // 00
	{
	public:
		inline static constexpr auto STATE_TYPE{ StateType::kExternalInterface };

		ExternalInterface()
			: State(STATE_TYPE)
		{
		}

		~ExternalInterface() override; // 00

		// add
		virtual void Callback(Movie* a_movieView, const char* a_methodName, const Value* a_args, std::uint32_t a_numArgs) = 0; // 01
	};
	static_assert(sizeof(ExternalInterface) == 0x18);
}
