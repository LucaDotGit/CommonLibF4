#pragma once

#include "RE/I/IDEvent.hpp"

namespace RE
{
	class __declspec(novtable) MouseMoveEvent : public IDEvent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::MouseMoveEvent;
		inline static constexpr const auto& VTABLE = VTABLE::MouseMoveEvent;
		inline static constexpr auto INPUT_TYPE = INPUT_EVENT_TYPE::MouseMove;

		~MouseMoveEvent() override = default; // 0x00

		// members
		std::int32_t mouseInputX{0}; // 0x38
		std::int32_t mouseInputY{0}; // 0x3C
	};

	static_assert(sizeof(MouseMoveEvent) == 0x40);
}
