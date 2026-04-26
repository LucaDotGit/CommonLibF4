#pragma once

namespace RE::BGSMod::Property
{
	enum class TYPE : std::int32_t
	{
		kInt = 0,
		kFloat = 1,
		kBool = 2,
		kString = 3,
		kForm = 4,
		kEnum = 5,
		kPair = 6
	};
}
