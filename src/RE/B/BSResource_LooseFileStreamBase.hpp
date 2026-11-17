#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSystemFile.hpp"
#include "RE/B/BSSystemFileStreamer.hpp"

namespace RE::BSResource
{
	class __declspec(novtable) LooseFileStreamBase
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSResource____LooseFileStreamBase;
		inline static constexpr const auto& VTABLE = VTABLE::BSResource____LooseFileStreamBase;

		// members
		BSFixedString prefix;			 // 0x00
		BSFixedString dirName;			 // 0x08
		BSFixedString fileName;			 // 0x10
		BSSystemFile file;				 // 0x18
		BSSystemFileStreamer::ID pathID; // 0x28
	};

	static_assert(sizeof(LooseFileStreamBase) == 0x30);
}
