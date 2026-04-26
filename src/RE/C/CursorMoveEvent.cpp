#include "RE/C/CursorMoveEvent.hpp"

namespace RE
{
	template bool InputEvent::Is<CursorMoveEvent>() const noexcept;
	template bool InputEvent::IsNot<CursorMoveEvent>() const noexcept;

	template CursorMoveEvent* InputEvent::As() noexcept;
	template const CursorMoveEvent* InputEvent::As() const noexcept;
}
