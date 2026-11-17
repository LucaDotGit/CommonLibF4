#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BSAnimationGraphChannel;
	class BSAnimationGraphManager;
	class BShkbAnimationGraph;
	class NiAVObject;

	class __declspec(novtable) IAnimationGraphManagerHolder
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IAnimationGraphManagerHolder;
		inline static constexpr const auto& VTABLE = VTABLE::IAnimationGraphManagerHolder;

		virtual ~IAnimationGraphManagerHolder() = default; // 0x00

		// add
		virtual auto NotifyAnimationGraphImpl(const BSFixedString& a_eventName) -> bool; // 0x01
		virtual void EventSuccessfullyProcessed();										 // 0x02 - { return; }
		virtual void ModifyInitialAnimationStateImpl(bool a_unk01);						 // 0x03 - { return; }
		virtual auto GetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) const
			-> bool = 0; // 0x04
		virtual auto SetAnimationGraphManagerImpl(const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr)
			-> bool = 0; // 0x05
		virtual auto PopulateGraphNodesToTarget(BSScrapArray<NiAVObject*>& a_nodesToAnimate) const
			-> bool; // 0x06 - { return false; }
		virtual auto ConstructAnimationGraph(BSTSmartPointer<BShkbAnimationGraph>& a_animGraph) -> bool = 0; // 0x07
		virtual auto InitializeAnimationGraphVariables(const BSTSmartPointer<BShkbAnimationGraph>& a_newGraph) const
			-> bool; // 0x08 - { return true; }
		virtual auto SetupAnimEventSinks(const BSTSmartPointer<BShkbAnimationGraph>& a_newGraph)
			-> bool;							  // 0x09 - { return true; }
		virtual void DoFailedToLoadGraph() const; // 0x0A - { return; }
		virtual auto CreateAnimationChannels(BSScrapArray<BSTSmartPointer<BSAnimationGraphChannel>>& a_channels)
			-> bool; // 0x0B - { return false; }
		virtual void PostCreateAnimationGraphManager(
			BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr); // 0x0C - { return; }
		virtual void PostChangeAnimationManager(
			const BSTSmartPointer<BSAnimationGraphManager>& a_newAnimGraphMgr,
			const BSTSmartPointer<BSAnimationGraphManager>& a_oldAnimGraphMgr); // 0x0D - { return; }
		virtual auto ShouldUpdateAnimation() -> bool;							// 0x0E - { return true; }
		virtual auto GetGraphVariableCacheSize() const -> std::uint32_t;		// 0x0F - { return 0; }
		virtual auto GetGraphVariableImpl(std::uint32_t a_graphVarID, REX::Float32& a_outValue) const
			-> bool; // 0x10 - { return false; }
		virtual auto GetGraphVariableImpl(std::uint32_t a_graphVarID, bool& a_outValue) const
			-> bool; // 0x11 - { return false; }
		virtual auto GetGraphVariableImpl(std::uint32_t a_graphVarID, std::int32_t& a_outValue) const
			-> bool; // 0x12 - { return false; }
		virtual auto GetGraphVariableImplFloat(const BSFixedString& a_variable, REX::Float32& a_outValue) const
			-> bool; // 0x13
		virtual auto GetGraphVariableImplInt(const BSFixedString& a_variable, std::int32_t& a_outValue) const
			-> bool;																							// 0x14
		virtual auto GetGraphVariableImplBool(const BSFixedString& a_variable, bool& a_outValue) const -> bool; // 0x15
		virtual void PreUpdateAnimationGraphManager(
			const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) const; // 0x16 - { return; }
		virtual void PostUpdateAnimationGraphManager(
			const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) const; // 0x17 - { return; }
		virtual void PreLoadAnimationGraphManager(
			const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr); // 0x18 - { return; }
		virtual void PostLoadAnimationGraphManager(
			const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr); // 0x19 - { return; }

		GAME_HEAP_REDEFINE_NEW(IAnimationGraphManagerHolder);

		auto SetGraphVariableBool(const BSFixedString& a_variable, bool a_var) -> bool
		{
			using FuncType = decltype(&IAnimationGraphManagerHolder::SetGraphVariableBool);
			static const auto FUNC = REL::Relocation<FuncType>(ID::IAnimationGraphManagerHolder::SetGraphVariableBool);
			return std::invoke(FUNC, this, a_variable, a_var);
		}

		auto SetGraphVariableFloat(const BSFixedString& a_variable, REX::Float32 a_var) -> bool
		{
			using FuncType = decltype(&IAnimationGraphManagerHolder::SetGraphVariableFloat);
			static const auto FUNC = REL::Relocation<FuncType>(ID::IAnimationGraphManagerHolder::SetGraphVariableFloat);
			return std::invoke(FUNC, this, a_variable, a_var);
		}

		auto SetGraphVariableInt(const BSFixedString& a_variable, std::int32_t a_var) -> bool
		{
			using FuncType = decltype(&IAnimationGraphManagerHolder::SetGraphVariableInt);
			static const auto FUNC = REL::Relocation<FuncType>(ID::IAnimationGraphManagerHolder::SetGraphVariableInt);
			return std::invoke(FUNC, this, a_variable, a_var);
		}

		auto RevertAnimationGraphManager(bool a_performModifyInitialAnimationStateC = true) -> bool
		{
			using FuncType = decltype(&IAnimationGraphManagerHolder::RevertAnimationGraphManager);
			static const auto FUNC =
				REL::Relocation<FuncType>{ID::IAnimationGraphManagerHolder::RevertAnimationGraphManager};
			return std::invoke(FUNC, this, a_performModifyInitialAnimationStateC);
		}
	};

	static_assert(sizeof(IAnimationGraphManagerHolder) == 0x08);
}
