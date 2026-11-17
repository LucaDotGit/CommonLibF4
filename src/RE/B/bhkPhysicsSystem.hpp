#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/H/hkLocalArray.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hknpPhysicsSystem.hpp"
#include "RE/H/hknpPhysicsSystemData.hpp"
#include "RE/N/NiObject.hpp"

namespace RE
{
	class bhkWorld;
	class hknpBodyId;
	class hkTransform;

	class __declspec(novtable) bhkPhysicsSystem : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::bhkPhysicsSystem;
		inline static constexpr const auto& VTABLE = VTABLE::bhkPhysicsSystem;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::bhkPhysicsSystem;

		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
		explicit bhkPhysicsSystem(hknpPhysicsSystemData* a_data)
		{
			using FuncType = void (bhkPhysicsSystem::*)(hknpPhysicsSystemData*);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkPhysicsSystem::ctor);
			std::invoke(FUNC, this, a_data);
		}

		~bhkPhysicsSystem() override; // 0x00

		// add
		virtual auto CreateUniqueSystem(const BSScrapArray<std::uint32_t>* a_bodyIndexA) -> bhkPhysicsSystem*; // 0x28
		virtual auto RemoveSubSystemFromWorld(const hkLocalArray<hknpBodyId>* a_bodyIdA) -> bool;			   // 0x29
		virtual auto CreateInstanceImpl(bhkWorld* a_world, const hkTransform* a_initialTransform)
			-> bhkPhysicsSystem*; // 0x2A

		GAME_HEAP_REDEFINE_NEW(bhkPhysicsSystem);

		void AddToWorld()
		{
			using FuncType = decltype(&bhkPhysicsSystem::AddToWorld);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkPhysicsSystem::AddToWorld);
			std::invoke(FUNC, this);
		}

		void CopyMembers(bhkPhysicsSystem* a_target, NiCloningProcess& a_cloningProcess)
		{
			using FuncType = decltype(&bhkPhysicsSystem::CopyMembers);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkPhysicsSystem::CopyMembers);
			std::invoke(FUNC, this, a_target, a_cloningProcess);
		}

		// members
		hkRefPtr<hknpPhysicsSystemData> systemData; // 0x10
		hkRefPtr<hknpPhysicsSystem> systemInstance; // 0x18
		bool activateOnAdd;							// 0x20
	};

	static_assert(sizeof(bhkPhysicsSystem) == 0x28);
}
