#include "RE/F/FORM_ENUM_STRING.hpp"

namespace RE
{
	auto FORM_ENUM_STRING::GetFormTypeStrings() -> std::span<FORM_ENUM_STRING, std::to_underlying(FormType::_Count)>
	{
		static const auto FORM_TYPE_STRINGS =
			REL::Relocation<std::array<FORM_ENUM_STRING, std::to_underlying(FormType::_Count)>*>{
				ID::FORM_ENUM_STRING::FormTypeStrings
		};
		return {*FORM_TYPE_STRINGS};
	}

	auto FORM_ENUM_STRING::GetFormTypeByString(std::string_view a_typeString) -> FormType
	{
		if (a_typeString.size() != sizeof(std::uint32_t)) {
			return FormType::None;
		}

		for (const auto& formInfo : GetFormTypeStrings()) {
			if (REX::EqualsIgnoreCase(a_typeString, std::string_view{formInfo.formString, sizeof(std::uint32_t)})) {
				return formInfo.formType.get();
			}
		}

		return FormType::None;
	}

	auto FORM_ENUM_STRING::GetFormStringByType(FormType a_formType) -> std::string_view
	{
		const auto formStrings = GetFormTypeStrings();
		if (std::to_underlying(a_formType) < 0 ||
			std::cmp_greater_equal(std::to_underlying(a_formType), formStrings.size())) {
			return {};
		}

		const auto& formString = formStrings[REX::ToUnsigned(std::to_underlying(a_formType))];
		return {formString.formString, sizeof(std::uint32_t)};
	}
}
