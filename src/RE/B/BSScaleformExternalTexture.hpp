#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiTexture;

	class BSScaleformExternalTexture
	{
	public:
		// members
		NiPointer<NiTexture> gamebryoTexture; // 0x00
		std::uint32_t renderTarget;			  // 0x08
		BSFixedString texturePath;			  // 0x10
	};

	static_assert(sizeof(BSScaleformExternalTexture) == 0x18);
}
