#pragma once

#include "REX/Logging/ISink.hpp"

namespace REX::Logging
{
	class Context;
}

namespace REX::Logging::Sinks
{
	class ConsoleSink final : public REX::Logging::ISink
	{
	public:
		ConsoleSink() noexcept = default;
		~ConsoleSink() noexcept override = default;

		ConsoleSink(const ConsoleSink&) = delete;
		ConsoleSink(ConsoleSink&&) = delete;

		auto operator=(const ConsoleSink&) -> ConsoleSink& = delete;
		auto operator=(ConsoleSink&&) -> ConsoleSink& = delete;

		void Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage) override;
		void Flush() override;
	};
}
