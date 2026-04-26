#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class BSAnimationGraphChannel;
	class BSAnimationGraphManager;
	class BShkbAnimationGraph;
	class NiAVObject;

	class __declspec(novtable) IAnimationGraphManagerHolder
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IAnimationGraphManagerHolder };
		inline static constexpr auto VTABLE{ VTABLE::IAnimationGraphManagerHolder };

		virtual ~IAnimationGraphManagerHolder() = default; // 00

		// add
		virtual bool NotifyAnimationGraphImpl(const BSFixedString& a_eventName);																									   // 01
		virtual void EventSuccessfullyProcessed();																																	   // 02 - { return; }
		virtual void ModifyInitialAnimationStateImpl(bool a_unk01);																													   // 03 - { return; }
		virtual bool GetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) const = 0;																   // 04
		virtual bool SetAnimationGraphManagerImpl(const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) = 0;																   // 05
		virtual bool PopulateGraphNodesToTarget(BSScrapArray<NiAVObject*>& a_nodesToAnimate) const;																					   // 06 - { return false; }
		virtual bool ConstructAnimationGraph(BSTSmartPointer<BShkbAnimationGraph>& a_animGraph) = 0;																				   // 07
		virtual bool InitializeAnimationGraphVariables(const BSTSmartPointer<BShkbAnimationGraph>& a_newGraph) const;																   // 08 - { return true; }
		virtual bool SetupAnimEventSinks(const BSTSmartPointer<BShkbAnimationGraph>& a_newGraph);																					   // 09 - { return true; }
		virtual void DoFailedToLoadGraph() const;																																	   // 0A - { return; }
		virtual bool CreateAnimationChannels(BSScrapArray<BSTSmartPointer<BSAnimationGraphChannel>>& a_channels);																	   // 0B - { return false; }
		virtual void PostCreateAnimationGraphManager(BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr);																		   // 0C - { return; }
		virtual void PostChangeAnimationManager(const BSTSmartPointer<BSAnimationGraphManager>& a_newAnimGraphMgr, const BSTSmartPointer<BSAnimationGraphManager>& a_oldAnimGraphMgr); // 0D - { return; }
		virtual bool ShouldUpdateAnimation();																																		   // 0E - { return true; }
		virtual std::uint32_t GetGraphVariableCacheSize() const;																													   // 0F - { return 0; }
		virtual bool GetGraphVariableImpl(std::uint32_t a_graphVarID, REX::Float32& a_out) const;																					   // 10 - { return false; }
		virtual bool GetGraphVariableImpl(std::uint32_t a_graphVarID, bool& a_out) const;																							   // 11 - { return false; }
		virtual bool GetGraphVariableImpl(std::uint32_t a_graphVarID, std::int32_t& a_out) const;																					   // 12 - { return false; }
		virtual bool GetGraphVariableImplFloat(const BSFixedString& a_variable, REX::Float32& a_out) const;																			   // 13
		virtual bool GetGraphVariableImplInt(const BSFixedString& a_variable, std::int32_t& a_out) const;																			   // 14
		virtual bool GetGraphVariableImplBool(const BSFixedString& a_variable, bool& a_out) const;																					   // 15
		virtual void PreUpdateAnimationGraphManager(const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) const;															   // 16 - { return; }
		virtual void PostUpdateAnimationGraphManager(const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) const;															   // 17 - { return; }
		virtual void PreLoadAnimationGraphManager(const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr);																	   // 18 - { return; }
		virtual void PostLoadAnimationGraphManager(const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr);																	   // 19 - { return; }

		bool SetGraphVariableBool(const BSFixedString& a_variable, bool a_var)
		{
			using FuncType = decltype(&IAnimationGraphManagerHolder::SetGraphVariableBool);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::IAnimationGraphManagerHolder::SetGraphVariableBool };
			return std::invoke(FUNC, this, a_variable, a_var);
		}

		bool SetGraphVariableFloat(const BSFixedString& a_variable, REX::Float32 a_var)
		{
			using FuncType = decltype(&IAnimationGraphManagerHolder::SetGraphVariableFloat);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::IAnimationGraphManagerHolder::SetGraphVariableFloat };
			return std::invoke(FUNC, this, a_variable, a_var);
		}

		bool SetGraphVariableInt(const BSFixedString& a_variable, std::int32_t a_var)
		{
			using FuncType = decltype(&IAnimationGraphManagerHolder::SetGraphVariableInt);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::IAnimationGraphManagerHolder::SetGraphVariableInt };
			return std::invoke(FUNC, this, a_variable, a_var);
		}

		bool RevertAnimationGraphManager(bool a_performModifyInitialAnimationStateC = true)
		{
			using FuncType = decltype(&IAnimationGraphManagerHolder::RevertAnimationGraphManager);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::IAnimationGraphManagerHolder::RevertAnimationGraphManager };
			return std::invoke(FUNC, this, a_performModifyInitialAnimationStateC);
		}
	};
	static_assert(sizeof(IAnimationGraphManagerHolder) == 0x08);
}
