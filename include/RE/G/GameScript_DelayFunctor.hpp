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
	class __declspec(novtable) DelayFunctor
		: public BSIntrusiveRefCounted // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__DelayFunctor };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__DelayFunctor };

		enum class FunctorType : std::int32_t
		{
			kMoveTo = 0,
			kMoveToOwnEditorLoc = 1,
			kDamageObject = 2,
			kEnable = 3,
			kDisable = 4,
			kDelete = 5,
			kSetPosition = 6,
			kSetAngle = 7,
			kSetMotionType = 8,
			kNonLatentDelete = 9,
			kMoveToPackLoc = 10,
			kSetScale = 11,
			kDropObject = 12,
			kAttachAshPile = 13,
			kAddRemoveConstraint = 14,
			kAddRemoveRagdoll = 15,
			kApplyHavokImpulse = 16,
			kResetRefr = 17,
			kSendPlayerToJail = 18,
			kAddItem = 19,
			kResurrect = 20,
			kCast = 21,
			kScrollCast = 22,
			kRemoveItem = 23,
			kWaitFor3D = 24,
			kPlayBink = 25,
			kMoveToNearestNavmesh = 26,
			kClearDestruction = 27,
			kWaitForResourceRecalc = 28,
			kRemoveComponent = 29,
			kDropRef = 30
		};

		virtual ~DelayFunctor(); // 00

		// add
		[[nodiscard]] virtual BSScript::Variable operator()() = 0;													 // 01
		[[nodiscard]] virtual bool IsLatent() const = 0;															 // 02
		[[nodiscard]] virtual bool WantsRequeue() const { return false; }											 // 03
		[[nodiscard]] virtual FunctorType GetType() const = 0;														 // 04
		virtual bool SaveImpl(BSStorage& a_storage) const = 0;														 // 05
		virtual bool LoadImpl(const BSStorage& a_storage, std::uint32_t a_scriptSaveVersion, bool& a_dataValid) = 0; // 06

		// members
		BSScript::StackID stackID{ 0 }; // 0C
	};
	static_assert(sizeof(DelayFunctor) == 0x10);
}
