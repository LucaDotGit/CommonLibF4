#include "REX/Logging/Sinks/IMemorySink.hpp"

namespace REX::Logging::Sinks
{
	auto IMemorySink::GetMessageCount() const noexcept -> std::size_t
	{
		const auto messageLock = std::shared_lock(_messageMutex);
		return _messages.size();
	}

	auto IMemorySink::GetMessages() const -> std::vector<MessageData>
	{
		const auto messageLock = std::shared_lock(_messageMutex);
		return _messages;
	}

	void IMemorySink::ClearMessages() noexcept
	{
		const auto messageLock = std::unique_lock(_messageMutex);
		_messages.clear();
	}

	void IMemorySink::Flush()
	{
		return;
	}
}
