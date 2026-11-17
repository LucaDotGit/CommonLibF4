#pragma once

#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class BSMultiBound;
	class NiAVObject;
}

namespace RE::BSDeferredDecal
{
	class __declspec(novtable) BSDFDecal : public NiRefObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSDeferredDecal__BSDFDecal;
		inline static constexpr const auto& VTABLE = VTABLE::BSDeferredDecal__BSDFDecal;

		~BSDFDecal() override; // 0x00

		// members
		std::array<void*, 10>
			textureHandles; // 0x10 - To-Do: `std::array<BSResource::RHandleType<BSResource::Entry<NiPointer<NiTexture>,
							// BSResource::EntryDBTraits<BSTextureDB::DBTraits,
							// BSResource::EntryDB<BSTextureDB::DBTraits>>::CArgs>,
							// BSResource::EntryDB<BSTextureDB::DBTraits>>, 10>`
		NiPointer<NiAVObject> dynamicObject;	// 0x60
		BSMultiBound* multibound;				// 0x68
		NiMatrix3 projection;					// 0x70
		NiPoint3A origin;						// 0xA0
		REX::Float32 decalWidth;				// 0xB0
		REX::Float32 decalHeight;				// 0xB4
		REX::Float32 decalDepth;				// 0xB8
		REX::Float32 parallaxOcclusionScale;	// 0xBC
		REX::Float32 alpha;						// 0xC0
		std::uint16_t stencilRef;				// 0xC4
		std::uint8_t subTex;					// 0xC6
		std::uint8_t maxParallaxOcclusionSteps; // 0xC7
		bool multiplicative;					// 0xC8
		bool useGBufferNormals;					// 0xC9
		bool isFirstInstance;					// 0xCA
		bool intersectFrustum;					// 0xCB
		bool parallaxOcclusionShadows;			// 0xCC
	};

	static_assert(sizeof(BSDFDecal) == 0xD0);
}
