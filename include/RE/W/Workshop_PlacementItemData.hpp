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
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::PlacementItemData::Set };
			std::invoke(FUNC, this, a_ref);
		}

		// members
		ObjectRefHandle placementItem;								  // 00
		BSTArray<hknpShape*> dropProxies;							  // 08
		BSTArray<bhkNPCollisionObject*> bodies;						  // 20
		BSTArray<BSTSmartPointer<BSConnectPoint::Parent>> snapPoints; // 38
		BSTSmartPointer<BSConnectPoint::Parent> recenterPoint;		  // 50
		hkAabb dropProxyExtends;									  // 60
		REX::Float32 sinkDepth;										  // 80
		REX::Float32 zOffset;										  // 84
		REX::Float32 intersectTolerance;							  // 88
		REX::Float32 snapPointQueryRadius;							  // 8C
		REX::Float32 forwardCastZRot;								  // 90
		REX::Float32 xyBoundOverride;								  // 94
		REX::Float32 xBoundMinOverride;								  // 98
		REX::Float32 xBoundMaxOverride;								  // 9C
		REX::Float32 yBoundMinOverride;								  // A0
		REX::Float32 yBoundMaxOverride;								  // A4
		REX::Float32 zBoundMinOverride;								  // A8
		REX::Float32 zBoundMaxOverride;								  // AC
		std::uint32_t dropProxyIndex;								  // B0
		bool anythingIsGround;										  // B4
		bool clampUp;												  // B5
		bool forwardCast;											  // B6
		bool recenter;												  // B7
		bool ignoreSimpleIntersection;								  // B8
		bool allowUnsupportedStacking;								  // B9
		bool isSet;													  // BA
		bool mustSnap;												  // BB
		bool stacksWhenSnapped;										  // BC
	};
	static_assert(sizeof(PlacementItemData) == 0xC0);
}
