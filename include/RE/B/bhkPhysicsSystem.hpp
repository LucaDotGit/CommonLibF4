#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/H/hkArray.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hknpPhysicsSystem.hpp"
#include "RE/H/hknpPhysicsSystemData.hpp"
#include "RE/N/NiObject.hpp"

namespace RE
{
	class bhkWorld;
	class hknpBodyId;
	class hkTransformf;

	class __declspec(novtable) bhkPhysicsSystem
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::bhkPhysicsSystem };
		inline static constexpr auto VTABLE{ VTABLE::bhkPhysicsSystem };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::bhkPhysicsSystem };

		bhkPhysicsSystem(hknpPhysicsSystemData* a_data)
		{
			using FuncType = void (bhkPhysicsSystem::*)(hknpPhysicsSystemData*);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkPhysicsSystem::ctor };
			FUNC(this, a_data);
		}

		~bhkPhysicsSystem() override; // 00

		// add
		virtual bhkPhysicsSystem* CreateUniqueSystem(const BSScrapArray<std::uint32_t>* a_bodyIndexA);			 // 28
		virtual bool RemoveSubSystemFromWorld(const hkLocalArray<hknpBodyId>* a_bodyIdA);						 // 29
		virtual bhkPhysicsSystem* CreateInstanceImpl(bhkWorld* a_world, const hkTransformf* a_initialTransform); // 2A

		GAME_HEAP_REDEFINE_NEW(bhkPhysicsSystem);

		void AddToWorld()
		{
			using FuncType = decltype(&bhkPhysicsSystem::AddToWorld);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkPhysicsSystem::AddToWorld };
			FUNC(this);
		}

		void CopyMembers(bhkPhysicsSystem* a_dest, NiCloningProcess& a_cloningProcess)
		{
			using FuncType = decltype(&bhkPhysicsSystem::CopyMembers);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkPhysicsSystem::CopyMembers };
			FUNC(this, a_dest, a_cloningProcess);
		}

		// members
		hkRefPtr<hknpPhysicsSystemData> systemData; // 10
		hkRefPtr<hknpPhysicsSystem> systemInstance; // 18
		bool activateOnAdd{ false };				// 20
	};
	static_assert(sizeof(bhkPhysicsSystem) == 0x28);
}
