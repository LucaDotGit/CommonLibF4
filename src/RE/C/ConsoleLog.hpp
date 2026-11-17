#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSString.hpp"
#include "RE/B/BSTSingleton.hpp"

namespace RE
{
	class ConsoleLog : public BSTSingletonSDM<ConsoleLog> // 0x00
	{
	public:
		[[nodiscard]]
		static auto GetSingleton() noexcept -> ConsoleLog*;

		[[nodiscard]]
		static auto GetAddStringLock() noexcept -> BSSpinLock&;

		void AddString(const char* a_message);

		void Print(std::string_view a_message);
		void PrintLine(std::string_view a_message);

		template <class... Args>
		void Print(REX::FormatString<Args...> a_format, Args&&... a_args)
			requires((REX::formattable<Args, char> && ...))
		{
			auto formatStorage = REX::StaticString<REX::MESSAGE_BUFFER_SIZE>();
			auto formatRessource = std::pmr::monotonic_buffer_resource{formatStorage.data(), formatStorage.size()};
			auto formatBuffer = std::pmr::string(std::addressof(formatRessource));

			REX::FormatTo(std::back_inserter(formatBuffer), a_format, std::forward<Args>(a_args)...);

			Print(formatBuffer);
		}

		template <class... Args>
		void PrintLine(REX::FormatString<Args...> a_format, Args&&... a_args)
			requires((REX::formattable<Args, char> && ...))
		{
			auto formatStorage = REX::StaticString<REX::MESSAGE_BUFFER_SIZE>();
			auto formatRessource = std::pmr::monotonic_buffer_resource{formatStorage.data(), formatStorage.size()};
			auto formatBuffer = std::pmr::string(std::addressof(formatRessource));

			REX::FormatTo(std::back_inserter(formatBuffer), a_format, std::forward<Args>(a_args)...);
			formatBuffer.push_back(REX::NEWLINE_CHAR<char>);

			Print(formatBuffer);
		}

		[[nodiscard]]
		auto GetHistory() const -> std::optional<std::string>;
		auto SetHistory(REX::ZStringView a_history) -> bool;
		auto Clear() -> bool;

		// members
		BSString buffer;		// 0x08
		bool useConsoleOverlay; // 0x18
	};

	static_assert(sizeof(ConsoleLog) == 0x20);
}
