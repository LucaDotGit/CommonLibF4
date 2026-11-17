#pragma once

namespace RE::BSScript::ByteCode
{
	enum class Opcode : std::int32_t
	{
		Noop = 0,
		IAdd = 1,
		FAdd = 2,
		ISubtract = 3,
		FSubtract = 4,
		IMultiply = 5,
		FMultiply = 6,
		IDivide = 7,
		FDivide = 8,
		IMod = 9,
		Not = 10,
		INegate = 11,
		FNegate = 12,
		Assign = 13,
		Cast = 14,
		CompareEQ = 15,
		CompareLT = 16,
		CompareLTE = 17,
		CompareGT = 18,
		CompareGTE = 19,
		Jump = 20,
		JumpT = 21,
		JumpF = 22,
		CallMethod = 23,
		CallParent = 24,
		CallStatic = 25,
		Return = 26,
		StrCat = 27,
		PropGet = 28,
		PropSet = 29,
		ArrayCreate = 30,
		ArrayLength = 31,
		ArrayGetElement = 32,
		ArraySetElement = 33,
		ArrayFindElement = 34,
		ArrayRFindElement = 35,
		Is = 36,
		StructCreate = 37,
		StructGet = 38,
		StructSet = 39,
		ArrayFindStruct = 40,
		ArrayRFindStruct = 41,
		ArrayAddElements = 42,
		ArrayInsertElement = 43,
		ArrayRemoveLastElement = 44,
		ArrayRemoveElements = 45,
		ArrayClearElements = 46,

		_Count = 47,
		Bits = 6
	};

}
