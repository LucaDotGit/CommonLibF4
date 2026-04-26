#pragma once

#include "RE/B/BGSDefaultObject.hpp"
#include "RE/I/IFormFactory.hpp"

namespace RE
{
	class __declspec(novtable) DefaultObjectFormFactory
		: public IFormFactory // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::__DefaultObjectFormFactory };
		inline static constexpr auto VTABLE{ VTABLE::__DefaultObjectFormFactory };

		~DefaultObjectFormFactory() override; // 00

		// override (IFormFactory)
		TESForm* DoCreate() override;							 // 01 - { return new BGSDefaultObject("", FormType::kNone, ""); }
		const char* GetFormName() const override;				 // 02 - { return "DefaultObject"; }
		FormType GetFormID() const override;					 // 03 - { return FormType::kDefaultObject; }
		const char* GetObjectName() const override;				 // 04 - { return "DefaultObject"; }
		OBJECT_TYPE GetObjectType() const override;				 // 05
		OBJECT_CATEGORY_TYPE GetObjectCategory() const override; // 06

		[[nodiscard]] static BGSDefaultObject* Create(const char* a_name, const char* a_description, FormType a_formType)
		{
			return new BGSDefaultObject(a_name, a_formType, a_description);
		}

		[[nodiscard]] static BGSDefaultObject* Create(const char* a_name, FormType a_formType)
		{
			return Create(a_name, "", a_formType);
		}
	};
	static_assert(sizeof(DefaultObjectFormFactory) == 0x08);
}
