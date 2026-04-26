#pragma once

#include "RE/B/BSTempEffect.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSGeometry;
	class BSTriShape;
	class NiNode;
	class SkinnedDecalCSData;

	class __declspec(novtable) BSTempEffectGeometryDecal
		: public BSTempEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSTempEffectGeometryDecal };
		inline static constexpr auto VTABLE{ VTABLE::BSTempEffectGeometryDecal };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSTempEffectGeometryDecal };
		inline static constexpr auto EFFECT_TYPE{ TEMP_EFFECT_TYPE::kGeometryDecal };

		~BSTempEffectGeometryDecal() override; // 00

		// members
		SkinnedDecalCSData* CSData;			 // 30
		void* baseTexture;					 // 38 - TODO: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiTexture>, BSResource::EntryDBTraits<BSTextureDB::DBTraits, BSResource::EntryDB<BSTextureDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSTextureDB::DBTraits>>`
		NiPointer<BSGeometry> decalGeometry; // 40
		NiPointer<BSTriShape> geometry;		 // 48
		std::uint16_t* oldIndex;			 // 50
		NiPointer<NiNode> parent;			 // 58
		NiPointer<NiNode> decalParent;		 // 68
		NiMatrix3 projection;				 // 70
		NiPoint3 origin;					 // A0
		NiPoint3 vector;					 // AC
		REX::Float32 scale;					 // B8
		std::int32_t numVerts;				 // BC
		std::uint32_t bodyParts;			 // C0
		REX::Float32 decalRotation;			 // C4
		std::uint8_t subTex;				 // C8
		bool decalLoaded;					 // C9
		bool fading;						 // CA
	};
	static_assert(sizeof(BSTempEffectGeometryDecal) == 0xD0);
}
