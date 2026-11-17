#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"

namespace RE
{
	class BSStorage;
}

namespace RE::BSScript
{
	class Variable;
}

namespace RE::GameScript
{
	class __declspec(novtable) DelayFunctor : public BSIntrusiveRefCounted // 0x08
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__DelayFunctor;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__DelayFunctor;

		enum class FunctorType : std::int32_t
		{
			MoveTo = 0,
			MoveToOwnEditorLoc = 1,
			DamageObject = 2,
			Enable = 3,
			Disable = 4,
			Delete = 5,
			SetPosition = 6,
			SetAngle = 7,
			SetMotionType = 8,
			NonLatentDelete = 9,
			MoveToPackLoc = 10,
			SetScale = 11,
			DropObject = 12,
			AttachAshPile = 13,
			AddRemoveConstraint = 14,
			AddRemoveRagdoll = 15,
			ApplyHavokImpulse = 16,
			ResetRefr = 17,
			SendPlayerToJail = 18,
			AddItem = 19,
			Resurrect = 20,
			Cast = 21,
			ScrollCast = 22,
			RemoveItem = 23,
			WaitFor3D = 24,
			PlayBink = 25,
			MoveToNearestNavmesh = 26,
			ClearDestruction = 27,
			WaitForResourceRecalc = 28,
			RemoveComponent = 29,
			DropRef = 30
		};

		virtual ~DelayFunctor(); // 0x00

		// add
		[[nodiscard]]
		virtual auto operator()() -> BSScript::Variable = 0; // 0x01
		[[nodiscard]]
		virtual auto IsLatent() const -> bool = 0; // 0x02

		[[nodiscard]]
		virtual auto WantsRequeue() const -> bool // 0x03
		{
			return false;
		}

		[[nodiscard]]
		virtual auto GetType() const -> FunctorType = 0;			   // 0x04
		virtual auto SaveImpl(BSStorage& a_storage) const -> bool = 0; // 0x05
		virtual auto LoadImpl(
			const BSStorage& a_storage,
			std::uint32_t a_scriptSaveVersion,
			bool& a_dataValid) -> bool = 0; // 0x06

		// members
		BSScript::StackID stackID{0}; // 0x0C
	};

	static_assert(sizeof(DelayFunctor) == 0x10);
}
