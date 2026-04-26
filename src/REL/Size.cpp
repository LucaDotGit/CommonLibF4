#include "REL/Size.hpp"

namespace REL
{
	static_assert([]() consteval noexcept {
		constexpr auto TEST_RUNTIME_01 = REL::CreateRuntime(1, 0, 0, 0);
		constexpr auto TEST_RUNTIME_02 = REL::CreateRuntime(1, 0, 0, 1);

		constexpr auto TEST_SIZE_01 = CreateSize<TEST_RUNTIME_01, TEST_RUNTIME_02>(12345678, 23456789);
		constexpr auto TEST_SIZE_02 = CreateSize<TEST_RUNTIME_02>(34567890);

		return (TEST_SIZE_01.GetSize(TEST_RUNTIME_01) == 12345678) &&
			   (TEST_SIZE_01.GetSize(TEST_RUNTIME_02) == 23456789) &&
			   (TEST_SIZE_02.GetSize(TEST_RUNTIME_01) == 34567890) &&
			   (TEST_SIZE_02.GetSize(TEST_RUNTIME_02) == 34567890);
	}());
}
