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
	class hkTransformf;

	class __declspec(novtable) bhkNPCollisionObject
		: public bhkNPCollisionObjectBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::bhkNPCollisionObject };
		inline static constexpr auto VTABLE{ VTABLE::bhkNPCollisionObject };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::bhkNPCollisionObject };

		// add
		virtual void CreateInstance(bhkWorld& a_world);			   // 2D
		virtual void AddToWorld(bhkWorld& a_world);				   // 2E
		virtual void RemoveFromWorld();							   // 2F
		virtual bool SetCollisionFilterInfo(CFilter a_filterInfo); // 30

		void CopyMembers(bhkNPCollisionObject* a_dest, NiCloningProcess& a_cloningProcess)
		{
			using FuncType = decltype(&bhkNPCollisionObject::CopyMembers);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkNPCollisionObject::CopyMembers };
			FUNC(this, a_dest, a_cloningProcess);
		}

		[[nodiscard]] static bhkNPCollisionObject* Getbhk(bhkWorld* a_world, hknpBodyId& a_bodyId)
		{
			using FuncType = decltype(&bhkNPCollisionObject::Getbhk);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkNPCollisionObject::Getbhk };
			return std::invoke(FUNC, a_world, a_bodyId);
		}

		[[nodiscard]] const hknpBody* GetBody() const
		{
			using FuncType = decltype(&bhkNPCollisionObject::GetBody);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkNPCollisionObject::GetBody };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] hknpBodyId& GetBodyId(hknpBodyId& a_id) const
		{
			using FuncType = decltype(&bhkNPCollisionObject::GetBodyId);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkNPCollisionObject::GetBodyId };
			return std::invoke(FUNC, this, a_id);
		}

		[[nodiscard]] hknpShape* GetShape() const
		{
			using FuncType = decltype(&bhkNPCollisionObject::GetShape);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkNPCollisionObject::GetShape };
			return std::invoke(FUNC, this);
		}

		bool GetTransform(hkTransformf& a_transform)
		{
			using FuncType = decltype(&bhkNPCollisionObject::GetTransform);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkNPCollisionObject::GetTransform };
			return std::invoke(FUNC, this, a_transform);
		}

		void SetMotionType(hknpMotionPropertiesId::Preset a_type)
		{
			using FuncType = decltype(&bhkNPCollisionObject::SetMotionType);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkNPCollisionObject::SetMotionType };
			FUNC(this, a_type);
		}

		bool SetTransform(hkTransformf& a_transform)
		{
			using FuncType = decltype(&bhkNPCollisionObject::SetTransform);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkNPCollisionObject::SetTransform };
			return std::invoke(FUNC, this, a_transform);
		}

		// members
		NiPointer<bhkPhysicsSystem> system; // 20
		std::uint32_t systemBodyIndex;		// 28
	};
	static_assert(sizeof(bhkNPCollisionObject) == 0x30);
}
