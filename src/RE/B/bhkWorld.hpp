#pragma once

#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/bhkCharProxyManager.hpp"
#include "RE/B/bhkCharRigidBodyManager.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpWorld.hpp"
#include "RE/N/NiObject.hpp"

namespace RE
{
	class bhkIAddToWorld;
	class bhkTrapListener;
	class hclBSWorld;
	class hkbnpPhysicsInterface;
	class hknpBSWorld;
	class hknpPhysicsSystem;
	class hkTaskQueue;
	class NiAVObject;

	class __declspec(novtable) bhkWorld : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::bhkWorld;
		inline static constexpr const auto& VTABLE = VTABLE::bhkWorld;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::bhkWorld;

		~bhkWorld() override; // 0x00

		// add
		virtual auto Update(std::uint32_t a_updateFlags) -> bool; // 0x28
		virtual void Init(const hknpWorldCinfo& a_info);		  // 0x29

		static auto Activate(NiAVObject* a_object, bool a_activate, bool a_recurse, bool a_force) -> bool
		{
			using FuncType = decltype(&bhkWorld::Activate);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkWorld::Activate);
			return std::invoke(FUNC, a_object, a_activate, a_recurse, a_force);
		}

		auto AddObjects(
			NiAVObject* a_object,
			bool a_recurse,
			bool a_notify,
			std::uint32_t a_group,
			bool a_force,
			const bhkIAddToWorld* a_addToWorld) -> bool
		{
			using FuncType = decltype(&bhkWorld::AddObjects);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkWorld::AddObjects);
			return std::invoke(FUNC, this, a_object, a_recurse, a_notify, a_group, a_force, a_addToWorld);
		}

		void AddPhysicsSystem(hknpPhysicsSystem* a_physicsSystem, bool a_startActive)
		{
			using FuncType = decltype(&bhkWorld::AddPhysicsSystem);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkWorld::AddPhysicsSystem);
			std::invoke(FUNC, this, a_physicsSystem, a_startActive);
		}

		[[nodiscard]]
		auto IsBodyAdded(hknpBodyId a_bodyId) -> bool
		{
			using FuncType = decltype(&bhkWorld::IsBodyAdded);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkWorld::IsBodyAdded);
			return std::invoke(FUNC, this, a_bodyId);
		}

		static auto Enable(NiAVObject* a_object, bool a_enable, bool a_recurse, bool a_force) -> bool
		{
			using FuncType = decltype(&bhkWorld::Enable);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkWorld::Enable);
			return std::invoke(FUNC, a_object, a_enable, a_recurse, a_force);
		}

		static auto EnableCollision(NiAVObject* a_object, bool a_enable, bool a_recurse, bool a_force) -> bool
		{
			using FuncType = decltype(&bhkWorld::EnableCollision);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkWorld::EnableCollision);
			return std::invoke(FUNC, a_object, a_enable, a_recurse, a_force);
		}

		[[nodiscard]]
		static auto IsActive(NiAVObject* a_object, bool a_recurse, bool a_force) -> bool
		{
			using FuncType = decltype(&bhkWorld::IsActive);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkWorld::IsActive);
			return std::invoke(FUNC, a_object, a_recurse, a_force);
		}

		static auto RemoveObjects(NiAVObject* a_object, bool a_recurse, bool a_force) -> bool
		{
			using FuncType = decltype(&bhkWorld::RemoveObjects);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkWorld::RemoveObjects);
			return std::invoke(FUNC, a_object, a_recurse, a_force);
		}

		void RemovePhysicsSystem(hknpPhysicsSystem* a_physicsSystem)
		{
			using FuncType = decltype(&bhkWorld::RemovePhysicsSystem);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkWorld::RemovePhysicsSystem);
			std::invoke(FUNC, this, a_physicsSystem);
		}

		static auto SetCollisionGroup(NiAVObject* a_object, std::uint32_t a_group, bool a_recurse, bool a_force) -> bool
		{
			using FuncType = decltype(&bhkWorld::SetCollisionGroup);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkWorld::SetCollisionGroup);
			return std::invoke(FUNC, a_object, a_group, a_recurse, a_force);
		}

		static auto SetDismemberedLimb(NiAVObject* a_object, bool a_tf, bool a_recurse) -> bool
		{
			using FuncType = decltype(&bhkWorld::SetDismemberedLimb);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkWorld::SetDismemberedLimb);
			return std::invoke(FUNC, a_object, a_tf, a_recurse);
		}

		static auto SetMotion(
			NiAVObject* a_object,
			std::uint32_t a_type,
			bool a_recurse,
			bool a_force,
			bool a_allowActivate) -> bool
		{
			using FuncType = decltype(&bhkWorld::SetMotion);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkWorld::SetMotion);
			return std::invoke(FUNC, a_object, a_type, a_recurse, a_force, a_allowActivate);
		}

		// members
		hkRefPtr<hkTaskQueue> taskQueue;							   // 0x010
		BSTArray<bhkIWorldStepListener*> stepListeners;				   // 0x018
		hkRefPtr<hkbnpPhysicsInterface> behaviorInterface;			   // 0x030
		mutable BSReadWriteLock charProxyManagerLock;				   // 0x038
		mutable BSReadWriteLock charRigidBodyManagerLock;			   // 0x040
		mutable BSReadWriteLock stepListenerALock;					   // 0x048
		hkVector4 origin;											   // 0x050
		hkRefPtr<hknpBSWorld> worldNP;								   // 0x060
		bhkCharProxyManager charProxyManager;						   // 0x068
		bhkCharRigidBodyManager charRigidBodyManager;				   // 0x0D8
		hkRefPtr<hclBSWorld> clothWorld;							   // 0x148
		std::byte* clothStepBuffer;									   // 0x150
		std::int32_t clothStepBufferSize;							   // 0x158
		REX::Enum<hknpWorld::AdditionMode, std::int32_t> additionMode; // 0x15C
		bhkTrapListener* trapListener;								   // 0x160
		REX::Float32 originalTau;									   // 0x168
		REX::Float32 originalDamping;								   // 0x16C
		bool globalWindActivated;									   // 0x170
		bool added;													   // 0x171
		bool enabled;												   // 0x172
	};

	static_assert(sizeof(bhkWorld) == 0x180);
}
