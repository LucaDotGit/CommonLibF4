#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/QueryInterface.hpp"

#include "RE/CoreTypes.hpp"

#include "REX/NotNull.hpp"
#include "REX/Own.hpp"

namespace RE::BSScript
{
	class IVirtualMachine;
}

namespace F4SE
{
	class PapyrusInterface final
	{
	public:
		inline static constexpr auto INTERFACE_ID{ QueryInterface::InterfaceID::kPapyrus };
		inline static constexpr auto INTERFACE_VERSION{ 2ui32 };

		using RegisterFunctions = bool F4SE_API(RE::BSScript::IVirtualMachine* a_vm);
		using RegistrantFunctor = void F4SE_API(RE::BSScript::ObjectHandle a_objectHandle, const char* a_scriptName, const char* a_callbackName, void* a_data);

		PapyrusInterface() = delete;
		~PapyrusInterface() = delete;

		PapyrusInterface(const PapyrusInterface&) = delete;
		PapyrusInterface(PapyrusInterface&&) = delete;

		PapyrusInterface& operator=(const PapyrusInterface&) = delete;
		PapyrusInterface& operator=(PapyrusInterface&&) = delete;

		[[nodiscard]] std::uint32_t GetVersion() const noexcept;

		void Register(REX::NotNull<REX::Observer<RegisterFunctions*>> a_callback) const;
		void GetExternalEventRegistrations(const char* a_eventName, void* a_data, REX::NotNull<REX::Observer<RegistrantFunctor*>> a_functor) const;
	};
	static_assert(std::is_empty_v<PapyrusInterface>);
}
