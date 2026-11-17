#pragma once

#include "RE/B/BSTempEffect.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSGeometry;
	class BSTriShape;
	class NiNode;
	class SkinnedDecalCSData;

	class __declspec(novtable) BSTempEffectGeometryDecal : public BSTempEffect // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSTempEffectGeometryDecal;
		inline static constexpr const auto& VTABLE = VTABLE::BSTempEffectGeometryDecal;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSTempEffectGeometryDecal;
		inline static constexpr auto EFFECT_TYPE = TEMP_EFFECT_TYPE::GeometryDecal;

		~BSTempEffectGeometryDecal() override; // 0x00

		// members
		SkinnedDecalCSData* CSData; // 0x30
		void* baseTexture;			// 0x38 - To-Do: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiTexture>,
									// BSResource::EntryDBTraits<BSTextureDB::DBTraits,
									// BSResource::EntryDB<BSTextureDB::DBTraits>>::CArgs>,
									// BSResource::EntryDB<BSTextureDB::DBTraits>>`
		NiPointer<BSGeometry> decalGeometry; // 0x40
		NiPointer<BSTriShape> geometry;		 // 0x48
		std::uint16_t* oldIndex;			 // 0x50
		NiPointer<NiNode> parent;			 // 0x58
		NiPointer<NiNode> decalParent;		 // 0x68
		NiMatrix3 projection;				 // 0x70
		NiPoint3 origin;					 // 0xA0
		NiPoint3 vector;					 // 0xAC
		REX::Float32 scale;					 // 0xB8
		std::int32_t numVerts;				 // 0xBC
		std::uint32_t bodyParts;			 // 0xC0
		REX::Float32 decalRotation;			 // 0xC4
		std::uint8_t subTex;				 // 0xC8
		bool decalLoaded;					 // 0xC9
		bool fading;						 // 0xCA
	};

	static_assert(sizeof(BSTempEffectGeometryDecal) == 0xD0);
}
