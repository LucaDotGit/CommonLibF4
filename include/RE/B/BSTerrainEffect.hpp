#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSResource_ID.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTempEffect.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiQuaternion.hpp"

namespace RE
{
	class bhkWorld;
	class PositionPlayerEvent;

	class __declspec(novtable) BSTerrainEffect
		: public BSTempEffect,					   // 00
		  public BSTEventSink<PositionPlayerEvent> // 30
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSTerrainEffect };
		inline static constexpr auto VTABLE{ VTABLE::BSTerrainEffect };
		inline static constexpr auto EFFECT_TYPE{ TEMP_EFFECT_TYPE::kTerrain };

		class BoneAdjustment
		{
		public:
			// members
			NiMatrix3 rotation;	   // 00
			NiAVObject* pBone;	   // 30
			REX::Float32 fZOffset; // 38
		};
		static_assert(sizeof(BoneAdjustment) == 0x40);

		~BSTerrainEffect() override; // 00

		// members
		NiQuaternion orientation;					 // 38
		NiPoint3 position;							 // 48
		BSTArray<BoneAdjustment> terrainAdjustments; // 58
		BSTArray<BoneAdjustment> dynamicAdjustments; // 70
		NiPointer<NiNode> model;					 // 88
		BSResource::ID modelID;						 // 90
		ObjectRefHandle target;						 // 9C
		NiPointer<bhkWorld> physWorld;				 // A0
		std::uint32_t physGroup;					 // A8
		NiPointer<NiAVObject> followNode;			 // B0
	};
	static_assert(sizeof(BSTerrainEffect) == 0xB8);
}
