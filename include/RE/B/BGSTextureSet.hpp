#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSResource_ID.hpp"
#include "RE/B/BSShaderData.hpp"
#include "RE/B/BSTextureSet.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class DecalData;

	class __declspec(novtable) BGSTextureSet
		: public TESBoundObject, // 000
		  public BSTextureSet	 // 068
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSTextureSet };
		inline static constexpr auto VTABLE{ VTABLE::BGSTextureSet };
		inline static constexpr auto FORM_TYPE{ FormType::kTextureSet };

		GAME_HEAP_REDEFINE_NEW(BGSTextureSet);

		// members
		BSFixedString materialName;					  // 078
		std::array<TESTexture, 8> textures;			  // 080
		DecalData* decalData;						  // 100
		std::uint16_t flags;						  // 108
		std::array<BSResource::ID, 8> textureFileIDs; // 10C
		BSShaderData materialData;					  // 170
	};
	static_assert(sizeof(BGSTextureSet) == 0x350);
}
