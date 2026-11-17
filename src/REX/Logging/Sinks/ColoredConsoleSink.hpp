#pragma once

#include "REX/Logging/ISink.hpp"

namespace REX::Logging
{
	class Context;
}

namespace REX::Logging::Sinks
{
	class ColoredConsoleSink final : public REX::Logging::ISink
	{
	public:
		ColoredConsoleSink() noexcept = default;
		~ColoredConsoleSink() noexcept override = default;

		ColoredConsoleSink(const ColoredConsoleSink&) = delete;
		ColoredConsoleSink(ColoredConsoleSink&&) = delete;

		auto operator=(const ColoredConsoleSink&) -> ColoredConsoleSink& = delete;
		auto operator=(ColoredConsoleSink&&) -> ColoredConsoleSink& = delete;

		void Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage) override;
		void Flush() override;
	};
}
