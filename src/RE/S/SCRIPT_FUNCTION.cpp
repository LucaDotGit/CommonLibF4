#include "RE/S/SCRIPT_FUNCTION.hpp"

#include "RE/S/SCRIPT_OUTPUT.hpp"

namespace RE
{
	auto SCRIPT_FUNCTION::GetConsoleFunctions() -> std::span<SCRIPT_FUNCTION>
	{
		constexpr auto FUNCTION_SIZE_NG = static_cast<std::size_t>(std::to_underlying(SCRIPT_OUTPUT::kConsole_Total_NG));
		constexpr auto FUNCTION_SIZE_OG = static_cast<std::size_t>(std::to_underlying(SCRIPT_OUTPUT::kConsole_Total_OG));

		if (F4SE::IsRuntimeAtLeastNG()) {
			static const auto CONSOLE_FUNCTIONS = REL::Relocation<std::array<SCRIPT_FUNCTION, FUNCTION_SIZE_NG>*>{ ID::SCRIPT_FUNCTION::ConsoleFunctions };
			return { *CONSOLE_FUNCTIONS };
		}

		static const auto CONSOLE_FUNCTIONS = REL::Relocation<std::array<SCRIPT_FUNCTION, FUNCTION_SIZE_OG>*>{ ID::SCRIPT_FUNCTION::ConsoleFunctions };
		return { *CONSOLE_FUNCTIONS };
	}

	auto SCRIPT_FUNCTION::GetScriptFunctions() -> std::span<SCRIPT_FUNCTION>
	{
		constexpr auto FUNCTION_SIZE = static_cast<std::size_t>(std::to_underlying(SCRIPT_OUTPUT::kScript_Total));

		static const auto SCRIPT_FUNCTIONS = REL::Relocation<std::array<SCRIPT_FUNCTION, FUNCTION_SIZE>*>{ ID::SCRIPT_FUNCTION::ScriptFunctions };
		return { *SCRIPT_FUNCTIONS };
	}

	SCRIPT_FUNCTION* SCRIPT_FUNCTION::GetConsoleFunctionByName(std::string_view a_name)
	{
		const auto functions = GetConsoleFunctions();

		const auto functionIt = std::ranges::find_if(functions, [a_name](const SCRIPT_FUNCTION& a_func) noexcept {
			return REX::EqualsIgnoreCase(std::string_view(a_func.functionName), a_name);
		});
		if (functionIt == functions.end()) {
			return nullptr;
		}

		return &*functionIt;
	}

	SCRIPT_FUNCTION* SCRIPT_FUNCTION::GetScriptFunctionByName(std::string_view a_name)
	{
		const auto functions = GetScriptFunctions();

		const auto functionIt = std::ranges::find_if(functions, [a_name](const SCRIPT_FUNCTION& a_func) noexcept {
			return REX::EqualsIgnoreCase(std::string_view(a_func.functionName), a_name);
		});
		if (functionIt == functions.end()) {
			return nullptr;
		}

		return &*functionIt;
	}

	SCRIPT_FUNCTION* SCRIPT_FUNCTION::GetConsoleFunctionByShortName(std::string_view a_name)
	{
		const auto functions = GetConsoleFunctions();

		const auto functionIt = std::ranges::find_if(functions, [a_name](const SCRIPT_FUNCTION& a_func) noexcept {
			return REX::EqualsIgnoreCase(std::string_view(a_func.shortName), a_name);
		});
		if (functionIt == functions.end()) {
			return nullptr;
		}

		return &*functionIt;
	}

	SCRIPT_FUNCTION* SCRIPT_FUNCTION::GetScriptFunctionByShortName(std::string_view a_name)
	{
		const auto functions = GetScriptFunctions();

		const auto functionIt = std::ranges::find_if(functions, [a_name](const SCRIPT_FUNCTION& a_func) noexcept {
			return REX::EqualsIgnoreCase(std::string_view(a_func.shortName), a_name);
		});
		if (functionIt == functions.end()) {
			return nullptr;
		}

		return &*functionIt;
	}
}
