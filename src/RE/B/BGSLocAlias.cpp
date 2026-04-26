#include "RE/B/BGSLocAlias.hpp"

namespace RE
{
	template bool BGSBaseAlias::Is<BGSLocAlias>() const noexcept;
	template bool BGSBaseAlias::IsNot<BGSLocAlias>() const noexcept;

	template BGSLocAlias* BGSBaseAlias::As<BGSLocAlias>() noexcept;
	template const BGSLocAlias* BGSBaseAlias::As<BGSLocAlias>() const noexcept;
}
