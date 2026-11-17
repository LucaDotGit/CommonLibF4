#pragma once

namespace RE
{
	enum class DIALOGUE_SUBTYPE : std::int32_t;

	class BGSTopicSubtypeUnion
	{
	public:
		enum class TOPIC_MODE : std::int32_t
		{
			Specific = 0,
			General = 1
		};

		// members
		REX::Enum<TOPIC_MODE, std::int32_t> mode; // 0x00

		union
		{
		public:
			REX::Enum<DIALOGUE_SUBTYPE, std::int32_t> generalTopicSubtype;
			TESFormID specificTopicID;
		}; // 0x04
	};

	static_assert(sizeof(BGSTopicSubtypeUnion) == 0x08);
}
