#include "REL/Id.hpp"

namespace REL
{
	static_assert([]() consteval noexcept {
		constexpr auto TEST_RUNTIME_01 = REL::CreateRuntime(1, 0, 0, 0);
		constexpr auto TEST_RUNTIME_02 = REL::CreateRuntime(1, 0, 0, 1);

		constexpr auto TEST_ID_01 = CreateId<TEST_RUNTIME_01, TEST_RUNTIME_02>(12345678, 23456789);
		constexpr auto TEST_ID_02 = CreateId<TEST_RUNTIME_02>(34567890);

		return (TEST_ID_01.GetId(TEST_RUNTIME_01) == 12345678) &&
			   (TEST_ID_01.GetId(TEST_RUNTIME_02) == 23456789) &&
			   (TEST_ID_02.GetId(TEST_RUNTIME_01) == 34567890) &&
			   (TEST_ID_02.GetId(TEST_RUNTIME_02) == 34567890);
	}());
}
