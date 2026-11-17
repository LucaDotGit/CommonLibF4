#include "REX/Logging/Sinks/NullSink.hpp"

namespace REX::Logging::Sinks
{
	void NullSink::Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage)
	{
		std::ignore = a_context;
		std::ignore = a_formattedMessage;
	}

	void NullSink::Flush()
	{
		return;
	}
}
