#pragma once

#include "REX/Logging/ISink.hpp"

namespace REX::Logging
{
	class Context;
}

namespace REX::Logging::Sinks
{
	class WindowsDebugSink : public REX::Logging::ISink
	{
	public:
		WindowsDebugSink() noexcept = default;
		~WindowsDebugSink() noexcept override = default;

		WindowsDebugSink(const WindowsDebugSink&) = delete;
		WindowsDebugSink(WindowsDebugSink&&) = delete;

		auto operator=(const WindowsDebugSink&) -> WindowsDebugSink& = delete;
		auto operator=(WindowsDebugSink&&) -> WindowsDebugSink& = delete;

		void Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage) override;
		void Flush() override;
	};
}
