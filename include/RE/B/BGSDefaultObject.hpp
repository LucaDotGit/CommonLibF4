#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSDefaultObject
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSDefaultObject };
		inline static constexpr auto VTABLE{ VTABLE::BGSDefaultObject };
		inline static constexpr auto FORM_TYPE{ FormType::kDefaultObject };

		BGSDefaultObject(const char* a_name, FormType a_formType, const char* a_description)
		{
			using FuncType = void (BGSDefaultObject::*)(const char*, FormType, const char*);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSDefaultObject::ctor };
			FUNC(this, a_name, a_formType, a_description);
		}

		[[nodiscard]] static auto* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<BSTArray<BGSDefaultObject*>**>{ ID::BGSDefaultObject::Singleton };
			return *SINGLETON;
		}

		template <class T = TESForm>
		[[nodiscard]] T* GetForm()
		{
			return form ? form->As<T>() : nullptr;
		}

		// members
		TESForm* form{ nullptr };				// 20
		REX::Enum<FormType, std::uint8_t> type; // 28
		BSFixedString formEditorID;				// 30
	};
	static_assert(sizeof(BGSDefaultObject) == 0x38);
}
