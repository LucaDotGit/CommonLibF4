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

	class __declspec(novtable) BGSTextureSet :
		public TESBoundObject, // 0x000
		public BSTextureSet	   // 0x068
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSTextureSet;
		inline static constexpr const auto& VTABLE = VTABLE::BGSTextureSet;
		inline static constexpr auto FORM_TYPE = FormType::TextureSet;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint16_t
		{
			None = 0,
			NoSpecularMap = 1 << 0,
			FacegenTextures = 1 << 1,
			HasModelSpaceNormalMap = 1 << 2
		};

		~BGSTextureSet() override; // 0x00

		GAME_HEAP_REDEFINE_NEW(BGSTextureSet);

		// members
		BSFixedString materialName;																			  // 0x078
		std::array<TESTexture, std::to_underlying(BSShaderProperty::TextureType::_Count)> textures;			  // 0x080
		DecalData* decalData;																				  // 0x100
		REX::EnumSet<Flags, std::uint16_t> flags;															  // 0x108
		std::array<BSResource::ID, std::to_underlying(BSShaderProperty::TextureType::_Count)> textureFileIDs; // 0x10C
		BSShaderData materialData;																			  // 0x170
	};

	static_assert(sizeof(BGSTextureSet) == 0x350);
}
