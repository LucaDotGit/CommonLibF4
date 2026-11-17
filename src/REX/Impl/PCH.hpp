#pragma once

// IWYU pragma: begin_exports

// C
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>

// C++
#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <barrier>
#include <bit>
#include <bitset>
#include <charconv>
#include <chrono>
#include <codecvt>
#include <compare>
#include <complex>
#include <concepts>
#include <condition_variable>
#include <coroutine>
#include <deque>
#include <exception>
#include <execution>
#include <expected>
#include <filesystem>
#include <flat_map>
#include <flat_set>
#include <format>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <generator>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <latch>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <mdspan>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <new>
#include <numbers>
#include <numeric>
#include <optional>
#include <ostream>
#include <print>
#include <queue>
#include <random>
#include <ranges>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <semaphore>
#include <set>
#include <shared_mutex>
#include <source_location>
#include <span>
#include <spanstream>
#include <sstream>
#include <stack>
#include <stacktrace>
#include <stdexcept>
#include <stdfloat>
#include <stop_token>
#include <streambuf>
#include <string>
#include <string_view>
#include <syncstream>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <variant>
#include <vector>
#include <version>

// IWYU pragma: end_exports

#if (COMMONLIB_FEATURE_FMT == 1)

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'702)
#endif

// IWYU pragma: begin_exports
#include <fmt/format.h>
#include <fmt/std.h>
#include <fmt/xchar.h>
// IWYU pragma: end_exports

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#endif

#if (COMMONLIB_FEATURE_INI == 1)

// IWYU pragma: begin_exports
#include <SimpleIni.h>
// IWYU pragma: end_exports

#endif

#if (COMMONLIB_FEATURE_TOML == 1 || \
	 COMMONLIB_FEATURE_JSON == 1 || \
	 COMMONLIB_FEATURE_YAML == 1 || \
	 COMMONLIB_RUNTIME_VR == 1)

// IWYU pragma: begin_exports
#include <glaze/glaze.hpp>
// IWYU pragma: end_exports

#endif

#if (COMMONLIB_FEATURE_TOML == 1)

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'702)
#endif

// IWYU pragma: begin_exports
#include <glaze/toml.hpp>
// IWYU pragma: end_exports

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#endif

#if (COMMONLIB_FEATURE_JSON == 1)

// IWYU pragma: begin_exports
#include <glaze/json.hpp>
// IWYU pragma: end_exports

#endif

#if (COMMONLIB_FEATURE_YAML == 1)

// IWYU pragma: begin_exports
#include <glaze/yaml.hpp>
// IWYU pragma: end_exports

#endif

#if (COMMONLIB_FEATURE_VR == 1)

// IWYU pragma: begin_exports
#include <glaze/csv.hpp>
// IWYU pragma: end_exports

#endif

#if (COMMONLIB_FEATURE_XBYAK == 1)

// IWYU pragma: begin_exports
#include <xbyak/xbyak.h>
// IWYU pragma: end_exports

#undef max
#undef MEM_COMMIT
#undef MEM_FREE
#undef MEM_RELEASE
#undef MEM_RESERVE
#undef PAGE_EXECUTE_READWRITE

#endif

// IWYU pragma: begin_exports
#include "REX/Floats.hpp"
// IWYU pragma: end_exports

namespace REL
{
	using namespace REX::Literals;
	using namespace std::literals;
}

namespace REX
{
	using namespace REX::Literals;
	using namespace std::literals;
}
