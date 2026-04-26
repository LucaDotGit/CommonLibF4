#include "RE/B/BGSRefAlias.hpp"

namespace RE
{
	template bool BGSBaseAlias::Is<BGSRefAlias>() const noexcept;
	template bool BGSBaseAlias::IsNot<BGSRefAlias>() const noexcept;

	template BGSRefAlias* BGSBaseAlias::As<BGSRefAlias>() noexcept;
	template const BGSRefAlias* BGSBaseAlias::As<BGSRefAlias>() const noexcept;
}
