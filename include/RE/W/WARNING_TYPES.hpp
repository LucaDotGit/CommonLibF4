#pragma once

namespace RE
{
	enum class WARNING_TYPES : std::int32_t
	{
		kDefault = 0,
		kSystem = 1,
		kCombat = 2,
		kAnimation = 3,
		kAI = 4,
		kScripts = 5,
		kSaveLoad = 6,
		kDialogue = 7,
		kQuests = 8,
		kPackages = 9,
		kEditor = 10,
		kModels = 11,
		kTextures = 12,
		kPlugins = 13,
		kMasterFile = 14,
		kForms = 15,
		kMagic = 16,
		kShaders = 17,
		kRendering = 18,
		kPathfinding = 19,
		kMenus = 20,
		kAudio = 21,
		kCells = 22,
		kHavok = 23,
		kFaceGen = 24,
		kWater = 25,
		kInGameMessage = 26,
		kMemory = 27,
		kPerformance = 28,
		kLootJoy = 29,
		kVATS = 30,
		kDismember = 31,
		kCompanion = 32,
		kWorkshop = 33,

		kTotal = 34
	};
}
