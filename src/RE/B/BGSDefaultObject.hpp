#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSDefaultObject : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSDefaultObject;
		inline static constexpr const auto& VTABLE = VTABLE::BGSDefaultObject;
		inline static constexpr auto FORM_TYPE = FormType::DefaultObject;

		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
		BGSDefaultObject(const char* a_name, FormType a_formType, const char* a_description)
		{
			using FuncType = void (BGSDefaultObject::*)(const char*, FormType, const char*);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSDefaultObject::ctor);
			std::invoke(FUNC, this, a_name, a_formType, a_description);
		}

		[[nodiscard]]
		static auto GetDefaultObjects() noexcept -> BSTArray<BGSDefaultObject*>&
		{
			static const auto SINGLETON =
				REL::Relocation<BSTArray<BGSDefaultObject*>*>{ID::BGSDefaultObject::GetDefaultObjects};
			return *SINGLETON;
		}

		template <class T = TESForm>
		[[nodiscard]]
		auto GetForm() -> T*
		{
			return form ? form->As<T>() : nullptr;
		}

		// members
		TESForm* form;							// 0x20
		REX::Enum<FormType, std::uint8_t> type; // 0x28
		BSFixedString formEditorID;				// 0x30
	};

	static_assert(sizeof(BGSDefaultObject) == 0x38);
}
