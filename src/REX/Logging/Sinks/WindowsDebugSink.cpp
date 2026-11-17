#include "REX/Logging/Sinks/WindowsDebugSink.hpp"

#include "REX/W32/KERNEL32.hpp"

namespace REX::Logging::Sinks
{
	void WindowsDebugSink::Log(
		[[maybe_unused]] const REX::Logging::Context& a_context,
		std::string_view a_formattedMessage)
	{
		REX::W32::OutputDebugStringA(a_formattedMessage.data());
	}

	void WindowsDebugSink::Flush()
	{
		return;
	}
}
