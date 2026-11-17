#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSScript
{
	enum class LogSeverity : std::int32_t;

	class ICachedErrorMessage;
	class LogEvent;

	class __declspec(novtable) ErrorLogger : public BSTEventSource<LogEvent> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__ErrorLogger;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__ErrorLogger;

		class PerThreadErrorCounts
		{
		public:
			// members
			std::uint32_t fatalCount;	// 0x00
			std::uint32_t errorCount;	// 0x04
			std::uint32_t warningCount; // 0x08
		};

		static_assert(sizeof(PerThreadErrorCounts) == 0x0C);

		virtual ~ErrorLogger(); // 0x00

		// add
		virtual void PostErrorImpl(const ICachedErrorMessage& a_errorMessage, LogSeverity a_severity) = 0; // 0x01
		virtual void ResetImpl(); // 0x02 - { return; }

		void PostCachedError(const ICachedErrorMessage& a_errorMessage, LogSeverity a_severity);

		GAME_HEAP_REDEFINE_NEW(ErrorLogger);

		// members
		BSFixedString logName;												// 0x60
		mutable BSSpinLock dataLock;										// 0x68
		BSTHashMap<REX::W32::THREAD_ID, PerThreadErrorCounts> threadErrors; // 0x70
	};

	static_assert(sizeof(ErrorLogger) == 0xA0);
}
