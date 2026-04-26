#pragma once

namespace RE
{
	class OBJ_ARMA
	{
	public:
		// members
		union
		{
			std::array<std::int8_t, 2> priorities;
			struct
			{
				std::int8_t malePriority;
				std::int8_t femalePriority;
			};
		}; // 00
		union
		{
			std::array<std::int8_t, 2> modelRanges;
			struct
			{
				std::int8_t maleModelRange;
				std::int8_t femaleModelRange;
			};
		}; // 02
		union
		{
			std::array<std::int8_t, 2> unusedArray04;
			struct
			{
				std::int8_t unused04;
				std::int8_t unused05;
			};
		}; // 04
		std::int8_t detectionSoundValue; // 06
		REX::Float32 weaponAdjust;		 // 08
	};
	static_assert(sizeof(OBJ_ARMA) == 0x0C);
}
