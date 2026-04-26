#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiQuaternion.hpp"

namespace RE::BSConnectPoint
{
	class Parent
		: public BSIntrusiveRefCounted // 00
	{
	public:
		// members
		BSFixedString parentName; // 08
		BSFixedString name;		  // 10
		NiQuaternion rot;		  // 18
		NiPoint3 pos;			  // 28
		REX::Float32 scale;		  // 34
	};
	static_assert(sizeof(BSConnectPoint::Parent) == 0x38);
}
