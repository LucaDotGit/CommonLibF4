#include "REX/Stopwatch.hpp"

namespace REX
{
	template class BasicStopwatch<std::chrono::steady_clock>;

	static_assert(Stopwatch::IS_STEADY);
	static_assert(Stopwatch::IS_HIGH_RESOLUTION);
}
