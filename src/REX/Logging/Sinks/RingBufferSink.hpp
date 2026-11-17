#pragma once

#include "REX/Logging/Sinks/IMemorySink.hpp"

namespace REX::Logging
{
	class Context;
}

namespace REX::Logging::Sinks
{
	class RingBufferSink final : public REX::Logging::Sinks::IMemorySink
	{
	public:
		RingBufferSink() noexcept;
		explicit RingBufferSink(std::size_t a_maxMessageCount);

		~RingBufferSink() noexcept override;

		RingBufferSink(const RingBufferSink&) = delete;
		RingBufferSink(RingBufferSink&&) = delete;

		auto operator=(const RingBufferSink&) -> RingBufferSink& = delete;
		auto operator=(RingBufferSink&&) -> RingBufferSink& = delete;

		[[nodiscard]]
		auto GetMaxMessageCount() const noexcept
		{
			return _maxMessageCount;
		}

		void Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage) override;

	private:
		std::size_t _maxMessageCount;
	};
}
