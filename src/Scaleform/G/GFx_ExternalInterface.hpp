#pragma once

#include "Scaleform/G/GFx_State.hpp"

namespace Scaleform::GFx
{
	class Movie;
	class Value;

	class __declspec(novtable) ExternalInterface : public State // 0x00
	{
	public:
		inline static constexpr auto STATE_TYPE = StateType::ExternalInterface;

		ExternalInterface() :
			State(STATE_TYPE)
		{
			// REL::EmplaceVtable(this);
		}

		~ExternalInterface() override; // 0x00

		// add
		virtual void Callback(
			Movie* a_movieView,
			const char* a_methodName,
			const Value* a_args,
			std::uint32_t a_numArgs) = 0; // 0x01
	};

	static_assert(sizeof(ExternalInterface) == 0x18);
}
