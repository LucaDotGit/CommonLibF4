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

	bool& Script::GetProcessScripts()
	{
		static const auto PROCESS_SCRIPTS = REL::Relocation<bool*>{ ID::Script::ProcessScripts };
		return *PROCESS_SCRIPTS;
	}

	const char* Script::GetText() const noexcept
	{
		return text;
	}

	void Script::SetText(std::string_view a_text)
	{
		if (text) {
			free(text);
			text = nullptr;
		}

		auto* newText = calloc<char>(a_text.size() + sizeof(char));
		if (!newText) [[unlikely]] {
			throw std::bad_alloc();
		}

		std::copy_n(a_text.data(), a_text.size(), newText);
		text = newText;
	}

	bool Script::ExecuteSingleLineConsoleCommand(std::string_view a_command, TESObjectREFR* a_targetRef, bool a_silent)
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
		auto script = std::unique_ptr<Script>(scriptFactory->Create());

		const auto consoleLogLock = BSAutoLock(ConsoleLog::GetAddStringLock());

		auto& logBuffer = consoleLog->buffer;
		auto tempLogBuffer = a_silent ? logBuffer : BSString();

		if (!a_silent) {
			consoleLog->PrintLine(a_command);
		}

		auto result = true;

		for (const auto linePart : std::ranges::views::split(a_command, COMMAND_SEPARATOR)) {
			const auto line = std::string_view{ linePart.begin(), linePart.end() };

			script->SetText(line);
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

	bool Script::ExecuteMultiLineConsoleCommand(std::string_view a_command, TESObjectREFR* a_targetRef, bool a_silent)
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
		auto script = std::unique_ptr<Script>(scriptFactory->Create());

		const auto consoleLogLock = BSAutoLock(ConsoleLog::GetAddStringLock());

		auto& logBuffer = consoleLog->buffer;
		auto tempLogBuffer = a_silent ? logBuffer : BSString();

		if (!a_silent) {
			consoleLog->PrintLine(a_command);
		}

		script->SetText(a_command);
		script->CompileAndRun(std::addressof(scriptCompiler), a_targetRef);

		if (a_silent) {
			logBuffer = std::move(tempLogBuffer);
		}

		return script->header.isCompiled;
	}

	void Script::CompileAndRunImpl(ScriptCompiler* a_compiler, COMPILER_NAME a_compilerIndex, TESObjectREFR* a_ownerObject)
	{
		using FuncType = decltype(&Script::CompileAndRunImpl);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Script::CompileAndRunImpl };
		std::invoke(FUNC, this, a_compiler, a_compilerIndex, a_ownerObject);
	}
}
