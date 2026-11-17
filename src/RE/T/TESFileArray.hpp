#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class TESFile;

	class TESFileArray : public BSStaticArray<TESFile*> // 0x00
	{
	public:
	};

	static_assert(sizeof(TESFileArray) == 0x10);
}
