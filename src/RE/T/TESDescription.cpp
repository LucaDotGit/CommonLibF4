#include "RE/T/TESDescription.hpp"

#include "RE/T/TESForm.hpp"

namespace RE
{
	auto TESDescription::GetFormDescription(const TESForm* a_form)
		-> std::optional<BSFixedStringCS>
	{
		if (!a_form) {
			return std::nullopt;
		}

		auto* lastPlugin = a_form->GetFile();
		if (!lastPlugin) {
			return std::nullopt;
		}

		const auto* description = DynamicCast<const TESDescription*>(a_form);
		if (!description) {
			return std::nullopt;
		}

		const auto stringBuffer = description->descriptionText.GetText(*lastPlugin);

		if (!stringBuffer) {
			return std::nullopt;
		}

		return BSFixedStringCS{ stringBuffer.data() };
	}
}
