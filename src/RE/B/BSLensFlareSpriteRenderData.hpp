#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSLensFlareSpriteData.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class NiTexture;

	class __declspec(novtable) BSLensFlareSpriteRenderData : public NiRefObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSLensFlareSpriteRenderData;
		inline static constexpr const auto& VTABLE = VTABLE::BSLensFlareSpriteRenderData;

		// members
		BSLensFlareSpriteData data;	  // 0x10
		BSFixedString textureName;	  // 0x38
		void* textureHandle;		  // 0x40 - BSResource::RHandleType<BSResource::Entry<NiPointer<NiTexture>,
									  // BSResource::EntryDBTraits<BSTextureDB::DBTraits,
									  // BSResource::EntryDB<BSTextureDB::DBTraits>>::CArgs>,
									  // BSResource::EntryDB<BSTextureDB::DBTraits>>
		NiPointer<NiTexture> texture; // 0x48
	};

	static_assert(sizeof(BSLensFlareSpriteRenderData) == 0x50);
}
