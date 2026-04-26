#pragma once

#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform
{
	class LogMessageId;

	class __declspec(novtable) Log
		: public RefCountBase<Log, 2> // 00
	{
	public:
		inline static constexpr auto RTTI{ ::RE::RTTI::Scaleform__Log };
		inline static constexpr auto VTABLE{ ::RE::VTABLE::Scaleform__Log };

		~Log() override
		{
			Release();
		}

		// add
		virtual void LogMessageVarg(LogMessageId a_messageID, const char* a_fmt, std::va_list a_argList);
	};
	static_assert(sizeof(Log) == 0x10);
}
