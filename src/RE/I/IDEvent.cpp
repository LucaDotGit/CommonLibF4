#include "RE/I/IDEvent.hpp"

namespace RE
{
	const BSFixedString& IDEvent::QUserEvent() const
	{
		static const auto DISABLED_STRING = BSFixedString("DISABLED"sv);
		return disabled ? DISABLED_STRING : strUserEvent;
	}
}
