#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_ErrorLogger.hpp"

namespace RE
{
	class BSLog;
}

namespace RE::GameScript
{
	class __declspec(novtable) Logger : public BSScript::ErrorLogger // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__Logger;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__Logger;

		~Logger() override; // 0x00

		// override (BSScript::ErrorLogger)
		void PostErrorImpl(const BSScript::ICachedErrorMessage& a_errorMessage, BSScript::LogSeverity a_severity)
			override; // 0x01

		// members
		BSFixedString logFolder; // 0xA0
		BSLog* log;				 // 0xA8
	};

	static_assert(sizeof(Logger) == 0xB0);
}
