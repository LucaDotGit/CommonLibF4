#include "RE/C/ComparisonQualifiers.hpp"

namespace RE::ComparisonQualifiers
{
	bool ContainerQualifier(const BSExtraData* a_extraData)
	{
		using FuncType = decltype(&ComparisonQualifiers::ContainerQualifier);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ComparisonQualifiers::ContainerQualifier };
		return std::invoke(FUNC, a_extraData);
	}

	bool UIQualifier(const BSExtraData* a_extraData)
	{
		using FuncType = decltype(&ComparisonQualifiers::UIQualifier);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ComparisonQualifiers::UIQualifier };
		return std::invoke(FUNC, a_extraData);
	}
}
