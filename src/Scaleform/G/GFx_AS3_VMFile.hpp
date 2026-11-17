#pragma once

#include "Scaleform/G/GFx_AS3_GASRefCountBase.hpp"

namespace Scaleform::GFx::AS3
{
	class ScriptVM;

	class __declspec(novtable) VMFile : public GASRefCountBase // 0x00
	{
	public:
		// members
		ScriptVM* vmRef;						  // 0x28
		std::array<std::byte, 0x98 - 0x30> unk30; // 0x30
	};

	static_assert(sizeof(VMFile) == 0x98);
}
