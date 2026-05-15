#include "RE/H/hkVisualDebugger.hpp"

// IWYU pragma: begin_keep
#include "RE/H/hkStringPtr.hpp"
#include "RE/H/hkVisualDebuggerClient.hpp"
#include "RE/H/hkVisualDebuggerTrackedObject.hpp"
// IWYU pragma: end_keep

namespace RE
{
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
	hkVisualDebugger::hkVisualDebugger(const hkArray<hkProcessContext*>& a_contexts, const hkVtableClassRegistry* a_classReg)
	{
		using FuncType = void (hkVisualDebugger::*)(const hkArray<hkProcessContext*>&, const hkVtableClassRegistry*);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::hkVisualDebugger::ctor };
		std::invoke(FUNC, this, a_contexts, a_classReg);
	}

	void hkVisualDebugger::AddContext(hkProcessContext* a_context)
	{
		using FuncType = decltype(&hkVisualDebugger::AddContext);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::hkVisualDebugger::AddContext };
		std::invoke(FUNC, this, a_context);
	}

	void hkVisualDebugger::AddDefaultProcess(const char* a_name)
	{
		using FuncType = decltype(&hkVisualDebugger::AddDefaultProcess);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::hkVisualDebugger::AddDefaultProcess };
		std::invoke(FUNC, this, a_name);
	}

	void hkVisualDebugger::Serve(std::uint32_t a_port)
	{
		using FuncType = decltype(&hkVisualDebugger::Serve);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::hkVisualDebugger::Serve };
		std::invoke(FUNC, this, a_port);
	}

	void hkVisualDebugger::Shutdown()
	{
		using FuncType = decltype(&hkVisualDebugger::Shutdown);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::hkVisualDebugger::Shutdown };
		std::invoke(FUNC, this);
	}
}
