#include "RE/C/ComparisonQualifiers.hpp"

namespace RE::ComparisonQualifiers
{
	auto ContainerQualifier(const BSExtraData* a_extraData) -> bool
	{
		using FuncType = decltype(&ComparisonQualifiers::ContainerQualifier);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ComparisonQualifiers::ContainerQualifier);
		return std::invoke(FUNC, a_extraData);
	}

	auto UIQualifier(const BSExtraData* a_extraData) -> bool
	{
		using FuncType = decltype(&ComparisonQualifiers::UIQualifier);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ComparisonQualifiers::UIQualifier);
		return std::invoke(FUNC, a_extraData);
	}
}
