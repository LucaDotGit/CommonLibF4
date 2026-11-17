#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class NiBinaryStream;

	class __declspec(novtable) BSStreamParserData
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSStreamParserData;
		inline static constexpr const auto& VTABLE = VTABLE::BSStreamParserData;

		virtual ~BSStreamParserData() = default; // 0x00

		// add
		virtual auto Begin() -> bool = 0;				 // 0x01
		virtual void End() = 0;							 // 0x02
		virtual auto GetStream() -> NiBinaryStream* = 0; // 0x03

		GAME_HEAP_REDEFINE_NEW(BSStreamParserData);
	};
}
