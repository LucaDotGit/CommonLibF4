#pragma once

#include "RE/B/BSResourceNiBinaryStream.hpp"
#include "RE/B/BSStreamParserData.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) BSResourceStreamParser :
		public BSResourceNiBinaryStream, // 0x00
		public BSStreamParserData		 // 0x30
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSResourceStreamParser;
		inline static constexpr const auto& VTABLE = VTABLE::BSResourceStreamParser;

		explicit BSResourceStreamParser(const char* a_file) :
			BSResourceNiBinaryStream(a_file)
		{
			REL::EmplaceVtable(this);
		}

		~BSResourceStreamParser() override = default; // 0x00

		// override (BSStreamParserData)
		auto Begin() -> bool override // 0x01
		{
			return good();
		}

		void End() override // 0x02
		{
			return;
		}

		auto GetStream() -> NiBinaryStream* override // 0x03
		{
			return this;
		}

		GAME_HEAP_REDEFINE_NEW(BSResourceStreamParser);
	};

	static_assert(sizeof(BSResourceStreamParser) == 0x38);
}
