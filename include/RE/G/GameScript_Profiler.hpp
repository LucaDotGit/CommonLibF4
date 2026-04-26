#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_IProfilePolicy.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/B/BSTimer.hpp"

namespace RE
{
	class BSLog;
}

namespace RE::BSScript
{
	class Variable;
}

namespace RE::BSScript::Internal
{
	class IFuncCallQuery;
}

namespace RE::GameScript
{
	class __declspec(novtable) Profiler
		: public BSScript::IProfilePolicy // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__Profiler };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__Profiler };

		~Profiler() override; // 00

		// override (BSScript::IProfilePolicy)
		void StackFramePushQueued(BSScript::StackID a_stackID, std::uint32_t a_frameNumber, const BSTSmartPointer<BSScript::Internal::IFuncCallQuery>& a_funcCallQuery) override;																 // 01
		void StackFramePushed(BSScript::StackID a_stackID, std::uint32_t a_frameNumber, const BSScript::Variable& a_self, const BSFixedString& a_scriptName, const BSFixedString& a_stateName, const BSFixedString& a_functionName) override;	 // 02
		void StackFramePopQueued(BSScript::StackID a_stackID, std::uint32_t a_frameNumber, const BSScript::Variable& a_self, const BSFixedString& a_scriptName, const BSFixedString& a_stateName, const BSFixedString& a_functionName) override; // 03
		void StackFramePopped(BSScript::StackID a_stackID, std::uint32_t a_frameNumber, const BSScript::Variable& a_self, const BSFixedString& a_scriptName, const BSFixedString& a_stateName, const BSFixedString& a_functionName) override;	 // 04

		// members
		mutable BSSpinLock dataLock;												// 008
		BSLog* globalProfilingLog;													// 010
		BSTHashMap<RE::BSScript::StackID, BSLog*> watchedStacks;					// 018
		BSTHashMap<BSFixedString, BSLog*> watchedScripts;							// 048
		BSTHashMap<BSScript::ObjectHandle, BSLog*> watchedObjects;					// 078
		BSTArray<BSTPair<BSFixedString, BSScript::ObjectHandle>> watchedStackRoots; // 0A8
		BSTimer timer;																// 0C0
	};
#if COMMONLIB_RUNTIME_AE == 0
	static_assert(sizeof(Profiler) == 0x100);
#elif COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0
	static_assert(sizeof(Profiler) == 0x110);
#else
	static_assert(sizeof(Profiler) == 0x0E0);
#endif
}
