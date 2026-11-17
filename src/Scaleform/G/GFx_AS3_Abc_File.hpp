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
	class __declspec(novtable) alignas(0x10) File :
		public RefCountImpl, // 0x00
		public NewOverrideBase<338>
	{
	public:
		~File() override; // 0x00

		// members
		std::uint32_t dataSize;		  // 0x010
		String source;				  // 0x018
		std::uint16_t minorVersion;	  // 0x020
		std::uint16_t majorVersion;	  // 0x022
		ConstPool constPool;		  // 0x028
		MethodTable methods;		  // 0x0E0
		MetadataTable metadata;		  // 0x0F8
		TraitTable traits;			  // 0x110
		ClassTable classes;			  // 0x128
		ScriptTable scripts;		  // 0x140
		MethodBodyTable methodBodies; // 0x158
	};

	static_assert(sizeof(File) == 0x170);
}
