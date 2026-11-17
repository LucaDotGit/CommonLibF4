#include "RE/C/ConsoleLog.hpp"

#include "RE/B/BSSpinLock.hpp"
#include "RE/C/Console.hpp"
#include "RE/U/UI.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace RE::Impl
{
	namespace
	{
		[[nodiscard]]
		auto GetConsoleMenu() -> Scaleform::Ptr<Console>
		{
			const auto* ui = UI::GetSingleton();
			if (!ui) {
				return nullptr;
			}

			return ui->GetMenu<Console>();
		}
	}
}

namespace RE
{
	auto ConsoleLog::GetSingleton() noexcept -> ConsoleLog*
	{
		static const auto SINGLETON = REL::Relocation<ConsoleLog**>(ID::ConsoleLog::Singleton);
		return *SINGLETON;
	}

	auto ConsoleLog::GetAddStringLock() noexcept -> BSSpinLock&
	{
		static const auto ADD_STRING_LOCK = REL::Relocation<BSSpinLock*>(ID::ConsoleLog::AddStringLock);
		return *ADD_STRING_LOCK;
	}

	void ConsoleLog::AddString(const char* a_message)
	{
		using FuncType = decltype(&ConsoleLog::AddString);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ConsoleLog::AddString);
		std::invoke(FUNC, this, a_message);
	}

	void ConsoleLog::Print(std::string_view a_message)
	{
		AddString(a_message.data());
	}

	void ConsoleLog::PrintLine(std::string_view a_message)
	{
		auto formatStorage = REX::StaticString<REX::MESSAGE_BUFFER_SIZE>();
		auto formatRessource = std::pmr::monotonic_buffer_resource{formatStorage.data(), formatStorage.size()};
		auto formatBuffer = std::pmr::string(std::addressof(formatRessource));

		formatBuffer.reserve(a_message.size() + 1);
		formatBuffer.append(a_message);
		formatBuffer.push_back(REX::NEWLINE_CHAR<char>);

		AddString(formatBuffer.data());
	}

	auto ConsoleLog::GetHistory() const -> std::optional<std::string>
	{
		const auto consoleMenu = Impl::GetConsoleMenu();
		if (consoleMenu) {
			return consoleMenu->GetHistory();
		}

		const auto bufferLock = BSAutoSpinLock(GetAddStringLock());
		return std::string{buffer.begin(), buffer.end()};
	}

	auto ConsoleLog::SetHistory(REX::ZStringView a_history) -> bool
	{
		const auto consoleMenu = Impl::GetConsoleMenu();
		if (consoleMenu) {
			return consoleMenu->SetHistory(a_history);
		}

		const auto bufferLock = BSAutoSpinLock(GetAddStringLock());
		buffer = a_history;

		return true;
	}

	auto ConsoleLog::Clear() -> bool
	{
		const auto consoleMenu = Impl::GetConsoleMenu();
		if (consoleMenu) {
			return consoleMenu->Clear();
		}

		const auto bufferLock = BSAutoSpinLock(GetAddStringLock());
		buffer.clear();

		return true;
	}
}
