#pragma once

#include "RE/T/TESObjectACTI.hpp"

namespace RE
{
	class __declspec(novtable) BGSTalkingActivator
		: public TESObjectACTI // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSTalkingActivator };
		inline static constexpr auto VTABLE{ VTABLE::BGSTalkingActivator };
		inline static constexpr auto FORM_TYPE{ FormType::kTalkingActivator };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kSpeaker = 1 << 23
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kHiddenFromLocalMap = 1 << 9,
				kIgnored = 1 << 12,
				kRandomAnimStart = 1 << 16,
				kRadioStation = 1 << 17
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// add
		virtual bool GetReflectedByAutoWater(); // 67 - { return false; }

		// members
		TESObjectREFR* tempRef;	 // 148
		BGSVoiceType* voiceType; // 150
	};
	static_assert(sizeof(BGSTalkingActivator) == 0x158);
}
