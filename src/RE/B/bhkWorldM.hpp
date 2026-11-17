#pragma once

#include "RE/B/bhkWorld.hpp"

namespace RE
{
	class __declspec(novtable) bhkWorldM : public bhkWorld // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::bhkWorldM;
		inline static constexpr const auto& VTABLE = VTABLE::bhkWorldM;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::bhkWorldM;

		~bhkWorldM() override; // 0x00

		// members
		hkVector4 worldTotalSize; // 0x180
		hkVector4 borderSize;	  // 0x190
		hkVector4 broadPhaseSize; // 0x1A0
	};

	static_assert(sizeof(bhkWorldM) == 0x1B0);
}
