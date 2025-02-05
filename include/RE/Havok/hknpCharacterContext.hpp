#pragma once

#include "RE/Havok/hkBaseTypes.hpp"
#include "RE/Havok/hkReferencedObject.hpp"
#include "RE/Havok/hkVector4.hpp"
#include "RE/Havok/hknpCharacterState.hpp"

namespace RE
{
	class hknpCharacterStateManager;

	class __declspec(novtable) hknpCharacterContext
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpCharacterContext };
		inline static constexpr auto VTABLE{ VTABLE::hknpCharacterContext };

		enum class CharacterType
		{
			kProxy,
			kRigidBody
		};

		// members
		hkEnum<CharacterType, std::uint32_t> characterType;								 // 10
		hknpCharacterStateManager* stateManager;										 // 18
		hkEnum<hknpCharacterState::hknpCharacterStateType, std::uint32_t> currentState;	 // 20
		hkEnum<hknpCharacterState::hknpCharacterStateType, std::uint32_t> previousState; // 24
		hkBool filterEnable;															 // 28
		float maxLinearAcceleration;													 // 2C
		float maxLinearSpeed;															 // 30
		float gain;																		 // 34
		hkVector4f previousSurfaceVelocity;												 // 40
		std::int32_t numUpdatesInCurrentState;											 // 50
	};
	static_assert(sizeof(hknpCharacterContext) == 0x60);
}
