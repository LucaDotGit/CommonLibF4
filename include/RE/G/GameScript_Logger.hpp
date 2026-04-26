#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_ErrorLogger.hpp"

namespace RE
{
	class BSLog;
}

namespace RE::GameScript
{
	class __declspec(novtable) Logger
		: public BSScript::ErrorLogger // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__Logger };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__Logger };

		~Logger() override; // 00

		// override (BSScript::ErrorLogger)
		void PostErrorImpl(const BSScript::ICachedErrorMessage* a_errMsg, Severity a_severity) override; // 01

		// members
		BSFixedString logFolder; // A0
		BSLog* log;				 // A8
	};
	static_assert(sizeof(Logger) == 0xB0);
}
