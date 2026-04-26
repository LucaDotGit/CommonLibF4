#include "RE/G/GetCurrentPositionFunctor.hpp"

namespace RE
{
	template class GetCurrentPositionFunctor<REX::Float32>;
	static_assert(std::is_empty_v<GetCurrentPositionFunctor<REX::Float32>>);
}
