#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSResource_ID.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTempEffect.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiQuaternion.hpp"

namespace RE
{
	class bhkWorld;
	class PositionPlayerEvent;

	class __declspec(novtable) BSTerrainEffect :
		public BSTempEffect,					 // 0x00
		public BSTEventSink<PositionPlayerEvent> // 0x30
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSTerrainEffect;
		inline static constexpr const auto& VTABLE = VTABLE::BSTerrainEffect;
		inline static constexpr auto EFFECT_TYPE = TEMP_EFFECT_TYPE::Terrain;

		class BoneAdjustment
		{
		public:
			// members
			NiMatrix3 rotation;	   // 0x00
			NiAVObject* pBone;	   // 0x30
			REX::Float32 fZOffset; // 0x38
		};

		static_assert(sizeof(BoneAdjustment) == 0x40);

		~BSTerrainEffect() override; // 0x00

		// members
		NiQuaternion orientation;					 // 0x38
		NiPoint3 position;							 // 0x48
		BSTArray<BoneAdjustment> terrainAdjustments; // 0x58
		BSTArray<BoneAdjustment> dynamicAdjustments; // 0x70
		NiPointer<NiNode> model;					 // 0x88
		BSResource::ID modelID;						 // 0x90
		ObjectRefHandle target;						 // 0x9C
		NiPointer<bhkWorld> physWorld;				 // 0xA0
		std::uint32_t physGroup;					 // 0xA8
		NiPointer<NiAVObject> followNode;			 // 0xB0
	};

	static_assert(sizeof(BSTerrainEffect) == 0xB8);
}
