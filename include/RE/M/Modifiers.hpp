#pragma once

namespace RE
{
	class Modifiers
	{
	public:
		// members
		std::array<REX::Float32, 3> modifiers; // 00
	};
	static_assert(sizeof(Modifiers) == 0x0C);
}
