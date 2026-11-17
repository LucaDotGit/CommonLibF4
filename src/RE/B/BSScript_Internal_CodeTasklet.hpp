#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_Internal_IFuncCallQuery.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class ErrorLogger;
	class Stack;
	class StackFrame;
}

namespace RE::BSScript::Internal
{
	class VirtualMachine;

	class __declspec(novtable) CodeTasklet : public IFuncCallQuery // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__Internal__CodeTasklet;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__Internal__CodeTasklet;

		enum class ResumeReason : std::int32_t
		{
			NotResuming = 0,
			NotResumingNoIncrement = 1,
			InitialStart = 2,
			FunctionReturn = 3,
			RetryInstruction = 4,
			FunctionCall = 5
		};

		~CodeTasklet() override; // 0x00

		// override (IFuncCallQuery)
		auto GetFunctionCallInfo(
			CallType& a_outCallType,
			BSTSmartPointer<ObjectTypeInfo>& a_outObjectTypeInfo,
			BSFixedString& a_outName,
			Variable& a_outSelf,
			BSScrapArray<Variable>& a_outArgs) const -> bool override; // 0x01

		// members
		Stack* stack;										// 0x10
		VirtualMachine* vm;									// 0x18
		ErrorLogger* errorLogger;							// 0x20
		REX::Enum<ResumeReason, std::int32_t> resumeReason; // 0x28
		StackFrame* topFrame;								// 0x30
		std::uint32_t frameMemoryPage;						// 0x38
		std::uint8_t jumpBitCount;							// 0x3C
		std::uint8_t localVarBitCount;						// 0x3D
		std::uint8_t memberVarBitCount;						// 0x3E
		std::uint32_t instructionDataBitCount;				// 0x40
		void* instructionDataStart;							// 0x48
	};

	static_assert(sizeof(CodeTasklet) == 0x50);
}
