#pragma once

#include "REX/Logging/ISink.hpp"

namespace REX::Logging
{
	class Context;
}

namespace REX::Logging::Sinks
{
	class CallbackSink final : public REX::Logging::ISink
	{
	public:
		using CallbackType = void(const REX::Logging::Context& a_context, std::string_view a_formattedMessage) const;

		explicit CallbackSink(REX::NotNull<std::move_only_function<CallbackType>> a_callback) noexcept;
		~CallbackSink() noexcept override;

		CallbackSink(const CallbackSink&) = delete;
		CallbackSink(CallbackSink&&) = delete;

		auto operator=(const CallbackSink&) -> CallbackSink& = delete;
		auto operator=(CallbackSink&&) -> CallbackSink& = delete;

		void Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage) override;
		void Flush() override;

	private:
		REX::NotNull<std::move_only_function<CallbackType>> _callback;
	};
}
