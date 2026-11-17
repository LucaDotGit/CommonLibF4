#pragma once

namespace RE
{
	class TOPIC_INFO_DATA
	{
	public:
		enum class TOPIC_INFO_FLAGS : std::uint16_t
		{
			None = 0,
			StartSceneOnEnd = 1 << 0,
			Random = 1 << 1,
			SayOnce = 1 << 2,
			RequirePlayerActivation = 1 << 3,
			InfoRefusal = 1 << 4,
			RandomEnd = 1 << 5,
			EndRunningScene = 1 << 6,
			IsForceGreet = 1 << 7,
			PlayerAddress = 1 << 8,
			GroupTracksData = 1 << 8,
			ForceSubtitle = 1 << 9,
			GroupForceRandom = 1 << 9,
			CanMoveWhileGreeting = 1 << 10,
			NoLIPFile = 1 << 11,
			GroupDoNotDoAll = 1 << 11,
			PostProcess = 1 << 12,
			CustomSoundOutput = 1 << 13,
			DialogueInfoSaid = 1 << 14,
			HasCapsData = 1 << 14,
			AlreadySaidDoAllBeforeRepeating = 1 << 15,
			EditorOnly = 1 << 14
		};

		// members
		REX::EnumSet<TOPIC_INFO_FLAGS, std::uint16_t> flags; // 0x00
		std::uint16_t timeUntilReset;						 // 0x02
	};

	static_assert(sizeof(TOPIC_INFO_DATA) == 0x04);
}
