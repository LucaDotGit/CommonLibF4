#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class NiAVObject;

	class ViewCasterData
	{
	public:
		// members
		ObjectRefHandle activatePickRef;	// 00
		ObjectRefHandle magnetismRef;		// 04
		ObjectRefHandle telekinesisPickRef; // 08
		ObjectRefHandle dialoguePickRef;	// 0C
		NiAVObject* avObject;				// 10
		NiAVObject* shapeCastAVObject;		// 18
		std::uint32_t collisionGroup;		// 20
	};
	static_assert(sizeof(ViewCasterData) == 0x28);
}
