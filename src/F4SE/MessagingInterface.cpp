#include "F4SE/MessagingInterface.hpp"

#include "F4SE/Api.hpp"
#include "F4SE/Core.hpp"
#include "REX/Macros.hpp"
#include "REX/Message.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace F4SE::Impl
{
	namespace
	{
		class F4SEMessagingInterface final
		{
		public:
			F4SEMessagingInterface() = delete;
			~F4SEMessagingInterface() = delete;

			F4SEMessagingInterface(const F4SEMessagingInterface&) = delete;
			F4SEMessagingInterface(F4SEMessagingInterface&&) = delete;

			auto operator=(const F4SEMessagingInterface&) -> F4SEMessagingInterface& = delete;
			auto operator=(F4SEMessagingInterface&&) -> F4SEMessagingInterface& = delete;

			F4SE::InterfaceVersion interfaceVersion;
			bool(F4SE_API* registerListener)(std::uint32_t, const char*, F4SE::MessagingInterface::EventCallback*);
			bool(F4SE_API* dispatch)(F4SE::PluginHandle, std::uint32_t, void*, std::uint32_t, const char*);
			void*(F4SE_API* getEventDispatcher)(F4SE::PluginHandle);
		};

		[[nodiscard]] [[REX_ALWAYS_INLINE]]
		auto GetProxy(const MessagingInterface& a_interface) noexcept -> const F4SEMessagingInterface&
		{
			return reinterpret_cast<const F4SEMessagingInterface&>(a_interface);
		}
	}
}

namespace F4SE
{
	auto MessagingInterface::GetVersion() const noexcept -> F4SE::InterfaceVersion
	{
		return Impl::GetProxy(*this).interfaceVersion;
	}

	void MessagingInterface::RegisterListener(REX::NotNull<REX::Observer<EventCallback*>> a_handler) const
	{
		constexpr auto SENDER_NAME = "F4SE"sv;

		if (!RegisterListener(a_handler, SENDER_NAME.data())) [[unlikely]] {
			REX::Fail(R"(Failed to register messaging listener for sender "{}".)"sv, SENDER_NAME);
		}
	}

	auto MessagingInterface::RegisterListener(
		REX::NotNull<REX::Observer<EventCallback*>> a_handler,
		const char* a_sender) const -> bool
	{
		return Impl::GetProxy(*this).registerListener(F4SE::GetPluginHandle(), a_sender, a_handler.get());
	}

	auto MessagingInterface::Dispatch(
		MessageType a_messageType,
		pointer a_data,
		size_type a_dataSize,
		const char* a_receiver) const -> bool
	{
		return Impl::GetProxy(*this).dispatch(
			F4SE::GetPluginHandle(),
			std::to_underlying(a_messageType),
			a_data,
			a_dataSize,
			a_receiver);
	}

	auto MessagingInterface::GetEventDispatcher(std::uint32_t a_dispatcherID) const -> REX::Observer<void*>
	{
		return Impl::GetProxy(*this).getEventDispatcher(a_dispatcherID);
	}
}
