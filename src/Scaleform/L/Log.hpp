#pragma once

#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform
{
	class LogMessageId;

	class __declspec(novtable) Log : public RefCountBase<Log, 2> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RE::RTTI::Scaleform__Log;
		inline static constexpr const auto& VTABLE = RE::VTABLE::Scaleform__Log;

		~Log() override; // 0x00

		// add
		virtual void LogMessageVarg(LogMessageId a_messageID, const char* a_format, std::va_list a_args); // 0x01
	};

	static_assert(sizeof(Log) == 0x10);
}
