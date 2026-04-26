#pragma once

#include "Scaleform/G/GFx_AS3_Abc_File.hpp"
#include "Scaleform/G/GFx_AS3_VMFile.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace Scaleform::GFx::AS3
{
	class __declspec(novtable) VMAbcFile
		: public VMFile // 00
	{
	public:
		// members
		Ptr<Abc::File> file;					  // 98
		std::array<std::byte, 0xE8 - 0xA0> unkA0; // A0 - TODO
	};
	static_assert(sizeof(VMAbcFile) == 0xE8);
}
