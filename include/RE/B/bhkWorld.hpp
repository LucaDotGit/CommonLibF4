#pragma once

#include "RE/B/BSSpinLock.hpp"
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

	class __declspec(novtable) bhkWorld
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::bhkWorld };
		inline static constexpr auto VTABLE{ VTABLE::bhkWorld };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::bhkWorld };

		~bhkWorld() override; // 00

		// add
		virtual bool Update(std::uint32_t a_updateFlags); // 28
		virtual void Init(const hknpWorldCinfo& a_info);  // 29

		static bool Activate(NiAVObject* a_object, bool a_activate, bool a_recurse, bool a_force)
		{
			using FuncType = decltype(&bhkWorld::Activate);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::Activate };
			return std::invoke(FUNC, a_object, a_activate, a_recurse, a_force);
		}

		bool AddObjects(NiAVObject* a_object, bool a_recurse, bool a_notify, std::uint32_t a_group, bool a_force, const bhkIAddToWorld* a_addToWorld)
		{
			using FuncType = decltype(&bhkWorld::AddObjects);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::AddObjects };
			return std::invoke(FUNC, this, a_object, a_recurse, a_notify, a_group, a_force, a_addToWorld);
		}

		void AddPhysicsSystem(hknpPhysicsSystem* a_physicsSystem, bool a_startActive)
		{
			using FuncType = decltype(&bhkWorld::AddPhysicsSystem);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::AddPhysicsSystem };
			std::invoke(FUNC, this, a_physicsSystem, a_startActive);
		}

		[[nodiscard]] bool IsBodyAdded(hknpBodyId a_bodyId)
		{
			using FuncType = decltype(&bhkWorld::IsBodyAdded);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::IsBodyAdded };
			return std::invoke(FUNC, this, a_bodyId);
		}

		static bool Enable(NiAVObject* a_object, bool a_enable, bool a_recurse, bool a_force)
		{
			using FuncType = decltype(&bhkWorld::Enable);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::Enable };
			return std::invoke(FUNC, a_object, a_enable, a_recurse, a_force);
		}

		static bool EnableCollision(NiAVObject* a_object, bool a_enable, bool a_recurse, bool a_force)
		{
			using FuncType = decltype(&bhkWorld::EnableCollision);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::EnableCollision };
			return std::invoke(FUNC, a_object, a_enable, a_recurse, a_force);
		}

		[[nodiscard]] static bool IsActive(NiAVObject* a_object, bool a_recurse, bool a_force)
		{
			using FuncType = decltype(&bhkWorld::IsActive);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::IsActive };
			return std::invoke(FUNC, a_object, a_recurse, a_force);
		}

		static bool RemoveObjects(NiAVObject* a_object, bool a_recurse, bool a_force)
		{
			using FuncType = decltype(&bhkWorld::RemoveObjects);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::RemoveObjects };
			return std::invoke(FUNC, a_object, a_recurse, a_force);
		}

		void RemovePhysicsSystem(hknpPhysicsSystem* a_physicsSystem)
		{
			using FuncType = decltype(&bhkWorld::RemovePhysicsSystem);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::RemovePhysicsSystem };
			std::invoke(FUNC, this, a_physicsSystem);
		}

		static bool SetCollisionGroup(NiAVObject* a_object, std::uint32_t a_group, bool a_recurse, bool a_force)
		{
			using FuncType = decltype(&bhkWorld::SetCollisionGroup);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::SetCollisionGroup };
			return std::invoke(FUNC, a_object, a_group, a_recurse, a_force);
		}

		static bool SetDismemberedLimb(NiAVObject* a_object, bool a_tf, bool a_recurse)
		{
			using FuncType = decltype(&bhkWorld::SetDismemberedLimb);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::SetDismemberedLimb };
			return std::invoke(FUNC, a_object, a_tf, a_recurse);
		}

		static bool SetMotion(NiAVObject* a_object, std::uint32_t a_type, bool a_recurse, bool a_force, bool a_allowActivate)
		{
			using FuncType = decltype(&bhkWorld::SetMotion);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::SetMotion };
			return std::invoke(FUNC, a_object, a_type, a_recurse, a_force, a_allowActivate);
		}

		// members
		hkRefPtr<hkTaskQueue> taskQueue;							   // 010
		BSTArray<bhkIWorldStepListener*> stepListeners;				   // 018
		hkRefPtr<hkbnpPhysicsInterface> behaviorInterface;			   // 030
		mutable BSReadWriteLock charProxyManagerLock;				   // 038
		mutable BSReadWriteLock charRigidBodyManagerLock;			   // 040
		mutable BSReadWriteLock stepListenerALock;					   // 048
		hkVector4 origin;											   // 050
		hkRefPtr<hknpBSWorld> worldNP;								   // 060
		bhkCharProxyManager charProxyManager;						   // 068
		bhkCharRigidBodyManager charRigidBodyManager;				   // 0D8
		hkRefPtr<hclBSWorld> clothWorld;							   // 148
		std::byte* clothStepBuffer;									   // 150
		std::int32_t clothStepBufferSize;							   // 158
		REX::Enum<hknpWorld::AdditionMode, std::int32_t> additionMode; // 15C
		bhkTrapListener* trapListener;								   // 160
		REX::Float32 originalTau;									   // 168
		REX::Float32 originalDamping;								   // 16C
		bool globalWindActivated;									   // 170
		bool added;													   // 171
		bool enabled;												   // 172
	};
	static_assert(sizeof(bhkWorld) == 0x180);
}
