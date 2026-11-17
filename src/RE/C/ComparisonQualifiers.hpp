#pragma once

namespace RE
{
	class BSExtraData;
}

namespace RE::ComparisonQualifiers
{
	[[nodiscard]]
	auto ContainerQualifier(const BSExtraData* a_extraData) -> bool;
	[[nodiscard]]
	auto UIQualifier(const BSExtraData* a_extraData) -> bool;
};
