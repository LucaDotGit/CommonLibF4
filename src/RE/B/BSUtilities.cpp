#include "RE/B/BSUtilities.hpp"

namespace RE::BSUtilities
{
	std::uint16_t ConvertFloatToHalf(REX::Float32 a_value)
	{
		using FuncType = decltype(&BSUtilities::ConvertFloatToHalf);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSUtilities::ConvertFloatToHalf };
		return std::invoke(FUNC, a_value);
	}

	REX::Float32 ConvertHalfToFloat(std::uint16_t a_value)
	{
		using FuncType = decltype(&BSUtilities::ConvertHalfToFloat);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSUtilities::ConvertHalfToFloat };
		return std::invoke(FUNC, a_value);
	}

	NiAVObject* GetObjectByName(NiAVObject* a_root, const BSFixedString& a_name, bool a_tryInternal, bool a_dontAttach)
	{
		using FuncType = decltype(&BSUtilities::GetObjectByName);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSUtilities::GetObjectByName };
		return std::invoke(FUNC, a_root, a_name, a_tryInternal, a_dontAttach);
	}
}
