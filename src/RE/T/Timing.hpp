#pragma once

namespace RE
{
	class Timing
	{
	public:
		class Interval
		{
		public:
			// members
			std::uint8_t begin; // 0x00
			std::uint8_t end;	// 0x01
		};

		static_assert(sizeof(Interval) == 0x02);

		// members
		Interval sunrise;		 // 0x00
		Interval sunset;		 // 0x02
		std::uint8_t volatility; // 0x04
	};

	static_assert(sizeof(Timing) == 0x05);
}
