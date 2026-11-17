#pragma once

namespace RE
{
	enum class SCRIPT_OUTPUT : std::int32_t;

	class ConditionCheckParams;
	class TESConditionItem;

	class TESCondition
	{
	public:
		~TESCondition()
		{
			ClearAllConditionItems();
		}

		[[nodiscard]]
		explicit operator bool() const noexcept
		{
			return head != nullptr;
		}

		[[nodiscard]]
		auto operator()(TESObjectREFR* a_actionRef, TESObjectREFR* a_targetRef) const -> bool
		{
			return IsTrue(a_actionRef, a_targetRef);
		}

		[[nodiscard]]
		auto IsTrue(TESObjectREFR* a_actionRef, TESObjectREFR* a_targetRef) const -> bool
		{
			using FuncType = decltype(&TESCondition::IsTrue);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESCondition::IsTrue);
			return std::invoke(FUNC, this, a_actionRef, a_targetRef);
		}

		[[nodiscard]]
		auto IsTrueForAllButFunction(ConditionCheckParams& a_paramData, SCRIPT_OUTPUT a_function) const -> bool
		{
			using FuncType = decltype(&TESCondition::IsTrueForAllButFunction);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESCondition::IsTrueForAllButFunction);
			return std::invoke(FUNC, this, a_paramData, a_function);
		}

		void ClearAllConditionItems() const
		{
			using FuncType = decltype(&TESCondition::ClearAllConditionItems);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESCondition::ClearAllConditionItems);
			std::invoke(FUNC, this);
		}

		// members
		TESConditionItem* head; // 0x00
	};

	static_assert(sizeof(TESCondition) == 0x08);
}
