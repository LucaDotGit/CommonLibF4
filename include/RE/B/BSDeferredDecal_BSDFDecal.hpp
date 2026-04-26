#pragma once

#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class BSMultiBound;
	class NiAVObject;
}

namespace RE::BSDeferredDecal
{
	class __declspec(novtable) BSDFDecal
		: public NiRefObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSDeferredDecal__BSDFDecal };
		inline static constexpr auto VTABLE{ VTABLE::BSDeferredDecal__BSDFDecal };

		~BSDFDecal() override; // 00

		// members
		std::array<void*, 10> textureHandles;	// 10 - TODO: `std::array<BSResource::RHandleType<BSResource::Entry<NiPointer<NiTexture>, BSResource::EntryDBTraits<BSTextureDB::DBTraits, BSResource::EntryDB<BSTextureDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSTextureDB::DBTraits>>, 10>`
		NiPointer<NiAVObject> dynamicObject;	// 60
		BSMultiBound* multibound;				// 68
		NiMatrix3 projection;					// 70
		NiPoint3A origin;						// A0
		REX::Float32 decalWidth;				// B0
		REX::Float32 decalHeight;				// B4
		REX::Float32 decalDepth;				// B8
		REX::Float32 parallaxOcclusionScale;	// BC
		REX::Float32 alpha;						// C0
		std::uint16_t stencilRef;				// C4
		std::uint8_t subTex;					// C6
		std::uint8_t maxParallaxOcclusionSteps; // C7
		bool multiplicative;					// C8
		bool useGBufferNormals;					// C9
		bool isFirstInstance;					// CA
		bool intersectFrustum;					// CB
		bool parallaxOcclusionShadows;			// CC
	};
	static_assert(sizeof(BSDFDecal) == 0xD0);
}
