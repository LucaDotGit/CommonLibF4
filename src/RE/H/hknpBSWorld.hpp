#pragma once

#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/H/hkMultiMap.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpWorld.hpp"

namespace RE
{
	class hknpBodyId;

	class __declspec(novtable) hknpBSWorld : public hknpWorld // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpBSWorld;
		inline static constexpr const auto& VTABLE = VTABLE::hknpBSWorld;

		~hknpBSWorld() override; // 0x00

		[[nodiscard]]
		auto AccessMotion(hknpMotionId a_motionId) -> hknpMotion*
		{
			using FuncType = decltype(&hknpBSWorld::AccessMotion);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpBSWorld::AccessMotion);
			return std::invoke(FUNC, this, a_motionId);
		}

		void ActivateBody(hknpBodyId a_bodyId)
		{
			using FuncType = decltype(&hknpBSWorld::ActivateBody);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpBSWorld::ActivateBody);
			std::invoke(FUNC, this, a_bodyId);
		}

		void SetBodyAngularVelocity(hknpBodyId a_bodyId, const hkVector4& a_angularVelocity)
		{
			using FuncType = decltype(&hknpBSWorld::SetBodyAngularVelocity);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpBSWorld::SetBodyAngularVelocity);
			std::invoke(FUNC, this, a_bodyId, a_angularVelocity);
		}

		void SetBodyKeyframed(hknpBodyId a_bodyId, RebuildCachesMode a_cacheBehavior)
		{
			using FuncType = decltype(&hknpBSWorld::SetBodyKeyframed);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpBSWorld::SetBodyKeyframed);
			std::invoke(FUNC, this, a_bodyId, a_cacheBehavior);
		}

		void SetBodyLinearVelocity(hknpBodyId a_bodyId, const hkVector4& a_linearVelocity)
		{
			using FuncType = decltype(&hknpBSWorld::SetBodyLinearVelocity);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpBSWorld::SetBodyLinearVelocity);
			std::invoke(FUNC, this, a_bodyId, a_linearVelocity);
		}

		void SetBodyStatic(hknpBodyId a_bodyId, RebuildCachesMode a_cacheBehavior)
		{
			using FuncType = decltype(&hknpBSWorld::SetBodyStatic);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpBSWorld::SetBodyStatic);
			std::invoke(FUNC, this, a_bodyId, a_cacheBehavior);
		}

		void SetBodyVelocity(hknpBodyId a_bodyId, const hkVector4& a_linearVelocity, const hkVector4& a_angularVelocity)
		{
			using FuncType = decltype(&hknpBSWorld::SetBodyVelocity);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpBSWorld::SetBodyVelocity);
			std::invoke(FUNC, this, a_bodyId, a_linearVelocity, a_angularVelocity);
		}

		// members
		void* bsUserData;												  // 0x6C0 - To-Do
		mutable BSReadWriteLock worldLock;								  // 0x6C8
		BSTSet<hknpBodyId> activateBodyPostCollideSet;					  // 0x6E0
		mutable BSSpinLock activateBodyPostCollideLock;					  // 0x6F8
		hkMultiMap<std::uint32_t, std::uint32_t> constrainedBodyFromBody; // 0x700
	};

	static_assert(sizeof(hknpBSWorld) == 0x730);
}
