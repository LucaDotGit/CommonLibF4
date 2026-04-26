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
			std::uint8_t begin; // 00
			std::uint8_t end;	// 01
		};
		static_assert(sizeof(Interval) == 0x02);

		// members
		Interval sunrise;		 // 00
		Interval sunset;		 // 02
		std::uint8_t volatility; // 04
	};
	static_assert(sizeof(Timing) == 0x05);
}
