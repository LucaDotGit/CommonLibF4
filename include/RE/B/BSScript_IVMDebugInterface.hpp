#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::BSScript
{
	class __declspec(novtable) IVMDebugInterface
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IVMDebugInterface };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IVMDebugInterface };

		virtual ~IVMDebugInterface() = default; // 00

		// add
		virtual void DumpRunningStacksToLog() = 0;																										// 01
		virtual void DumpStackFrameToLog(StackID a_stackID, std::uint32_t a_frame, bool a_verbose) = 0;													// 02
		virtual void GetStackFrame(StackID a_stackID, std::uint32_t a_frame, bool a_wantFilename, BSFixedString& a_stackFrame) = 0;						// 03
		virtual void DumpPersistenceInformationToLog(const char* a_logfile, ObjectHandle a_objectHandle) const = 0;										// 04
		virtual void DumpEventRelayInformationToLog(const char* a_logfile, ObjectHandle a_objectHandle, const BSFixedString& a_propertyName) const = 0; // 05
	};
	static_assert(sizeof(IVMDebugInterface) == 0x08);
}
