#pragma once

#include "Scaleform/N/NewOverrideBase.hpp"

namespace Scaleform::GFx::AS3::Abc
{
	class ScriptTable
		: public NewOverrideBase<338>
	{
	public:
		// members
		std::array<std::byte, 0x18> punk00; // 00 - TODO
	};
	static_assert(sizeof(ScriptTable) == 0x18);
}
