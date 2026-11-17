#pragma once

namespace RE::BSSpring
{
	template <class T>
	class SpringState
	{
	public:
		// members
		T position;					 // 0x00
		T velocity;					 // 0x??
		REX::Float32 springConstant; // 0x??
	};
}
