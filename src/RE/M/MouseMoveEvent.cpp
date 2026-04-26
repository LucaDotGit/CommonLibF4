#include "RE/M/MouseMoveEvent.hpp"

namespace RE
{
	template bool InputEvent::Is<MouseMoveEvent>() const noexcept;
	template bool InputEvent::IsNot<MouseMoveEvent>() const noexcept;

	template MouseMoveEvent* InputEvent::As() noexcept;
	template const MouseMoveEvent* InputEvent::As() const noexcept;
}
