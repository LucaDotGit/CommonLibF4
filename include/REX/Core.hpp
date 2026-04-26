#pragma once

#if NDEBUG == 0
#define REX_CONSTEXPR_RELEASE const
#else
#define REX_CONSTEXPR_RELEASE constexpr
#endif

#if NDEBUG == 0
#define REX_CONSTEVAL_RELEASE
#else
#define REX_CONSTEVAL_RELEASE consteval
#endif

#if NDEBUG == 0
#define REX_CONSTINIT_RELEASE
#else
#define REX_CONSTINIT_RELEASE constinit
#endif

// IWYU pragma: begin_exports
#include "REX/Float.hpp"
// IWYU pragma: end_exports
