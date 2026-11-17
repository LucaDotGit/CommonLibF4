#pragma once

#include "Scaleform/N/NewOverrideBase.hpp"

namespace Scaleform::GFx::AS3::Abc
{
	class MethodTable : public NewOverrideBase<338>
	{
	public:
		// members
		std::array<std::byte, 0x18> unk00; // 0x00 - To-Do
	};

	static_assert(sizeof(MethodTable) == 0x18);
}
