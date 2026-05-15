#include "F4SE/MessagingInterface.hpp"

#include "F4SE/API.hpp"

namespace F4SE::Impl
{
	struct F4SEMessagingInterface final
	{
		std::uint32_t interfaceVersion;
		bool(F4SE_API* RegisterListener)(std::uint32_t, const char*, void*);
		bool(F4SE_API* Dispatch)(std::uint32_t, std::uint32_t, void*, std::uint32_t, const char*);
		void*(F4SE_API* GetEventDispatcher)(std::uint32_t);
	};

	[[nodiscard]] __forceinline static const F4SEMessagingInterface& GetProxy(const MessagingInterface* a_interface) noexcept
	{
		return reinterpret_cast<const F4SEMessagingInterface&>(*a_interface);
	}
}

namespace F4SE
{
	std::uint32_t MessagingInterface::GetVersion() const noexcept
	{
		return Impl::GetProxy(this).interfaceVersion;
	}

	void MessagingInterface::RegisterListener(REX::NotNull<REX::Observer<EventCallback*>> a_handler) const
	{
		constexpr auto SENDER_NAME = "F4SE"sv;

		if (!RegisterListener(a_handler, SENDER_NAME.data())) [[unlikely]] {
			REX::Fail(R"(Failed to register messaging listener for sender "{}".)"sv,
				SENDER_NAME);
		}
	}

	bool MessagingInterface::RegisterListener(REX::NotNull<REX::Observer<EventCallback*>> a_handler, const char* a_sender) const
	{
		return Impl::GetProxy(this).RegisterListener(F4SE::GetPluginHandle(), a_sender, reinterpret_cast<void*>(a_handler.get()));
	}

	bool MessagingInterface::Dispatch(MessageType a_messageType, std::byte* a_data, std::uint32_t a_dataSize, const char* a_receiver) const
	{
		return Impl::GetProxy(this).Dispatch(F4SE::GetPluginHandle(), std::to_underlying(a_messageType), a_data, a_dataSize, a_receiver);
	}

	void* MessagingInterface::GetEventDispatcher(std::uint32_t a_dispatcherID) const
	{
		return Impl::GetProxy(this).GetEventDispatcher(a_dispatcherID);
	}
}
