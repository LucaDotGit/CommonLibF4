#include "RE/C/ConsoleLog.hpp"

#include "RE/C/Console.hpp"
#include "RE/U/UI.hpp"

#include "Scaleform/P/Ptr.hpp"

namespace RE::Impl
{
	[[nodiscard]] static ::Scaleform::Ptr<Console> GetConsoleMenu()
	{
		const auto* ui = UI::GetSingleton();
		if (!ui) {
			return nullptr;
		}

		return ui->GetMenu<Console>();
	}
}

namespace RE
{
	ConsoleLog* ConsoleLog::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<ConsoleLog**>{ ID::ConsoleLog::Singleton };
		return *SINGLETON;
	}

	BSSpinLock& ConsoleLog::GetAddStringLock()
	{
		static const auto ADD_STRING_LOCK = REL::Relocation<BSSpinLock*>{ ID::ConsoleLog::AddStringLock };
		return *ADD_STRING_LOCK;
	}

	void ConsoleLog::AddString(const char* a_text)
	{
		using FuncType = decltype(&ConsoleLog::AddString);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ConsoleLog::AddString };
		FUNC(this, a_text);
	}

	void ConsoleLog::Print(REX::zstring_view a_text)
	{
		AddString(a_text.data());
	}

	void ConsoleLog::PrintLine(REX::zstring_view a_text)
	{
		const auto newText = REX::Format("{}\n"sv, a_text);
		AddString(newText.data());
	}

	auto ConsoleLog::GetHistory() const -> std::optional<std::string>
	{
		const auto consoleMenu = Impl::GetConsoleMenu();
		if (consoleMenu) {
			return consoleMenu->GetHistory();
		}

		const auto bufferLock = BSAutoLock(GetAddStringLock());
		return std::string{ buffer.begin(), buffer.end() };
	}

	bool ConsoleLog::SetHistory(REX::zstring_view a_history)
	{
		const auto consoleMenu = Impl::GetConsoleMenu();
		if (consoleMenu) {
			return consoleMenu->SetHistory(a_history);
		}

		const auto bufferLock = BSAutoLock(GetAddStringLock());
		buffer = a_history;

		return true;
	}

	bool ConsoleLog::Clear()
	{
		const auto consoleMenu = Impl::GetConsoleMenu();
		if (consoleMenu) {
			return consoleMenu->Clear();
		}

		const auto bufferLock = BSAutoLock(GetAddStringLock());
		buffer.clear();

		return true;
	}
}
