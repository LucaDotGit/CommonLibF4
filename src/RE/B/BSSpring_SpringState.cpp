#include "RE/B/BSSpring_SpringState.hpp"

namespace RE::BSSpring
{
	template class SpringState<REX::Float32>;
	static_assert(sizeof(SpringState<REX::Float32>) == 0x0C);

	template class SpringState<NiPoint2>;
	static_assert(sizeof(SpringState<NiPoint2>) == 0x14);

	template class SpringState<NiPoint3>;
	static_assert(sizeof(SpringState<NiPoint3>) == 0x1C);
}
