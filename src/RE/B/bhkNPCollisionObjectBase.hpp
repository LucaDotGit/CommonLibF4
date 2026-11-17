#pragma once

#include "RE/N/NiCollisionObject.hpp"

namespace RE
{
	class __declspec(novtable) bhkNPCollisionObjectBase : public NiCollisionObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::bhkNPCollisionObjectBase;
		inline static constexpr const auto& VTABLE = VTABLE::bhkNPCollisionObjectBase;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::bhkNPCollisionObjectBase;

		enum class TRANSCHANGEFLAGS : std::uint32_t
		{
			None = 0,
			Pos = 1,
			Rot = 2
		};

		enum class Flags : std::uint16_t
		{
			None = 0,
			NotifyPosition = 1 << 0,
			SetLocalPosition = 1 << 1,
			UseVelocityPosition = 1 << 2,
			ResetPosition = 1 << 3,
			SyncOnUpdate = 1 << 4,
			AimTargeted = 1 << 5,
			DismemberedLimb = 1 << 6
		};

		// add
		virtual void LockMotionImpl() = 0; // 0x2C

		// members
		REX::EnumSet<Flags, std::uint16_t> flags; // 0x18
	};

	static_assert(sizeof(bhkNPCollisionObjectBase) == 0x20);
}
