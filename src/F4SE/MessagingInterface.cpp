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

	[[nodiscard]] static const F4SEMessagingInterface& GetProxy(const MessagingInterface* a_interface) noexcept
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

	bool MessagingInterface::RegisterListener(REX::NotNull<REX::Observer<EventCallback*>> a_handler) const
	{
		return RegisterListener(a_handler, "F4SE");
	}

	bool MessagingInterface::RegisterListener(REX::NotNull<REX::Observer<EventCallback*>> a_handler, const char* a_sender) const
	{
		const auto result = Impl::GetProxy(this).RegisterListener(F4SE::GetPluginHandle(), a_sender, reinterpret_cast<void*>(a_handler.get()));
		if (!result) [[unlikely]] {
			REX::Fail(R"(Failed to register messaging listener for "{}".)"sv,
				a_sender);
		}

		return result;
	}

	bool MessagingInterface::Dispatch(MessageType a_messageType, std::byte* a_data, std::uint32_t a_dataSize, const char* a_receiver) const
	{
		const auto result = Impl::GetProxy(this).Dispatch(F4SE::GetPluginHandle(), std::to_underlying(a_messageType), a_data, a_dataSize, a_receiver);
		if (!result) [[unlikely]] {
			REX::Fail(R"(Failed to dispatch message to "{}".)"sv,
				a_receiver ? a_receiver : "<all listeners>"sv);
		}

		return result;
	}

	void* MessagingInterface::GetEventDispatcher(std::uint32_t a_dispatcherID) const
	{
		return Impl::GetProxy(this).GetEventDispatcher(a_dispatcherID);
	}
}
