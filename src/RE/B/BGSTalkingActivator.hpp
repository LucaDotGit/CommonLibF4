#pragma once

#include "RE/T/TESObjectACTI.hpp"

namespace RE
{
	class __declspec(novtable) BGSTalkingActivator : public TESObjectACTI // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSTalkingActivator;
		inline static constexpr const auto& VTABLE = VTABLE::BGSTalkingActivator;
		inline static constexpr auto FORM_TYPE = FormType::TalkingActivator;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				Speaker = 1 << 23
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				HiddenFromLocalMap = 1 << 9,
				Ignored = 1 << 12,
				RandomAnimStart = 1 << 16,
				RadioStation = 1 << 17
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		~BGSTalkingActivator() override; // 0x00

		// add
		virtual auto GetReflectedByAutoWater() -> bool; // 0x67 - { return false; }

		// members
		TESObjectREFR* tempRef;	 // 0x148
		BGSVoiceType* voiceType; // 0x150
	};

	static_assert(sizeof(BGSTalkingActivator) == 0x158);
}
