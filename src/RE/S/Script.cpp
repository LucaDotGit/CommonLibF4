#include "RE/S/Script.hpp"

#include "RE/B/BSSpinLock.hpp"
#include "RE/C/COMPILER_NAME.hpp"
#include "RE/C/ConcreteFormFactory.hpp"
#include "RE/C/ConsoleLog.hpp"
#include "RE/S/ScriptCompiler.hpp"

namespace RE
{
	void Script::CompileAndRun(ScriptCompiler* a_compiler, TESObjectREFR* a_ownerObject, COMPILER_NAME a_compilerIndex)
	{
		CompileAndRunImpl(a_compiler, a_compilerIndex, a_ownerObject);
	}

	auto Script::GetProcessScripts() noexcept -> bool&
	{
		static const auto PROCESS_SCRIPTS = REL::Relocation<bool*>(ID::Script::ProcessScripts);
		return *PROCESS_SCRIPTS;
	}

	auto Script::GetText() const noexcept -> const char*
	{
		return text;
	}

	void Script::SetText(std::string_view a_text)
	{
		if (text) {
			free(text);
		}

		auto* newText = malloc<char>(a_text.size() + 1);
		if (!newText) [[unlikely]] {
			REX::Throw<std::bad_alloc>();
		}

		std::ranges::copy(a_text, newText);
		newText[a_text.size()] = REX::EMPTY_CHAR<char>;

		text = newText;
	}

	auto Script::ExecuteSingleLineConsoleCommand(std::string_view a_command, TESObjectREFR* a_targetRef, bool a_silent)
		-> bool
	{
		auto* consoleLog = ConsoleLog::GetSingleton();
		if (!consoleLog) {
			return false;
		}

		auto* scriptFactory = ConcreteFormFactory<Script>::GetFormFactory();
		if (!scriptFactory) {
			return false;
		}

		auto scriptCompiler = ScriptCompiler();
		const auto script = std::unique_ptr<Script>(scriptFactory->Create());

		const auto consoleLogLock = BSAutoSpinLock(ConsoleLog::GetAddStringLock());

		auto& logBuffer = consoleLog->buffer;
		auto tempLogBuffer = a_silent ? logBuffer : BSString();

		if (!a_silent) {
			consoleLog->PrintLine("{}"sv, a_command);
		}

		auto result = true;

		for (const auto element : std::ranges::views::split(a_command, COMMAND_SEPARATOR)) {
			const auto elementView = std::string_view{element.begin(), element.end()};

			script->SetText(elementView);
			script->CompileAndRun(std::addressof(scriptCompiler), a_targetRef);

			if (!script->header.isCompiled) {
				result = false;
				break;
			}
		}

		if (a_silent) {
			logBuffer = std::move(tempLogBuffer);
		}

		return result;
	}

	auto Script::ExecuteMultiLineConsoleCommand(std::string_view a_command, TESObjectREFR* a_targetRef, bool a_silent)
		-> bool
	{
		auto* consoleLog = ConsoleLog::GetSingleton();
		if (!consoleLog) {
			return false;
		}

		auto* scriptFactory = ConcreteFormFactory<Script>::GetFormFactory();
		if (!scriptFactory) {
			return false;
		}

		auto scriptCompiler = ScriptCompiler();
		const auto script = std::unique_ptr<Script>(scriptFactory->Create());

		const auto consoleLogLock = BSAutoSpinLock(ConsoleLog::GetAddStringLock());

		auto& logBuffer = consoleLog->buffer;
		auto tempLogBuffer = a_silent ? logBuffer : BSString();

		if (!a_silent) {
			consoleLog->PrintLine("{}"sv, a_command);
		}

		script->SetText(a_command);
		script->CompileAndRun(std::addressof(scriptCompiler), a_targetRef);

		if (a_silent) {
			logBuffer = std::move(tempLogBuffer);
		}

		return script->header.isCompiled;
	}

	void Script::CompileAndRunImpl(
		ScriptCompiler* a_compiler,
		COMPILER_NAME a_compilerIndex,
		TESObjectREFR* a_ownerObject)
	{
		using FuncType = decltype(&Script::CompileAndRunImpl);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Script::CompileAndRunImpl);
		std::invoke(FUNC, this, a_compiler, a_compilerIndex, a_ownerObject);
	}
}
