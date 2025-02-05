#pragma once

#include "RE/Bethesda/BSString.hpp"
#include "RE/Bethesda/BSTSingleton.hpp"

namespace RE
{
	class ConsoleLog
		: public BSTSingletonSDM<ConsoleLog> // 00
	{
	public:
		[[nodiscard]] static ConsoleLog* GetSingleton()
		{
			static REL::Relocation<ConsoleLog**> singleton{ REL::RelocationID(689441, 2690148) };
			return *singleton;
		}

		void AddString(char const* a_string)
		{
			using func_t = decltype(&ConsoleLog::AddString);
			static REL::Relocation<func_t> func{ REL::RelocationID(764, 2248593) };
			return func(this, a_string);
		}

		void Print(const char* a_fmt, std::va_list a_args)
		{
			using func_t = decltype(&ConsoleLog::Print);
			static REL::Relocation<func_t> func{ REL::RelocationID(799546, 2248591) };
			func(this, a_fmt, a_args);
		}

		void PrintLine(const char* a_fmt, ...)
		{
			std::va_list args;
			va_start(args, a_fmt);
			Print(a_fmt, args);
			va_end(args);
		}

		// members
		BSString buffer;		// 08
		bool useConsoleOverlay; // 18
	};
	static_assert(sizeof(ConsoleLog) == 0x20);
}
