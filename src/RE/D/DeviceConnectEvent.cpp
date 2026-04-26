#include "RE/D/DeviceConnectEvent.hpp"

namespace RE
{
	template bool InputEvent::Is<DeviceConnectEvent>() const noexcept;
	template bool InputEvent::IsNot<DeviceConnectEvent>() const noexcept;

	template DeviceConnectEvent* InputEvent::As() noexcept;
	template const DeviceConnectEvent* InputEvent::As() const noexcept;
}
