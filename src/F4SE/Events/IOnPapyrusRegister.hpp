#pragma once

namespace RE::BSScript
{
	class IVirtualMachine;
}

namespace F4SE::Events
{
	class IOnScriptFunctionsRegister
	{
	public:
		IOnScriptFunctionsRegister() noexcept = default;
		virtual ~IOnScriptFunctionsRegister() noexcept = default;

		IOnScriptFunctionsRegister(const IOnScriptFunctionsRegister&) noexcept = default;
		IOnScriptFunctionsRegister(IOnScriptFunctionsRegister&&) noexcept = default;

		auto operator=(const IOnScriptFunctionsRegister&) noexcept -> IOnScriptFunctionsRegister& = default;
		auto operator=(IOnScriptFunctionsRegister&&) noexcept -> IOnScriptFunctionsRegister& = default;

		virtual void OnScriptFunctionsRegister(RE::BSScript::IVirtualMachine& a_vm) = 0;
	};
}
