#pragma once

#include "RE/B/BSGFxFunctionBase.hpp"
#include "RE/B/BSTArray.hpp"

#include "msvc/memory.hpp"

namespace RE
{
	class UsesBSGFXFunctionHandler
	{
	public:
		inline static constexpr auto RTTI{ RTTI::UsesBSGFXFunctionHandler };

		// members
		BSTArray<msvc::unique_ptr<BSGFxFunctionBase>> functions; // 00
	};
	static_assert(sizeof(UsesBSGFXFunctionHandler) == 0x18);
}
