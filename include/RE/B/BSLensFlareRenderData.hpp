#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSLensFlareSpriteRenderData;

	class BSLensFlareRenderData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSLensFlareRenderData };

		// members
		REX::Float32 fadeDistRadiusScale;						  // 00
		REX::Float32 colorInfluence;							  // 04
		BSTArray<NiPointer<BSLensFlareSpriteRenderData>> sprites; // 08
		mutable BSSpinLock lock;								  // 20
		std::uint32_t refCount;									  // 28
	};
	static_assert(sizeof(BSLensFlareRenderData) == 0x30);
}
