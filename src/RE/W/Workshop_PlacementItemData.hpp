#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/H/hkAabb.hpp"

namespace BSConnectPoint
{
	class Parent;
}

namespace RE::Workshop
{
	class bhkNPCollisionObject;
	class hknpShape;

	class PlacementItemData
	{
	public:
		void Set(TESObjectREFR& a_ref)
		{
			using FuncType = decltype(&PlacementItemData::Set);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::PlacementItemData::Set);
			std::invoke(FUNC, this, a_ref);
		}

		// members
		ObjectRefHandle placementItem;								  // 0x00
		BSTArray<hknpShape*> dropProxies;							  // 0x08
		BSTArray<bhkNPCollisionObject*> bodies;						  // 0x20
		BSTArray<BSTSmartPointer<BSConnectPoint::Parent>> snapPoints; // 0x38
		BSTSmartPointer<BSConnectPoint::Parent> recenterPoint;		  // 0x50
		hkAabb dropProxyExtends;									  // 0x60
		REX::Float32 sinkDepth;										  // 0x80
		REX::Float32 zOffset;										  // 0x84
		REX::Float32 intersectTolerance;							  // 0x88
		REX::Float32 snapPointQueryRadius;							  // 0x8C
		REX::Float32 forwardCastZRot;								  // 0x90
		REX::Float32 xyBoundOverride;								  // 0x94
		REX::Float32 xBoundMinOverride;								  // 0x98
		REX::Float32 xBoundMaxOverride;								  // 0x9C
		REX::Float32 yBoundMinOverride;								  // 0xA0
		REX::Float32 yBoundMaxOverride;								  // 0xA4
		REX::Float32 zBoundMinOverride;								  // 0xA8
		REX::Float32 zBoundMaxOverride;								  // 0xAC
		std::uint32_t dropProxyIndex;								  // 0xB0
		bool anythingIsGround;										  // 0xB4
		bool clampUp;												  // 0xB5
		bool forwardCast;											  // 0xB6
		bool recenter;												  // 0xB7
		bool ignoreSimpleIntersection;								  // 0xB8
		bool allowUnsupportedStacking;								  // 0xB9
		bool isSet;													  // 0xBA
		bool mustSnap;												  // 0xBB
		bool stacksWhenSnapped;										  // 0xBC
	};

	static_assert(sizeof(PlacementItemData) == 0xC0);
}
