#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSpinLock.hpp"

namespace RE
{
	class ActorPackageData;

	class ActorPackage
	{
	public:
		// members
		mutable BSSpinLock packageLock;		 // 0x00
		TESPackage* package;				 // 0x08
		ActorPackageData* data;				 // 0x10
		ObjectRefHandle target;				 // 0x18
		std::int32_t currentProcedureIndex;	 // 0x1C
		REX::Float32 packageStartTime;		 // 0x20
		std::uint32_t modifiedPackageFlag;	 // 0x24
		std::uint16_t modifiedInterruptFlag; // 0x28
		std::int8_t actorPackageFlags;		 // 0x2A
		std::int8_t preferredSpeed;			 // 0x2B
	};

	static_assert(sizeof(ActorPackage) == 0x30);
}
