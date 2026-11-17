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
		inline static constexpr const auto& RTTI = RTTI::BSLensFlareRenderData;

		// members
		REX::Float32 fadeDistRadiusScale;						  // 0x00
		REX::Float32 colorInfluence;							  // 0x04
		BSTArray<NiPointer<BSLensFlareSpriteRenderData>> sprites; // 0x08
		mutable BSSpinLock lock;								  // 0x20
		std::uint32_t refCount;									  // 0x28
	};

	static_assert(sizeof(BSLensFlareRenderData) == 0x30);
}
