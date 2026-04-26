#pragma once

namespace RE
{
	enum class REGION_DATA_ID : std::int32_t;

	class REGION_DATA_BASE
	{
	public:
		// members
		REX::Enum<REGION_DATA_ID, std::int32_t> dataTypeID; // 00
		bool override;										// 04
		std::uint8_t priority;								// 05
	};
	static_assert(sizeof(REGION_DATA_BASE) == 0x08);
}
