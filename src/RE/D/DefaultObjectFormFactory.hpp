#pragma once

#include "RE/B/BGSDefaultObject.hpp"
#include "RE/I/IFormFactory.hpp"

namespace RE
{
	class __declspec(novtable) DefaultObjectFormFactory : public IFormFactory // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::__DefaultObjectFormFactory;
		inline static constexpr const auto& VTABLE = VTABLE::__DefaultObjectFormFactory;

		~DefaultObjectFormFactory() override; // 0x00

		// override (IFormFactory)
		auto DoCreate() -> TESForm* override; // 0x01 - { return new BGSDefaultObject("", FormType::None, ""); }
		auto GetFormName() const -> const char* override;				 // 0x02 - { return "DefaultObject"; }
		auto GetFormID() const -> FormType override;					 // 0x03 - { return FormType::DefaultObject; }
		auto GetObjectName() const -> const char* override;				 // 0x04 - { return "DefaultObject"; }
		auto GetObjectType() const -> OBJECT_TYPE override;				 // 0x05
		auto GetObjectCategory() const -> OBJECT_CATEGORY_TYPE override; // 0x06

		[[nodiscard]]
		static auto Create(const char* a_name, const char* a_description, FormType a_formType)
			-> std::unique_ptr<BGSDefaultObject>
		{
			return std::make_unique<BGSDefaultObject>(a_name, a_formType, a_description);
		}

		[[nodiscard]]
		static auto Create(const char* a_name, FormType a_formType) -> std::unique_ptr<BGSDefaultObject>
		{
			return Create(a_name, "", a_formType);
		}
	};

	static_assert(sizeof(DefaultObjectFormFactory) == 0x08);
}
