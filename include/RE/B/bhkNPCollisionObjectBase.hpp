#pragma once

#include "RE/N/NiCollisionObject.hpp"

namespace RE
{
	class __declspec(novtable) bhkNPCollisionObjectBase
		: public NiCollisionObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::bhkNPCollisionObjectBase };
		inline static constexpr auto VTABLE{ VTABLE::bhkNPCollisionObjectBase };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::bhkNPCollisionObjectBase };

		enum class TRANSCHANGEFLAGS : std::uint32_t
		{
			kNone = 0,
			kPos = 1,
			kRot = 2
		};

		enum class Flags : std::uint16_t
		{
			kNone = 0,
			kNotifyPosition = 1 << 0,
			kSetLocalPosition = 1 << 1,
			kUseVelocityPosition = 1 << 2,
			kResetPosition = 1 << 3,
			kSyncOnUpdate = 1 << 4,
			kAimTargeted = 1 << 5,
			kDismemberedLimb = 1 << 6
		};

		// add
		virtual void LockMotionImpl() = 0; // 2C

		// members
		REX::EnumSet<Flags, std::uint16_t> flags; // 18
	};
	static_assert(sizeof(bhkNPCollisionObjectBase) == 0x20);
}
