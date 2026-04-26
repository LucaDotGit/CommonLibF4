#pragma once

namespace RE::nsUIDebug
{
	struct UIDebugLogger_NoOp
	{
	public:
	};
	static_assert(std::is_empty_v<UIDebugLogger_NoOp>);
}
