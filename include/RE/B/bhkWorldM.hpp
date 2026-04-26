#pragma once

#include "RE/B/bhkWorld.hpp"

namespace RE
{
	class __declspec(novtable) bhkWorldM
		: public bhkWorld // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::bhkWorldM };
		inline static constexpr auto VTABLE{ VTABLE::bhkWorldM };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::bhkWorldM };

		~bhkWorldM() override; // 00

		// members
		hkVector4f worldTotalSize; // 180
		hkVector4f borderSize;	   // 190
		hkVector4f broadPhaseSize; // 1A0
	};
	static_assert(sizeof(bhkWorldM) == 0x1B0);
}
