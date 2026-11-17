#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class NiAVObject;
}

namespace RE::BSUtilities
{
	[[nodiscard]]
	auto ConvertFloatToHalf(REX::Float32 a_value) -> std::uint16_t;
	[[nodiscard]]
	auto ConvertHalfToFloat(std::uint16_t a_value) -> REX::Float32;
	[[nodiscard]]
	auto GetObjectByName(NiAVObject* a_root, const BSFixedString& a_name, bool a_tryInternal, bool a_dontAttach)
		-> NiAVObject*;
}
