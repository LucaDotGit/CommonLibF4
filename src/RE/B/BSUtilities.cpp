#include "RE/B/BSUtilities.hpp"

namespace RE::BSUtilities
{
	auto ConvertFloatToHalf(REX::Float32 a_value) -> std::uint16_t
	{
		using FuncType = decltype(&BSUtilities::ConvertFloatToHalf);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSUtilities::ConvertFloatToHalf);
		return std::invoke(FUNC, a_value);
	}

	auto ConvertHalfToFloat(std::uint16_t a_value) -> REX::Float32
	{
		using FuncType = decltype(&BSUtilities::ConvertHalfToFloat);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSUtilities::ConvertHalfToFloat);
		return std::invoke(FUNC, a_value);
	}

	auto GetObjectByName(NiAVObject* a_root, const BSFixedString& a_name, bool a_tryInternal, bool a_dontAttach)
		-> NiAVObject*
	{
		using FuncType = decltype(&BSUtilities::GetObjectByName);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSUtilities::GetObjectByName);
		return std::invoke(FUNC, a_root, a_name, a_tryInternal, a_dontAttach);
	}
}
