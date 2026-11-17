#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class NiAVObject;

	class ViewCasterData
	{
	public:
		// members
		ObjectRefHandle activatePickRef;	// 0x00
		ObjectRefHandle magnetismRef;		// 0x04
		ObjectRefHandle telekinesisPickRef; // 0x08
		ObjectRefHandle dialoguePickRef;	// 0x0C
		NiAVObject* avObject;				// 0x10
		NiAVObject* shapeCastAVObject;		// 0x18
		std::uint32_t collisionGroup;		// 0x20
	};

	static_assert(sizeof(ViewCasterData) == 0x28);
}
