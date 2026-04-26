#pragma once

namespace RE
{
	template <class T>
	class AnimationStanceNodeLocationData
	{
	public:
		// members
		std::array<T, 3> nodeLocationArray; // 00
	};
	static_assert(sizeof(AnimationStanceNodeLocationData<std::uintptr_t>) == 0x18);
}
