#include "RE/K/KinectEvent.hpp"

namespace RE
{
	template bool InputEvent::Is<KinectEvent>() const noexcept;
	template bool InputEvent::IsNot<KinectEvent>() const noexcept;

	template KinectEvent* InputEvent::As() noexcept;
	template const KinectEvent* InputEvent::As() const noexcept;
}
