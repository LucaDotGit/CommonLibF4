#pragma once

#include "RE/T/TESForm.hpp"

namespace RE
{
	enum class DIALOGUE_TYPE : std::int32_t;

	class __declspec(novtable) BGSDialogueBranch : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSDialogueBranch;
		inline static constexpr const auto& VTABLE = VTABLE::BGSDialogueBranch;
		inline static constexpr auto FORM_TYPE = FormType::DialogueBranch;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			None = 0,
			TopLevel = 1 << 0,
			Blocking = 1 << 1,
			Exclusive = 1 << 2
		};

		// members
		REX::EnumSet<Flags, std::uint32_t> flags;	 // 0x20
		TESQuest* quest;							 // 0x28
		TESTopic* startingTopic;					 // 0x30
		REX::Enum<DIALOGUE_TYPE, std::int32_t> type; // 0x38
	};

	static_assert(sizeof(BGSDialogueBranch) == 0x40);
}
