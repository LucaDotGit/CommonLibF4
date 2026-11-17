#include "REX/Logging/Sinks/ColoredConsoleSink.hpp"

#include "REX/Logging/Context.hpp"
#include "REX/Logging/Level.hpp"

namespace REX::Logging::Sinks
{
	void ColoredConsoleSink::Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage)
	{
		const auto levelColorCode = REX::Logging::GetAnsiColorCodeForLevel(a_context.GetLevel());
		const auto resetColorCode = REX::Logging::GetAnsiColorCodeForLevel(REX::Logging::Level::None);

		REX::PrintLine(std::cout, "{}{}{}"sv, levelColorCode, a_formattedMessage, resetColorCode);
	}

	void ColoredConsoleSink::Flush()
	{
		std::cout.flush();
	}
}
