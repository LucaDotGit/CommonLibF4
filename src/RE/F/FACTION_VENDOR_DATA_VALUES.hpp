#pragma once

namespace RE
{
	class FACTION_VENDOR_DATA_VALUES
	{
	public:
		// members
		std::uint16_t startHour;	  // 0x00
		std::uint16_t endHour;		  // 0x02
		std::uint32_t locationRadius; // 0x04
		bool buysStolen;			  // 0x08
		bool notBuySell;			  // 0x09
		bool buysNonStolen;			  // 0x0A
	};

	static_assert(sizeof(FACTION_VENDOR_DATA_VALUES) == 0x0C);
}
