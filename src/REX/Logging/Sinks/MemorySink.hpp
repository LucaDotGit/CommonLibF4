#pragma once

#include "REX/Logging/Sinks/IMemorySink.hpp"

namespace REX::Logging
{
	class Context;
}

namespace REX::Logging::Sinks
{
	class MemorySink final : public REX::Logging::Sinks::IMemorySink
	{
	public:
		MemorySink() noexcept = default;
		~MemorySink() noexcept override = default;

		MemorySink(const MemorySink&) = delete;
		MemorySink(MemorySink&&) = delete;

		auto operator=(const MemorySink&) -> MemorySink& = delete;
		auto operator=(MemorySink&&) -> MemorySink& = delete;

		void Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage) override;
	};
}
