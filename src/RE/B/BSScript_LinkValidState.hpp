#pragma once

namespace RE::BSScript
{
	enum class LinkValidState : std::uint32_t
	{
		NotLinked = 0,
		CurrentlyLinking = 1,
		LinkedInvalid = 2,
		LinkedValid = 3
	};
}
