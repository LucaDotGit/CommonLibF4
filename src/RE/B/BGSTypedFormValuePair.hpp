#pragma once

namespace RE::BGSTypedFormValuePair
{
	union SharedVal
	{
	public:
		// members
		std::uint32_t uint32{0};
		REX::Float32 float32;
	};

	static_assert(sizeof(SharedVal) == 0x04);
}
