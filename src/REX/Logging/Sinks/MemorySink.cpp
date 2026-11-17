#include "REX/Logging/Sinks/MemorySink.hpp"

#include "REX/Logging/Context.hpp"

namespace REX::Logging::Sinks
{
	void MemorySink::Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage)
	{
		const auto messageLock = std::unique_lock(_messageMutex);
		_messages.emplace_back(a_context, std::string(a_formattedMessage));
	}
}
