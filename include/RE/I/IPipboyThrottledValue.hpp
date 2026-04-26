#pragma once

namespace RE
{
	class __declspec(novtable) IPipboyThrottledValue
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IPipboyThrottledValue };
		inline static constexpr auto VTABLE{ VTABLE::IPipboyThrottledValue };

		// members
		virtual ~IPipboyThrottledValue(); // 00

		// add
		virtual void Update(); // 01
	};
	static_assert(sizeof(IPipboyThrottledValue) == 0x08);
}
