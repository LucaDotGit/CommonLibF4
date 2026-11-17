#pragma once

#include "Scaleform/G/GFx_AS3_Abc_MbiInd.hpp"
#include "Scaleform/G/GFx_AS3_Value.hpp"
#include "Scaleform/N/NewOverrideBase.hpp"

namespace Scaleform
{
	class MemoryHeap;
}

namespace Scaleform::GFx::AS3
{
	class Traits;
	class ValueRegisterFile;
	class VMAbcFile;

	class __declspec(novtable) CallFrame : public NewOverrideBase<330>
	{
	public:
		// members
		bool discardResult;				  // 0x00
		bool aCopy;						  // 0x01
		std::uint64_t scopeStackBaseInd;  // 0x08
		std::uint64_t* cp;				  // 0x10
		ValueRegisterFile* registerValue; // 0x18
		MemoryHeap* heap;				  // 0x20
		VMAbcFile* file;				  // 0x28
		Abc::MbiInd mbiIndex;			  // 0x30
		void* savedScope;				  // 0x38 - To-Do
		Traits* originationTraits;		  // 0x40
		void* scopeStack;				  // 0x48 - To-Do
		AS3::Value* prevInitialStackPos;  // 0x50
		void* defXMLNamespace;			  // 0x58 - To-Do
		AS3::Value* prevFirstStackPos;	  // 0x60
		AS3::Value invoker;				  // 0x68
	};

	static_assert(sizeof(CallFrame) == 0x88);
}
