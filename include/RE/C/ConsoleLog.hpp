#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSStringT.hpp"
#include "RE/B/BSTSingleton.hpp"

namespace RE
{
	class ConsoleLog
		: public BSTSingletonSDM<ConsoleLog> // 00
	{
	public:
		[[nodiscard]] static ConsoleLog* GetSingleton();

		[[nodiscard]] static BSSpinLock& GetAddStringLock();

		void AddString(const char* a_text);

		void Print(REX::zstring_view a_text);
		void PrintLine(REX::zstring_view a_text);

		template <class... Args>
		void Print(REX::FormatString<Args...> a_format, Args&&... a_args)
			requires((REX::formattable<Args, char> && ...))
		{
			const auto formatData = REX::FixedFormat(a_format, std::forward<Args>(a_args)...);
			Print(REX::zstring_view{ formatData.buffer.data(), formatData.size });
		}

		template <class... Args>
		void PrintLine(REX::FormatString<Args...> a_format, Args&&... a_args)
			requires((REX::formattable<Args, char> && ...))
		{
			auto formatData = REX::FixedFormat(a_format, std::forward<Args>(a_args)...);
			auto formatResult = REX::FixedFormat(std::span(formatData.buffer), "{}\n"sv, std::string_view{ formatData.buffer.data(), formatData.size });

			Print(formatResult);
		}

		[[nodiscard]] auto GetHistory() const
			-> std::optional<std::string>;
		bool SetHistory(REX::zstring_view a_history);
		bool Clear();

		// members
		BSString buffer;		// 08
		bool useConsoleOverlay; // 18
	};
	static_assert(sizeof(ConsoleLog) == 0x20);
}
