#pragma once

namespace RE
{
	class BSExtraData;
}

namespace RE::ComparisonQualifiers
{
	[[nodiscard]] bool ContainerQualifier(const BSExtraData* a_extraData);
	[[nodiscard]] bool UIQualifier(const BSExtraData* a_extraData);
};
