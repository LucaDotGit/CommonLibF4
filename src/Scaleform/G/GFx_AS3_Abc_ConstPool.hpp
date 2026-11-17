#pragma once

#include "Scaleform/G/GFx_AS3_Abc_NamespaceInfo.hpp"
#include "Scaleform/N/NewOverrideBase.hpp"

namespace Scaleform::GFx::AS3::Abc
{
	class ConstPool : public NewOverrideBase<339>
	{
	public:
		// members
		std::uint32_t doubleCount;				  // 0x00
		std::uint8_t* doubles;					  // 0x08
		std::array<std::byte, 0xA0 - 0x10> unk10; // 0x10 - To-Do
		NamespaceInfo anyNamespace;				  // 0xA0
	};

	static_assert(sizeof(ConstPool) == 0xB8);
}
