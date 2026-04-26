#pragma once

#include "Scaleform/G/GFx_AS3_Abc_ClassTable.hpp"
#include "Scaleform/G/GFx_AS3_Abc_ConstPool.hpp"
#include "Scaleform/G/GFx_AS3_Abc_MetadataTable.hpp"
#include "Scaleform/G/GFx_AS3_Abc_MethodBodyTable.hpp"
#include "Scaleform/G/GFx_AS3_Abc_MethodTable.hpp"
#include "Scaleform/G/GFx_AS3_Abc_ScriptTable.hpp"
#include "Scaleform/G/GFx_AS3_Abc_TraitTable.hpp"
#include "Scaleform/N/NewOverrideBase.hpp"
#include "Scaleform/R/RefCountBase.hpp"
#include "Scaleform/S/String.hpp"

namespace Scaleform::GFx::AS3::Abc
{
	class __declspec(novtable) alignas(0x10) File
		: public RefCountImpl, // 00
		  public NewOverrideBase<338>
	{
	public:
		~File() override; // 00

		// members
		std::uint32_t dataSize;		  // 010
		String source;				  // 018
		std::uint16_t minorVersion;	  // 020
		std::uint16_t majorVersion;	  // 022
		ConstPool constPool;		  // 028
		MethodTable methods;		  // 0E0
		MetadataTable metadata;		  // 0F8
		TraitTable traits;			  // 110
		ClassTable classes;			  // 128
		ScriptTable scripts;		  // 140
		MethodBodyTable methodBodies; // 158
	};
	static_assert(sizeof(File) == 0x170);
}
