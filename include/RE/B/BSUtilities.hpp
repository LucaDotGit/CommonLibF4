#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class NiAVObject;
}

namespace RE::BSUtilities
{
	[[nodiscard]] std::uint16_t ConvertFloatToHalf(REX::Float32 a_value);
	[[nodiscard]] REX::Float32 ConvertHalfToFloat(std::uint16_t a_value);
	[[nodiscard]] NiAVObject* GetObjectByName(NiAVObject* a_root, const BSFixedString& a_name, bool a_tryInternal, bool a_dontAttach);
}
