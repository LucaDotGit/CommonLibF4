#include "RE/B/BGSBaseAlias.hpp"

#include "RE/B/BGSLocAlias.hpp"
#include "RE/B/BGSRefAlias.hpp"
#include "RE/B/BGSRefCollectionAlias.hpp"

namespace RE
{
	[[nodiscard]] FormType BGSBaseAlias::GetFormType() const
	{
		const auto& aliasType = QType();
		if (aliasType == BGSRefAlias::ALIAS_TYPE) {
			return FormType::kRefAlias;
		}

		if (aliasType == BGSLocAlias::ALIAS_TYPE) {
			return FormType::kLocationAlias;
		}

		if (aliasType == BGSRefCollectionAlias::ALIAS_TYPE) {
			return FormType::kRefCollectionAlias;
		}

		return FormType::kNone;
	}
}
