#pragma once

namespace RE
{
	enum class WARNING_TYPES : std::int32_t
	{
		Default = 0,
		System = 1,
		Combat = 2,
		Animation = 3,
		AI = 4,
		Scripts = 5,
		SaveLoad = 6,
		Dialogue = 7,
		Quests = 8,
		Packages = 9,
		Editor = 10,
		Models = 11,
		Textures = 12,
		Plugins = 13,
		MasterFile = 14,
		Forms = 15,
		Magic = 16,
		Shaders = 17,
		Rendering = 18,
		Pathfinding = 19,
		Menus = 20,
		Audio = 21,
		Cells = 22,
		Havok = 23,
		FaceGen = 24,
		Water = 25,
		InGameMessage = 26,
		Memory = 27,
		Performance = 28,
		LootJoy = 29,
		VATS = 30,
		Dismember = 31,
		Companion = 32,
		Workshop = 33,

		_Count = 34
	};
}
