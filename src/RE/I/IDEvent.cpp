#include "RE/I/IDEvent.hpp"

namespace RE
{
	auto IDEvent::QUserEvent() const -> const BSFixedString&
	{
		static const auto DISABLED_STRING = BSFixedString("DISABLED"sv);
		return disabled ? DISABLED_STRING : strUserEvent;
	}
}
