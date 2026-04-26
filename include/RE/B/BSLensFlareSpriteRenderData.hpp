#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSLensFlareSpriteData.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class NiTexture;

	class __declspec(novtable) BSLensFlareSpriteRenderData
		: public NiRefObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSLensFlareSpriteRenderData };
		inline static constexpr auto VTABLE{ VTABLE::BSLensFlareSpriteRenderData };

		// members
		BSLensFlareSpriteData data;	  // 10
		BSFixedString textureName;	  // 38
		void* textureHandle;		  // 40 - BSResource::RHandleType<BSResource::Entry<NiPointer<NiTexture>, BSResource::EntryDBTraits<BSTextureDB::DBTraits, BSResource::EntryDB<BSTextureDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSTextureDB::DBTraits>>
		NiPointer<NiTexture> texture; // 48
	};
	static_assert(sizeof(BSLensFlareSpriteRenderData) == 0x50);
}
