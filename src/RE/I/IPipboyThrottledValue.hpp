#pragma once

namespace RE
{
	class __declspec(novtable) IPipboyThrottledValue
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IPipboyThrottledValue;
		inline static constexpr const auto& VTABLE = VTABLE::IPipboyThrottledValue;

		// members
		virtual ~IPipboyThrottledValue(); // 0x00

		// add
		virtual void Update(); // 0x01
	};

	static_assert(sizeof(IPipboyThrottledValue) == 0x08);
}
