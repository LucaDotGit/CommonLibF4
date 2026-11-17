#pragma once

namespace RE
{
	class WorkbenchData
	{
	public:
		enum class Type : std::int32_t
		{
			None = 0,
			CreateObject = 1,
			Weapons = 2,
			Enchanting = 3,
			EnchantingExperiment = 4,
			Alchemy = 5,
			AlchemyExperiment = 6,
			Armor = 7,
			PowerArmor = 8,
			RobotMod = 9
		};

		// members
		REX::Enum<Type, std::int8_t> type; // 0x00
	};

	static_assert(sizeof(WorkbenchData) == 0x01);
}
