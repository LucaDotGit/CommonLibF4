#pragma once

namespace RE
{
	class WorkbenchData
	{
	public:
		enum class Type : std::int32_t
		{
			kNone = 0,
			kCreateObject = 1,
			kWeapons = 2,
			kEnchanting = 3,
			kEnchantingExperiment = 4,
			kAlchemy = 5,
			kAlchemyExperiment = 6,
			kArmor = 7,
			kPowerArmor = 8,
			kRobotMod = 9
		};

		// members
		REX::Enum<Type, std::int8_t> type; // 00
	};
	static_assert(sizeof(WorkbenchData) == 0x01);
}
