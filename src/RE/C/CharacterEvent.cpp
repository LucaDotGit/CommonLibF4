#include "RE/C/CharacterEvent.hpp"

namespace RE
{
	template bool InputEvent::Is<CharacterEvent>() const noexcept;
	template bool InputEvent::IsNot<CharacterEvent>() const noexcept;

	template CharacterEvent* InputEvent::As() noexcept;
	template const CharacterEvent* InputEvent::As() const noexcept;
}
