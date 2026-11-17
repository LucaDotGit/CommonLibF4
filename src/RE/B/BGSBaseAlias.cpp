#include "RE/B/BGSBaseAlias.hpp"

#include "RE/B/BGSLocAlias.hpp"
#include "RE/B/BGSRefAlias.hpp"
#include "RE/B/BGSRefCollectionAlias.hpp"

namespace RE
{
	[[nodiscard]]
	auto BGSBaseAlias::GetFormType() const -> FormType
	{
		const auto& aliasType = QType();
		if (aliasType == BGSRefAlias::ALIAS_TYPE) {
			return FormType::RefAlias;
		}

		if (aliasType == BGSLocAlias::ALIAS_TYPE) {
			return FormType::LocationAlias;
		}

		if (aliasType == BGSRefCollectionAlias::ALIAS_TYPE) {
			return FormType::RefCollectionAlias;
		}

		return FormType::None;
	}
}
