#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/C/COMPILER_NAME.hpp"
#include "RE/S/SCRIPT_HEADER.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class SCRIPT_FUNCTION;
	class SCRIPT_PARAMETER;
	class SCRIPT_REFERENCED_OBJECT;
	class ScriptCompiler;
	class ScriptLocals;
	class ScriptVariable;

	class __declspec(novtable) Script
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::Script };
		inline static constexpr auto VTABLE{ VTABLE::TESForm };
		inline static constexpr auto FORM_TYPE{ FormType::kScript };

		inline static constexpr auto COMMAND_SEPARATOR = ';';

		void CompileAndRun(ScriptCompiler* a_compiler, TESObjectREFR* a_ownerObject = nullptr, COMPILER_NAME a_compilerIndex = COMPILER_NAME::kSystemWindow);
		[[nodiscard]] static bool& GetProcessScripts();
		[[nodiscard]] const char* GetText() const noexcept;
		void SetText(std::string_view a_text);

		static bool ExecuteSingleLineConsoleCommand(std::string_view a_command, TESObjectREFR* a_targetRef = nullptr, bool a_silent = false);
		static bool ExecuteMultiLineConsoleCommand(std::string_view a_command, TESObjectREFR* a_targetRef = nullptr, bool a_silent = false);

		template <class... Args>
		static bool ParseParameters(const SCRIPT_PARAMETER* a_parameters, const char* a_compiledParams, std::uint32_t& a_offset, TESObjectREFR* a_refObject, TESObjectREFR* a_container, Script* a_script, ScriptLocals* a_scriptLocals, Args... a_args)
			requires((std::is_pointer_v<Args> && ...))
		{
			using FuncType = decltype(&Script::ParseParameters<Args...>);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Script::ParseParameters };
			return std::invoke(FUNC, a_parameters, a_compiledParams, a_offset, a_refObject, a_container, a_script, a_scriptLocals, a_args...);
		}

		void CompileAndRunImpl(ScriptCompiler* a_compiler, COMPILER_NAME a_compilerIndex, TESObjectREFR* a_ownerObject);

		// members
		SCRIPT_HEADER header;								// 20
		char* text;											// 38
		std::byte* data;									// 40
		REX::Float32 profilerTimer;							// 48
		REX::Float32 questScriptDelay;						// 4C
		REX::Float32 questScriptGetSecondsBuffer;			// 50
		TESQuest* parentQuest;								// 58
		BSSimpleList<SCRIPT_REFERENCED_OBJECT*> refObjects; // 60
		BSSimpleList<ScriptVariable*> variables;			// 70
	};
	static_assert(sizeof(Script) == 0x80);
}
