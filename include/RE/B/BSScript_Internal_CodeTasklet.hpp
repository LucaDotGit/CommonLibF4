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

	class __declspec(novtable) CodeTasklet
		: public IFuncCallQuery // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__Internal__CodeTasklet };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__Internal__CodeTasklet };

		enum class OpCode : std::int32_t
		{
			kNop = 0,
			kIAdd = 1,
			kFAdd = 2,
			kISub = 3,
			kFSub = 4,
			kIMul = 5,
			kFMul = 6,
			kIDiv = 7,
			kFDiv = 8,
			kIMod = 9,
			kNot = 10,
			kINeg = 11,
			kFNeg = 12,
			kAssign = 13,
			kCast = 14,
			kCmp_Eq = 15,
			kCmp_Lt = 16,
			kCmp_Lte = 17,
			kCmp_Gt = 18,
			kCmp_Gte = 19,
			kJmp = 20,
			kJmpT = 21,
			kJmpF = 22,
			kCallMethod = 23,
			kCallParent = 24,
			kCallStatic = 25,
			kReturn = 26,
			kStrCat = 27,
			kPropGet = 28,
			kPropSet = 29,
			kArray_Create = 30,
			kArray_Length = 31,
			kArray_GetElement = 32,
			kArray_SetElement = 33,
			kArray_FindElement = 34,
			kArray_RFindElement = 35,
			kIs = 36,
			kStruct_Create = 37,
			kStruct_Get = 38,
			kStruct_Set = 39,
			kArray_FindStruct = 40,
			kArray_RFindStruct = 41,
			kArray_Add = 42,
			kArray_Insert = 43,
			kArray_RemoveLast = 44,
			kArray_Remove = 45,
			kArray_Clear = 46
		};

		enum class ResumeReason : std::int32_t
		{
			kNotResuming = 0,
			kNotResumingNoIncrement = 1,
			kInitialStart = 2,
			kFunctionReturn = 3,
			kRetryInstruction = 4,
			kFunctionCall = 5
		};

		~CodeTasklet() override; // 00

		// override (IFuncCallQuery)
		bool GetFunctionCallInfo(CallType& a_callType, BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo, BSFixedString& a_name, Variable& a_self, BSScrapArray<Variable>& a_args) const override; // 01

		// members
		Stack* stack;										// 10
		VirtualMachine* vm;									// 18
		ErrorLogger* errorLogger;							// 20
		REX::Enum<ResumeReason, std::int32_t> resumeReason; // 28
		StackFrame* topFrame;								// 30
		std::uint32_t frameMemoryPage;						// 38
		std::uint8_t jumpBitCount;							// 3C
		std::uint8_t localVarBitCount;						// 3D
		std::uint8_t memberVarBitCount;						// 3E
		std::uint32_t instructionDataBitCount;				// 40
		void* instructionDataStart;							// 48
	};
	static_assert(sizeof(CodeTasklet) == 0x50);
}
