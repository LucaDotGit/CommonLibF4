#include "RE/S/SCRIPT_FUNCTION.hpp"

#include "RE/S/SCRIPT_OUTPUT.hpp"

namespace RE
{
	auto SCRIPT_FUNCTION::Chunk::AsInteger() noexcept -> SCRIPT_FUNCTION::IntegerChunk*
	{
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
		return static_cast<IntegerChunk*>(this);
	}

	auto SCRIPT_FUNCTION::Chunk::AsString() noexcept -> SCRIPT_FUNCTION::StringChunk*
	{
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
		return static_cast<StringChunk*>(this);
	}

	auto SCRIPT_FUNCTION::Chunk::AsInteger() const noexcept -> const SCRIPT_FUNCTION::IntegerChunk*
	{
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
		return static_cast<const IntegerChunk*>(this);
	}

	auto SCRIPT_FUNCTION::Chunk::AsString() const noexcept -> const SCRIPT_FUNCTION::StringChunk*
	{
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
		return static_cast<const StringChunk*>(this);
	}

	auto SCRIPT_FUNCTION::IntegerChunk::GetNext() noexcept -> SCRIPT_FUNCTION::Chunk*
	{
		return static_cast<Chunk*>(this + 1);
	}

	auto SCRIPT_FUNCTION::IntegerChunk::GetNext() const noexcept -> const SCRIPT_FUNCTION::Chunk*
	{
		return static_cast<const Chunk*>(this + 1);
	}

	auto SCRIPT_FUNCTION::IntegerChunk::GetValue() const noexcept -> std::int32_t
	{
		return *std::bit_cast<std::int32_t*>(std::bit_cast<std::uintptr_t>(this) + 1);
	}

	auto SCRIPT_FUNCTION::StringChunk::GetNext() noexcept -> SCRIPT_FUNCTION::Chunk*
	{
		return reinterpret_cast<Chunk*>(static_cast<char*>(str) + length);
	}

	auto SCRIPT_FUNCTION::StringChunk::GetNext() const noexcept -> const SCRIPT_FUNCTION::Chunk*
	{
		return reinterpret_cast<const Chunk*>(static_cast<const char*>(str) + length);
	}

	auto SCRIPT_FUNCTION::StringChunk::GetValue() const noexcept -> std::string_view
	{
		return length ? std::string_view{static_cast<const char*>(str), length} : ""sv;
	}

	auto SCRIPT_FUNCTION::ScriptData::GetChunk() noexcept -> SCRIPT_FUNCTION::Chunk*
	{
		return reinterpret_cast<Chunk*>(this + 1);
	}

	auto SCRIPT_FUNCTION::ScriptData::GetChunk() const noexcept -> const SCRIPT_FUNCTION::Chunk*
	{
		return reinterpret_cast<const Chunk*>(this + 1);
	}

	auto SCRIPT_FUNCTION::ScriptData::GetIntegerChunk() noexcept -> SCRIPT_FUNCTION::IntegerChunk*
	{
		return GetChunk()->AsInteger();
	}

	auto SCRIPT_FUNCTION::ScriptData::GetIntegerChunk() const noexcept -> const SCRIPT_FUNCTION::IntegerChunk*
	{
		return GetChunk()->AsInteger();
	}

	auto SCRIPT_FUNCTION::ScriptData::GetStringChunk() noexcept -> SCRIPT_FUNCTION::StringChunk*
	{
		return GetChunk()->AsString();
	}

	auto SCRIPT_FUNCTION::ScriptData::GetStringChunk() const noexcept -> const SCRIPT_FUNCTION::StringChunk*
	{
		return GetChunk()->AsString();
	}

	auto SCRIPT_FUNCTION::GetConsoleFunctions() -> std::span<SCRIPT_FUNCTION>
	{
		constexpr auto FUNCTION_COUNT_NG =
			static_cast<std::size_t>(std::to_underlying(SCRIPT_OUTPUT::_Console_Count_NG));
		constexpr auto FUNCTION_COUNT_OG =
			static_cast<std::size_t>(std::to_underlying(SCRIPT_OUTPUT::_Console_Count_OG));

		if (F4SE::IsRuntimeAtLeastNG()) {
			static const auto CONSOLE_FUNCTIONS =
				REL::Relocation<std::array<SCRIPT_FUNCTION, FUNCTION_COUNT_NG>*>{ID::SCRIPT_FUNCTION::ConsoleFunctions};
			return {*CONSOLE_FUNCTIONS};
		}

		static const auto CONSOLE_FUNCTIONS =
			REL::Relocation<std::array<SCRIPT_FUNCTION, FUNCTION_COUNT_OG>*>{ID::SCRIPT_FUNCTION::ConsoleFunctions};
		return {*CONSOLE_FUNCTIONS};
	}

	auto SCRIPT_FUNCTION::GetScriptFunctions() -> std::span<SCRIPT_FUNCTION>
	{
		constexpr auto FUNCTION_COUNT = static_cast<std::size_t>(std::to_underlying(SCRIPT_OUTPUT::_Script_Count));

		static const auto SCRIPT_FUNCTIONS =
			REL::Relocation<std::array<SCRIPT_FUNCTION, FUNCTION_COUNT>*>{ID::SCRIPT_FUNCTION::ScriptFunctions};
		return {*SCRIPT_FUNCTIONS};
	}

	auto SCRIPT_FUNCTION::GetConsoleFunctionByName(std::string_view a_name) -> SCRIPT_FUNCTION*
	{
		const auto functions = GetConsoleFunctions();

		const auto functionIt =
			std::ranges::find_if(functions, [a_name](const SCRIPT_FUNCTION& a_func) noexcept -> bool {
				return REX::EqualsIgnoreCase(std::string_view(a_func.functionName), a_name);
			});
		if (functionIt == functions.end()) {
			return nullptr;
		}

		return &*functionIt;
	}

	auto SCRIPT_FUNCTION::GetScriptFunctionByName(std::string_view a_name) -> SCRIPT_FUNCTION*
	{
		const auto functions = GetScriptFunctions();

		const auto functionIt =
			std::ranges::find_if(functions, [a_name](const SCRIPT_FUNCTION& a_func) noexcept -> bool {
				return REX::EqualsIgnoreCase(std::string_view(a_func.functionName), a_name);
			});
		if (functionIt == functions.end()) {
			return nullptr;
		}

		return &*functionIt;
	}

	auto SCRIPT_FUNCTION::GetConsoleFunctionByShortName(std::string_view a_name) -> SCRIPT_FUNCTION*
	{
		const auto functions = GetConsoleFunctions();

		const auto functionIt =
			std::ranges::find_if(functions, [a_name](const SCRIPT_FUNCTION& a_func) noexcept -> bool {
				return REX::EqualsIgnoreCase(std::string_view(a_func.shortName), a_name);
			});
		if (functionIt == functions.end()) {
			return nullptr;
		}

		return &*functionIt;
	}

	auto SCRIPT_FUNCTION::GetScriptFunctionByShortName(std::string_view a_name) -> SCRIPT_FUNCTION*
	{
		const auto functions = GetScriptFunctions();

		const auto functionIt =
			std::ranges::find_if(functions, [a_name](const SCRIPT_FUNCTION& a_func) noexcept -> bool {
				return REX::EqualsIgnoreCase(std::string_view(a_func.shortName), a_name);
			});
		if (functionIt == functions.end()) {
			return nullptr;
		}

		return &*functionIt;
	}
}
