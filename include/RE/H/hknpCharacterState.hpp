#pragma once

#include "RE/H/hkReferencedObject.hpp"

namespace RE
{
	class __declspec(novtable) hknpCharacterState
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpCharacterState };
		inline static constexpr auto VTABLE{ VTABLE::hknpCharacterState };

		enum class hknpCharacterStateType : std::int32_t
		{
			kOnGround = 0,
			kJumping = 1,
			kInAir = 2,
			kClimbing = 3,
			kFlying = 4,
			kUserState0 = 5,
			kUserState1 = 6,
			kUserState2 = 7,
			kUserState3 = 8,
			kUserState4 = 9,
			kUserState5 = 10,
			kMaxStateID = 11
		};

		~hknpCharacterState() override; // 00
	};
	static_assert(sizeof(hknpCharacterState) == 0x10);
}
