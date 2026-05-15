#pragma once

#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpCharacterState.hpp"

namespace RE
{
	class hknpCharacterStateManager;

	class __declspec(novtable) hknpCharacterContext
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpCharacterContext };
		inline static constexpr auto VTABLE{ VTABLE::hknpCharacterContext };

		enum class CharacterType : std::int32_t
		{
			kCharacter_Proxy = 0,
			kCharacter_RigidBody = 1
		};

		~hknpCharacterContext() override; // 00

		REX::Enum<CharacterType, std::int32_t> characterType;							   // 10
		hknpCharacterStateManager* stateManager;										   // 18
		REX::Enum<hknpCharacterState::hknpCharacterStateType, std::int32_t> currentState;  // 20
		REX::Enum<hknpCharacterState::hknpCharacterStateType, std::int32_t> previousState; // 24
		bool filterEnable;																   // 28
		REX::Float32 maxLinearAcceleration;												   // 2C
		REX::Float32 maxLinearSpeed;													   // 30
		REX::Float32 gain;																   // 34
		hkVector4 previousSurfaceVelocity;												   // 40
		std::int32_t numUpdatesInCurrentState;											   // 50
	};
	static_assert(sizeof(hknpCharacterContext) == 0x60);
}
