#pragma once

#include "RE/H/hkReferencedObject.hpp"

namespace RE
{
	class __declspec(novtable) hknpCharacterState : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpCharacterState;
		inline static constexpr const auto& VTABLE = VTABLE::hknpCharacterState;

		enum class hknpCharacterStateType : std::int32_t
		{
			OnGround = 0,
			Jumping = 1,
			InAir = 2,
			Climbing = 3,
			Flying = 4,
			UserState0 = 5,
			UserState1 = 6,
			UserState2 = 7,
			UserState3 = 8,
			UserState4 = 9,
			UserState5 = 10,
			MaxStateID = 11
		};

		~hknpCharacterState() override; // 0x00
	};

	static_assert(sizeof(hknpCharacterState) == 0x10);
}
