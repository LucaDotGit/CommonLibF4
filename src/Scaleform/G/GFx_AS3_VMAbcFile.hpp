#pragma once

#include "Scaleform/G/GFx_AS3_Abc_File.hpp"
#include "Scaleform/G/GFx_AS3_VMFile.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace Scaleform::GFx::AS3
{
	class __declspec(novtable) VMAbcFile : public VMFile // 0x00
	{
	public:
		// members
		Ptr<Abc::File> file;					  // 0x98
		std::array<std::byte, 0xE8 - 0xA0> unkA0; // 0xA0 - To-Do
	};

	static_assert(sizeof(VMAbcFile) == 0xE8);
}
