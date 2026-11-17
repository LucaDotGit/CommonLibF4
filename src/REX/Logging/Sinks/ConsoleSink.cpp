#include "REX/Logging/Sinks/ConsoleSink.hpp"

namespace REX::Logging::Sinks
{
	void ConsoleSink::Log([[maybe_unused]] const REX::Logging::Context& a_context, std::string_view a_formattedMessage)
	{
		REX::PrintLine(std::cout, "{}"sv, a_formattedMessage);
	}

	void ConsoleSink::Flush()
	{
		std::cout.flush();
	}
}
