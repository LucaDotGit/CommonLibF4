#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiQuaternion.hpp"

namespace RE::BSConnectPoint
{
	class Parent : public BSIntrusiveRefCounted // 0x00
	{
	public:
		// members
		BSFixedString parentName; // 0x08
		BSFixedString name;		  // 0x10
		NiQuaternion rotation;	  // 0x18
		NiPoint3 position;		  // 0x28
		REX::Float32 scale;		  // 0x34
	};

	static_assert(sizeof(BSConnectPoint::Parent) == 0x38);
}
