#pragma once

#include "REX/Logging/Context.hpp"
#include "REX/Logging/ISink.hpp"

namespace REX::Logging::Sinks
{
	class IMemorySink : public REX::Logging::ISink
	{
	public:
		class MessageData final
		{
		public:
			REX::Logging::Context context;
			std::string formattedMessage;
		};

		IMemorySink() noexcept = default;
		~IMemorySink() noexcept override = default;

		IMemorySink(const IMemorySink&) = delete;
		IMemorySink(IMemorySink&&) = delete;

		auto operator=(const IMemorySink&) -> IMemorySink& = delete;
		auto operator=(IMemorySink&&) -> IMemorySink& = delete;

		[[nodiscard]]
		auto GetMessageCount() const noexcept -> std::size_t;

		[[nodiscard]]
		auto GetMessages() const -> std::vector<MessageData>;

		void ClearMessages() noexcept;

		void Flush() override;

	protected:
		mutable std::shared_mutex _messageMutex;
		std::vector<MessageData> _messages;
	};
}
