#include "RE/B/BSTInterpolator.hpp"

namespace RE
{
	template class BSTInterpolator<REX::Float32, EaseOutInterpolator, GetCurrentPositionFunctor>;
	static_assert(sizeof(BSTInterpolator<REX::Float32, EaseOutInterpolator, GetCurrentPositionFunctor>) == 0x18);
}
