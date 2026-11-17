#include "REX/Logging/Sinks/RingBufferSink.hpp"

#include "REX/Logging/Context.hpp"

namespace REX::Logging::Sinks
{
	RingBufferSink::RingBufferSink() noexcept :
		_maxMessageCount(0)
	{
	}

	RingBufferSink::RingBufferSink(std::size_t a_maxMessageCount) :
		_maxMessageCount(a_maxMessageCount)
	{
		_messages.reserve(a_maxMessageCount);
	}

	RingBufferSink::~RingBufferSink() noexcept = default;

	void RingBufferSink::Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage)
	{
		const auto messageLock = std::unique_lock(_messageMutex);

		if (_maxMessageCount > 0 && _messages.size() >= _maxMessageCount) {
			_messages.erase(_messages.begin());
		}

		_messages.emplace_back(a_context, std::string(a_formattedMessage));
	}
}
