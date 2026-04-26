#pragma once

namespace RE::BSScript
{
	enum class LinkValidState : std::uint32_t
	{
		kNotLinked = 0,
		kCurrentlyLinking = 1,
		kLinkedInvalid = 2,
		kLinkedValid = 3
	};
}
