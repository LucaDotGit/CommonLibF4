#pragma once

#include "Scaleform/N/NewOverrideBase.hpp"

namespace Scaleform::GFx::AS3::Abc
{
	class ClassTable
		: public NewOverrideBase<338>
	{
	public:
		// members
		std::array<std::byte, 0x18 - 0x00> unk00; // 00 - TODO
	};
	static_assert(sizeof(ClassTable) == 0x18);
}
