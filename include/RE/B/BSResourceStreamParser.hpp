#pragma once

#include "RE/B/BSResourceNiBinaryStream.hpp"
#include "RE/B/BSStreamParserData.hpp"

namespace RE
{
	class __declspec(novtable) BSResourceStreamParser
		: public BSResourceNiBinaryStream, // 00
		  public BSStreamParserData		   // 30
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSResourceStreamParser };
		inline static constexpr auto VTABLE{ VTABLE::BSResourceStreamParser };

		explicit BSResourceStreamParser(const char* a_file);

		~BSResourceStreamParser() override = default; // 00

		// override (BSStreamParserData)
		bool Begin() override { return good(); }			  // 01
		void End() override { return; }						  // 02
		NiBinaryStream* GetStream() override { return this; } // 03
	};
	static_assert(sizeof(BSResourceStreamParser) == 0x38);
}
