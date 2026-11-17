#pragma once

#include "RE/B/bhkNPCollisionObjectBase.hpp"
#include "RE/H/hknpMotionPropertiesId.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class bhkPhysicsSystem;
	class bhkWorld;
	class CFilter;
	class hknpBody;
	class hknpBodyId;
	class hknpShape;
	class hkTransform;

	class __declspec(novtable) bhkNPCollisionObject : public bhkNPCollisionObjectBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::bhkNPCollisionObject;
		inline static constexpr const auto& VTABLE = VTABLE::bhkNPCollisionObject;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::bhkNPCollisionObject;

		// add
		virtual void CreateInstance(bhkWorld& a_world);					   // 0x2D
		virtual void AddToWorld(bhkWorld& a_world);						   // 0x2E
		virtual void RemoveFromWorld();									   // 0x2F
		virtual auto SetCollisionFilterInfo(CFilter a_filterInfo) -> bool; // 0x30

		[[nodiscard]]
		static auto CreateObject() -> bhkNPCollisionObject*
		{
			using FuncType = decltype(&bhkNPCollisionObject::CreateObject);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkNPCollisionObject::CreateObject);
			return std::invoke(FUNC);
		}

		void CopyMembers(bhkNPCollisionObject* a_target, NiCloningProcess& a_cloningProcess)
		{
			using FuncType = decltype(&bhkNPCollisionObject::CopyMembers);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkNPCollisionObject::CopyMembers);
			std::invoke(FUNC, this, a_target, a_cloningProcess);
		}

		[[nodiscard]]
		static auto Getbhk(bhkWorld* a_world, const hknpBodyId& a_bodyId) -> bhkNPCollisionObject*
		{
			using FuncType = decltype(&bhkNPCollisionObject::Getbhk);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkNPCollisionObject::Getbhk);
			return std::invoke(FUNC, a_world, a_bodyId);
		}

		[[nodiscard]]
		auto GetBody() const -> const hknpBody*
		{
			using FuncType = decltype(&bhkNPCollisionObject::GetBody);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkNPCollisionObject::GetBody);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetBodyId(const hknpBodyId& a_bodyId) const -> hknpBodyId&
		{
			using FuncType = decltype(&bhkNPCollisionObject::GetBodyId);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkNPCollisionObject::GetBodyId);
			return std::invoke(FUNC, this, a_bodyId);
		}

		[[nodiscard]]
		auto GetShape() const -> hknpShape*
		{
			using FuncType = decltype(&bhkNPCollisionObject::GetShape);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkNPCollisionObject::GetShape);
			return std::invoke(FUNC, this);
		}

		auto GetTransform(hkTransform& a_outTransform) -> bool
		{
			using FuncType = decltype(&bhkNPCollisionObject::GetTransform);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkNPCollisionObject::GetTransform);
			return std::invoke(FUNC, this, a_outTransform);
		}

		void SetMotionType(hknpMotionPropertiesId::Preset a_type)
		{
			using FuncType = decltype(&bhkNPCollisionObject::SetMotionType);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkNPCollisionObject::SetMotionType);
			std::invoke(FUNC, this, a_type);
		}

		auto SetTransform(const hkTransform& a_transform) -> bool
		{
			using FuncType = decltype(&bhkNPCollisionObject::SetTransform);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkNPCollisionObject::SetTransform);
			return std::invoke(FUNC, this, a_transform);
		}

		// members
		NiPointer<bhkPhysicsSystem> system; // 0x20
		std::uint32_t systemBodyIndex;		// 0x28
	};

	static_assert(sizeof(bhkNPCollisionObject) == 0x30);
}
