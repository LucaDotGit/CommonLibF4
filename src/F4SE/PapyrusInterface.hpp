#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/QueryInterface.hpp"
#include "RE/CoreTypes.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace RE::BSScript
{
	class IVirtualMachine;
}

namespace F4SE
{
	class PapyrusInterface final
	{
	public:
		inline static constexpr auto INTERFACE_ID = QueryInterface::InterfaceID::Papyrus;
		inline static constexpr auto INTERFACE_VERSION = static_cast<std::uint32_t>(2);

		using RegisterCallback = bool F4SE_API(RE::BSScript::IVirtualMachine* a_vm);
		using ExternalEventCallback = void F4SE_API(
			RE::BSScript::ObjectHandle a_objectHandle,
			const char* a_scriptName,
			const char* a_callbackName,
			void* a_data);

		PapyrusInterface() = delete;
		~PapyrusInterface() = delete;

		PapyrusInterface(const PapyrusInterface&) = delete;
		PapyrusInterface(PapyrusInterface&&) = delete;

		auto operator=(const PapyrusInterface&) -> PapyrusInterface& = delete;
		auto operator=(PapyrusInterface&&) -> PapyrusInterface& = delete;

		[[nodiscard]]
		auto GetVersion() const noexcept -> F4SE::InterfaceVersion;

		void Register(REX::NotNull<REX::Observer<RegisterCallback*>> a_callback) const;
		void GetExternalEventRegistrations(
			const char* a_eventName,
			void* a_data,
			REX::NotNull<REX::Observer<ExternalEventCallback*>> a_functor) const;
	};

	static_assert(std::is_empty_v<PapyrusInterface>);
}
