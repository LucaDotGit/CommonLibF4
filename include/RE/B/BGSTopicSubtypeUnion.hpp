#pragma once

namespace RE
{
	enum class DIALOGUE_SUBTYPE : std::int32_t;

	class BGSTopicSubtypeUnion
	{
	public:
		enum class TOPIC_MODE : std::int32_t
		{
			kSpecific = 0,
			kGeneral = 1
		};

		// members
		REX::Enum<TOPIC_MODE, std::int32_t> mode; // 00
		union
		{
			REX::Enum<DIALOGUE_SUBTYPE, std::int32_t> generalTopicSubtype;
			TESFormID specificTopicID;
		}; // 04
	};
	static_assert(sizeof(BGSTopicSubtypeUnion) == 0x08);
}
