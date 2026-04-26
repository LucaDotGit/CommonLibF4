#include "RE/B/BGSRefCollectionAlias.hpp"

namespace RE
{
	template bool BGSBaseAlias::Is<BGSRefCollectionAlias>() const noexcept;
	template bool BGSBaseAlias::IsNot<BGSRefCollectionAlias>() const noexcept;

	template BGSRefCollectionAlias* BGSBaseAlias::As<BGSRefCollectionAlias>() noexcept;
	template const BGSRefCollectionAlias* BGSBaseAlias::As<BGSRefCollectionAlias>() const noexcept;
}
