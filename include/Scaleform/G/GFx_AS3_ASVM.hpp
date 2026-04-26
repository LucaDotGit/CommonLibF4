#pragma once

#include "Scaleform/G/GFx_AS3_VM.hpp"

namespace Scaleform::GFx::AS3
{
	class __declspec(novtable) ASVM
		: public ScriptVM // 000
	{
	public:
		// members
		std::array<std::byte, 0x3C8 - 0x2D0> unk2D0; // 2D0 - TODO
	};
	static_assert(sizeof(ASVM) == 0x3C8);
}
