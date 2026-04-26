#pragma once

namespace RE
{
	class FACTION_VENDOR_DATA_VALUES
	{
	public:
		// members
		std::uint16_t startHour;	  // 00
		std::uint16_t endHour;		  // 02
		std::uint32_t locationRadius; // 04
		bool buysStolen;			  // 08
		bool notBuySell;			  // 09
		bool buysNonStolen;			  // 0A
	};
	static_assert(sizeof(FACTION_VENDOR_DATA_VALUES) == 0x0C);
}
