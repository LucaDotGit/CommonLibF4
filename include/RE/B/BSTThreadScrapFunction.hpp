#pragma once

#include "msvc/functional.hpp"

namespace RE
{
	template <class F>
	using BSTThreadScrapFunction = msvc::function<F>;
}
