#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class __declspec(novtable) BGSOpenCloseForm
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSOpenCloseForm;
		inline static constexpr const auto& VTABLE = VTABLE::BGSOpenCloseForm;

		enum class OPEN_STATE : std::int32_t
		{
			None = 0,
			Open = 1,
			Opening = 2,
			Closed = 3,
			Closing = 4
		};

		virtual ~BGSOpenCloseForm(); // 0x00

		// add
		virtual void HandleOpenStart(
			TESObjectREFR* a_target,
			TESObjectREFR* a_activator,
			bool a_snap); // 0x01 - { return; }
		virtual void HandleCloseStart(
			TESObjectREFR* a_target,
			TESObjectREFR* a_activator,
			bool a_snap);																	 // 0x02 - { return; }
		virtual void HandleOpenFinish(TESObjectREFR* a_target, TESObjectREFR* a_activator);	 // 0x03 - { return; }
		virtual void HandleCloseFinish(TESObjectREFR* a_target, TESObjectREFR* a_activator); // 0x04 - { return; }

		inline static void AutoCloseRef(const TESObjectREFR* a_ref)
		{
			using FuncType = decltype(&BGSOpenCloseForm::AutoCloseRef);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSOpenCloseForm::AutoCloseRef);
			std::invoke(FUNC, a_ref);
		}

		[[nodiscard]]
		static auto GetOpenState(const TESObjectREFR* a_ref) -> OPEN_STATE
		{
			using FuncType = decltype(&BGSOpenCloseForm::GetOpenState);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSOpenCloseForm::GetOpenState);
			return std::invoke(FUNC, a_ref);
		}

		[[nodiscard]]
		static auto HasOnlyOpenCloseAnims(const TESObjectREFR* a_ref) -> bool
		{
			using FuncType = decltype(&BGSOpenCloseForm::HasOnlyOpenCloseAnims);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSOpenCloseForm::HasOnlyOpenCloseAnims);
			return std::invoke(FUNC, a_ref);
		}

		[[nodiscard]]
		static auto IsAnimating(const TESObjectREFR* a_ref) -> bool
		{
			using FuncType = decltype(&BGSOpenCloseForm::IsAnimating);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSOpenCloseForm::IsAnimating);
			return std::invoke(FUNC, a_ref);
		}

		[[nodiscard]]
		static auto IsOpenCloseEvent(const BSFixedString& a_event, const bool& a_open) -> bool
		{
			using FuncType = decltype(&BGSOpenCloseForm::IsOpenCloseEvent);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSOpenCloseForm::IsOpenCloseEvent);
			return std::invoke(FUNC, a_event, a_open);
		}

		[[nodiscard]]
		static auto IsOpenCloseForm(TESForm* a_form) -> bool
		{
			using FuncType = decltype(&BGSOpenCloseForm::IsOpenCloseForm);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSOpenCloseForm::IsOpenCloseForm);
			return std::invoke(FUNC, a_form);
		}

		static auto SetOpenState(const TESObjectREFR* a_ref, bool a_open, bool a_snap) -> bool
		{
			using FuncType = decltype(&BGSOpenCloseForm::SetOpenState);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSOpenCloseForm::SetOpenState);
			return std::invoke(FUNC, a_ref, a_open, a_snap);
		}
	};

	static_assert(sizeof(BGSOpenCloseForm) == 0x08);
}
