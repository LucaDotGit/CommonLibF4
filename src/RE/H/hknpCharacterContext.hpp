#pragma once

#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpCharacterState.hpp"

namespace RE
{
	class hknpCharacterStateManager;

	class __declspec(novtable) hknpCharacterContext : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpCharacterContext;
		inline static constexpr const auto& VTABLE = VTABLE::hknpCharacterContext;

		enum class CharacterType : std::int32_t
		{
			Character_Proxy = 0,
			Character_RigidBody = 1
		};

		~hknpCharacterContext() override; // 0x00

		REX::Enum<CharacterType, std::int32_t> characterType;							   // 0x10
		hknpCharacterStateManager* stateManager;										   // 0x18
		REX::Enum<hknpCharacterState::hknpCharacterStateType, std::int32_t> currentState;  // 0x20
		REX::Enum<hknpCharacterState::hknpCharacterStateType, std::int32_t> previousState; // 0x24
		bool filterEnable;																   // 0x28
		REX::Float32 maxLinearAcceleration;												   // 0x2C
		REX::Float32 maxLinearSpeed;													   // 0x30
		REX::Float32 gain;																   // 0x34
		hkVector4 previousSurfaceVelocity;												   // 0x40
		std::int32_t numUpdatesInCurrentState;											   // 0x50
	};

	static_assert(sizeof(hknpCharacterContext) == 0x60);
}
