#pragma once

#include "RE/T/TESForm.hpp"

namespace RE
{
	enum class DIALOGUE_TYPE : std::int32_t;

	class __declspec(novtable) BGSDialogueBranch
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSDialogueBranch };
		inline static constexpr auto VTABLE{ VTABLE::BGSDialogueBranch };
		inline static constexpr auto FORM_TYPE{ FormType::kDialogueBranch };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kTopLevel = 1 << 0,
			kBlocking = 1 << 1,
			kExclusive = 1 << 2
		};

		// members
		REX::EnumSet<Flags, std::uint32_t> flags;	 // 20
		TESQuest* quest;							 // 28
		TESTopic* startingTopic;					 // 30
		REX::Enum<DIALOGUE_TYPE, std::int32_t> type; // 38
	};
	static_assert(sizeof(BGSDialogueBranch) == 0x40);
}
