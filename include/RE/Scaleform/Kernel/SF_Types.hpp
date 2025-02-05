#pragma once

namespace RE::Scaleform
{
	template <class E, class U = std::underlying_type_t<E>>
	using SFEnum = REX::Enum<E, U>;

	template <class E, class U = std::underlying_type_t<E>>
	using SFFlags = REX::EnumSet<E, U>;
}
