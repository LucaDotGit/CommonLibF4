#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSScript/ICachedErrorMessage.hpp"
#include "RE/Bethesda/BSTEvent.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"

namespace RE::BSScript
{
	class ICachedErrorMessage;

	struct LogEvent;

	class __declspec(novtable) ErrorLogger
		: public BSTEventSource<LogEvent> // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__ErrorLogger };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__ErrorLogger };

		enum class Severity
		{
			kInfo,
			kWarning,
			kError,
			kFatal
		};

		struct PerThreadErrorCounts
		{
		public:
			// members
			std::uint32_t fatalCount;	// 00
			std::uint32_t errorCount;	// 04
			std::uint32_t warningCount; // 08
		};
		static_assert(sizeof(PerThreadErrorCounts) == 0xC);

		virtual ~ErrorLogger(); // 00

		// add
		virtual void PostErrorImpl(const ICachedErrorMessage* a_errMsg, Severity a_severity) = 0; // 01
		virtual void ResetImpl() { return; }													  // 02

		// members
		const BSFixedString logName;											   // 60
		mutable BSSpinLock dataLock;											   // 68
		BSTHashMap<std::uint32_t, ErrorLogger::PerThreadErrorCounts> threadErrors; // 70
	};
	static_assert(sizeof(ErrorLogger) == 0xA0);
}
