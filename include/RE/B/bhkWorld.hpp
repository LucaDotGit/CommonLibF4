#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/bhkCharProxyManager.hpp"
#include "RE/B/bhkCharRigidBodyManager.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkVector4f.hpp"
#include "RE/H/hknpWorld.hpp"
#include "RE/N/NiObject.hpp"

namespace RE
{
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

		void AddPhysicsSystem(hknpPhysicsSystem* a_physicsSystem, bool a_startActive)
		{
			using FuncType = decltype(&bhkWorld::AddPhysicsSystem);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::AddPhysicsSystem };
			FUNC(this, a_physicsSystem, a_startActive);
		}

		void RemovePhysicsSystem(hknpPhysicsSystem* a_physicsSystem)
		{
			using FuncType = decltype(&bhkWorld::RemovePhysicsSystem);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::RemovePhysicsSystem };
			FUNC(this, a_physicsSystem);
		}

		static bool RemoveObjects(NiAVObject* a_object, bool a_recurse, bool a_force)
		{
			using FuncType = decltype(&bhkWorld::RemoveObjects);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkWorld::RemoveObjects };
			return std::invoke(FUNC, a_object, a_recurse, a_force);
		}

		// members
		hkRefPtr<hkTaskQueue> taskQueue;							   // 010
		BSTArray<bhkIWorldStepListener*> stepListeners;				   // 018
		hkRefPtr<hkbnpPhysicsInterface> behaviorInterface;			   // 030
		mutable BSReadWriteLock charProxyManagerLock;				   // 038
		mutable BSReadWriteLock charRigidBodyManagerLock;			   // 040
		mutable BSReadWriteLock stepListenerALock;					   // 048
		hkVector4f origin;											   // 050
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
