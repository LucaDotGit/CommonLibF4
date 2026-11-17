#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::BSGraphics
{
	class Texture;
}

namespace RE
{
	class NiTexture;

	class ImageSpaceLUTData
	{
	public:
		// members
		std::array<BSFixedString, 4> filename;		   // 0x00
		std::array<REX::Float32, 4> weight;			   // 0x20
		std::array<NiPointer<NiTexture>, 4> niTexture; // 0x30
		std::array<BSGraphics::Texture*, 4> texture;   // 0x50
	};

	static_assert(sizeof(ImageSpaceLUTData) == 0x70);
}
