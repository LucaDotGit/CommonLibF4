#pragma once

#include "RE/I/IDEvent.hpp"

namespace RE
{
	class __declspec(novtable) MouseMoveEvent
		: public IDEvent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::MouseMoveEvent };
		inline static constexpr auto VTABLE{ VTABLE::MouseMoveEvent };
		inline static constexpr auto INPUT_TYPE{ INPUT_EVENT_TYPE::kMouseMove };

		~MouseMoveEvent() override = default; // 00

		// members
		std::int32_t mouseInputX{ 0 }; // 38
		std::int32_t mouseInputY{ 0 }; // 3C
	};
	static_assert(sizeof(MouseMoveEvent) == 0x40);

	extern template bool InputEvent::Is<MouseMoveEvent>() const noexcept;
	extern template bool InputEvent::IsNot<MouseMoveEvent>() const noexcept;

	extern template MouseMoveEvent* InputEvent::As() noexcept;
	extern template const MouseMoveEvent* InputEvent::As() const noexcept;
}
