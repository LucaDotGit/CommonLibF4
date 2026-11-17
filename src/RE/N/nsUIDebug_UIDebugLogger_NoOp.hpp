#pragma once

namespace RE::nsUIDebug
{
	class UIDebugLogger_NoOp
	{
	public:
	};

	static_assert(std::is_empty_v<UIDebugLogger_NoOp>);
}
