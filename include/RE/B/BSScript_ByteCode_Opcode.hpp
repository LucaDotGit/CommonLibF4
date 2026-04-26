#pragma once

namespace RE::BSScript::ByteCode
{
	enum class Opcode : std::int32_t
	{
		kNoop = 0,
		kIAdd = 1,
		kFAdd = 2,
		kISubtract = 3,
		kFSubtract = 4,
		kIMultiply = 5,
		kFMultiply = 6,
		kIDivide = 7,
		kFDivide = 8,
		kIMod = 9,
		kNot = 10,
		kINegate = 11,
		kFNegate = 12,
		kAssign = 13,
		kCast = 14,
		kCompareEQ = 15,
		kCompareLT = 16,
		kCompareLTE = 17,
		kCompareGT = 18,
		kCompareGTE = 19,
		kJump = 20,
		kJumpT = 21,
		kJumpF = 22,
		kCallMethod = 23,
		kCallParent = 24,
		kCallStatic = 25,
		kReturn = 26,
		kStrCat = 27,
		kPropGet = 28,
		kPropSet = 29,
		kArrayCreate = 30,
		kArrayLength = 31,
		kArrayGetElement = 32,
		kArraySetElement = 33,
		kArrayFindElement = 34,
		kArrayRFindElement = 35,
		kIs = 36,
		kStructCreate = 37,
		kStructGet = 38,
		kStructSet = 39,
		kArrayFindStruct = 40,
		kArrayRFindStruct = 41,
		kArrayAddElements = 42,
		kArrayInsertElement = 43,
		kArrayRemoveLastElement = 44,
		kArrayRemoveElements = 45,
		kArrayClearElements = 46,

		kTotal = 47,
		kBits = 6
	};

}
