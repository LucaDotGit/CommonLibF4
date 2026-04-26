#pragma once

namespace RE::BGSTypedFormValuePair
{
	union SharedVal
	{
	public:
		~SharedVal() noexcept { return; }

		// members
		std::uint32_t int32{ 0 };
		REX::Float32 float32;
	};
	static_assert(sizeof(SharedVal) == 0x04);
}
