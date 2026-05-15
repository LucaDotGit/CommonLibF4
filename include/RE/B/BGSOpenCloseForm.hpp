#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class __declspec(novtable) BGSOpenCloseForm
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSOpenCloseForm };
		inline static constexpr auto VTABLE{ VTABLE::BGSOpenCloseForm };

		enum class OPEN_STATE : std::int32_t
		{
			kNone = 0,
			kOpen = 1,
			kOpening = 2,
			kClosed = 3,
			kClosing = 4
		};

		virtual ~BGSOpenCloseForm(); // 00

		// add
		virtual void HandleOpenStart(TESObjectREFR* a_target, TESObjectREFR* a_activator, bool a_snap);	 // 01 - { return; }
		virtual void HandleCloseStart(TESObjectREFR* a_target, TESObjectREFR* a_activator, bool a_snap); // 02 - { return; }
		virtual void HandleOpenFinish(TESObjectREFR* a_target, TESObjectREFR* a_activator);				 // 03 - { return; }
		virtual void HandleCloseFinish(TESObjectREFR* a_target, TESObjectREFR* a_activator);			 // 04 - { return; }

		inline static void AutoCloseRef(const TESObjectREFR* a_ref)
		{
			using FuncType = decltype(&BGSOpenCloseForm::AutoCloseRef);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOpenCloseForm::AutoCloseRef };
			std::invoke(FUNC, a_ref);
		}

		[[nodiscard]] inline static OPEN_STATE GetOpenState(const TESObjectREFR* a_ref)
		{
			using FuncType = decltype(&BGSOpenCloseForm::GetOpenState);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOpenCloseForm::GetOpenState };
			return std::invoke(FUNC, a_ref);
		}

		[[nodiscard]] inline static bool HasOnlyOpenCloseAnims(const TESObjectREFR* a_ref)
		{
			using FuncType = decltype(&BGSOpenCloseForm::HasOnlyOpenCloseAnims);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOpenCloseForm::HasOnlyOpenCloseAnims };
			return std::invoke(FUNC, a_ref);
		}

		[[nodiscard]] inline static bool IsAnimating(const TESObjectREFR* a_ref)
		{
			using FuncType = decltype(&BGSOpenCloseForm::IsAnimating);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOpenCloseForm::IsAnimating };
			return std::invoke(FUNC, a_ref);
		}

		[[nodiscard]] inline static bool IsOpenCloseEvent(const BSFixedString& a_event, const bool& a_open)
		{
			using FuncType = decltype(&BGSOpenCloseForm::IsOpenCloseEvent);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOpenCloseForm::IsOpenCloseEvent };
			return std::invoke(FUNC, a_event, a_open);
		}

		[[nodiscard]] inline static bool IsOpenCloseForm(TESForm* a_form)
		{
			using FuncType = decltype(&BGSOpenCloseForm::IsOpenCloseForm);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOpenCloseForm::IsOpenCloseForm };
			return std::invoke(FUNC, a_form);
		}

		inline static bool SetOpenState(const TESObjectREFR* a_ref, bool a_open, bool a_snap)
		{
			using FuncType = decltype(&BGSOpenCloseForm::SetOpenState);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOpenCloseForm::SetOpenState };
			return std::invoke(FUNC, a_ref, a_open, a_snap);
		}
	};
	static_assert(sizeof(BGSOpenCloseForm) == 0x08);
}
