#pragma once

namespace RE
{
	class TOPIC_INFO_DATA
	{
	public:
		enum class TOPIC_INFO_FLAGS : std::uint16_t
		{
			kNone = 0,
			kStartSceneOnEnd = 1 << 0,
			kRandom = 1 << 1,
			kSayOnce = 1 << 2,
			kRequirePlayerActivation = 1 << 3,
			kInfoRefusal = 1 << 4,
			kRandomEnd = 1 << 5,
			kEndRunningScene = 1 << 6,
			kIsForceGreet = 1 << 7,
			kPlayerAddress = 1 << 8,
			kGroupTracksData = 1 << 8,
			kForceSubtitle = 1 << 9,
			kGroupForceRandom = 1 << 9,
			kCanMoveWhileGreeting = 1 << 10,
			kNoLIPFile = 1 << 11,
			kGroupDoNotDoAll = 1 << 11,
			kPostProcess = 1 << 12,
			kCustomSoundOutput = 1 << 13,
			kDialogueInfoSaid = 1 << 14,
			kHasCapsData = 1 << 14,
			kAlreadySaidDoAllBeforeRepeating = 1 << 15,
			kEditorOnly = 1 << 14
		};

		// members
		REX::EnumSet<TOPIC_INFO_FLAGS, std::uint16_t> flags; // 00
		std::uint16_t timeUntilReset;						 // 02
	};
	static_assert(sizeof(TOPIC_INFO_DATA) == 0x04);
}
