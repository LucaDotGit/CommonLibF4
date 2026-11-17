#pragma once

namespace RE
{
	class PipboyRadioController
	{
	public:
		// members
		REX::Float32 chaseStation; // 0x00
	};

	static_assert(sizeof(PipboyRadioController) == 0x04);
}
