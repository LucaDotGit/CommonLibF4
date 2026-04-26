#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE::BSSpring
{
	template <class T>
	class SpringState
	{
	public:
		// members
		T position;					 // 00
		T velocity;					 // ??
		REX::Float32 springConstant; // ??
	};

	extern template class SpringState<REX::Float32>;
	extern template class SpringState<NiPoint2>;
	extern template class SpringState<NiPoint3>;
}
