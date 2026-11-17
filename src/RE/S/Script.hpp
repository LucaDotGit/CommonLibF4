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

	class __declspec(novtable) Script : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::Script;
		inline static constexpr const auto& VTABLE = VTABLE::TESForm;
		inline static constexpr auto FORM_TYPE = FormType::Script;

		inline static constexpr auto COMMAND_SEPARATOR = ';';

		void CompileAndRun(
			ScriptCompiler* a_compiler,
			TESObjectREFR* a_ownerObject = nullptr,
			COMPILER_NAME a_compilerIndex = COMPILER_NAME::SystemWindow);
		[[nodiscard]]
		static auto GetProcessScripts() noexcept -> bool&;
		[[nodiscard]]
		auto GetText() const noexcept -> const char*;
		void SetText(std::string_view a_text);

		static auto ExecuteSingleLineConsoleCommand(
			std::string_view a_command,
			TESObjectREFR* a_targetRef = nullptr,
			bool a_silent = false) -> bool;
		static auto ExecuteMultiLineConsoleCommand(
			std::string_view a_command,
			TESObjectREFR* a_targetRef = nullptr,
			bool a_silent = false) -> bool;

		template <class... Args>
		static auto ParseParameters(
			const SCRIPT_PARAMETER* a_parameters,
			const char* a_compiledParams,
			std::uint32_t& a_offset,
			TESObjectREFR* a_refObject,
			TESObjectREFR* a_container,
			Script* a_script,
			ScriptLocals* a_scriptLocals,
			Args... a_args) -> bool
			requires((REX::pointer<Args> && ...))
		{
			using FuncType = decltype(&Script::ParseParameters<Args...>);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Script::ParseParameters);
			return std::invoke(
				FUNC,
				a_parameters,
				a_compiledParams,
				a_offset,
				a_refObject,
				a_container,
				a_script,
				a_scriptLocals,
				a_args...);
		}

		void CompileAndRunImpl(ScriptCompiler* a_compiler, COMPILER_NAME a_compilerIndex, TESObjectREFR* a_ownerObject);

		// members
		SCRIPT_HEADER header;								// 0x20
		char* text;											// 0x38
		std::byte* data;									// 0x40
		REX::Float32 profilerTimer;							// 0x48
		REX::Float32 questScriptDelay;						// 0x4C
		REX::Float32 questScriptGetSecondsBuffer;			// 0x50
		TESQuest* parentQuest;								// 0x58
		BSSimpleList<SCRIPT_REFERENCED_OBJECT*> refObjects; // 0x60
		BSSimpleList<ScriptVariable*> variables;			// 0x70
	};

	static_assert(sizeof(Script) == 0x80);
}
