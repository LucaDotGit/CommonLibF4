#pragma once

#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class BSPathingLockData;

	class BSPathingActorAttributes
	{
	public:
		enum class ACTOR_SHAPE_TYPE : std::int32_t
		{
			Point = 0,
			Biped = 1,
			Quadruped = 2
		};

		enum class LOCK_HANDLING_TYPE : std::int32_t
		{
			Ignore = 4,
			CantOpen = 8,
			UseLockData = 12
		};

		enum class ATTRIBUTE : std::int32_t
		{
			WaitIfPlayerWaits = 128
		};

		enum class TRAVERSAL_TYPE : std::int32_t
		{
			None = 0,
			CanWalk = 1 << 0,
			CanSwim = 1 << 1,
			CanFly = 1 << 2,
			CanFloat = 1 << 3,
			IsLarge = 1 << 4,
			CanJump = 1 << 5
		};

		// members
		REX::Float32 radius;						 // 0x00
		REX::Float32 height;						 // 0x04
		REX::Float32 floatHeight;					 // 0x08
		BSTSmartPointer<BSPathingLockData> lockData; // 0x10
		std::uint32_t data;							 // 0x18
		std::uint8_t traversalFlags;				 // 0x1C
	};

	static_assert(sizeof(BSPathingActorAttributes) == 0x20);
}
