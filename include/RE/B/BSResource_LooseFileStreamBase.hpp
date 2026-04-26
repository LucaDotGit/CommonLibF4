#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSystemFile.hpp"
#include "RE/B/BSSystemFileStreamer.hpp"

namespace RE::BSResource
{
	class __declspec(novtable) LooseFileStreamBase
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSResource____LooseFileStreamBase };
		inline static constexpr auto VTABLE{ VTABLE::BSResource____LooseFileStreamBase };

		// members
		BSFixedString prefix;			 // 00
		BSFixedString dirName;			 // 08
		BSFixedString fileName;			 // 10
		BSSystemFile file;				 // 18
		BSSystemFileStreamer::ID pathID; // 28
	};
	static_assert(sizeof(LooseFileStreamBase) == 0x30);
}
