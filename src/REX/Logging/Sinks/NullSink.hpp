#pragma once

#include "REX/Logging/ISink.hpp"

namespace REX::Logging
{
	class Context;
}

namespace REX::Logging::Sinks
{
	class NullSink final : public ISink
	{
	public:
		NullSink() noexcept = default;
		~NullSink() noexcept override = default;

		NullSink(const NullSink&) = delete;
		NullSink(NullSink&&) = delete;

		auto operator=(const NullSink&) -> NullSink& = delete;
		auto operator=(NullSink&&) -> NullSink& = delete;

		void Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage) override;
		void Flush() override;
	};
}
