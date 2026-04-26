#include "RE/T/ThumbstickEvent.hpp"

namespace RE
{
	template bool InputEvent::Is<ThumbstickEvent>() const noexcept;
	template bool InputEvent::IsNot<ThumbstickEvent>() const noexcept;

	template ThumbstickEvent* InputEvent::As() noexcept;
	template const ThumbstickEvent* InputEvent::As() const noexcept;
}
