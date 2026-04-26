#pragma once

#include "RE/B/BSISoundOutputModel.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSSoundOutput
		: public TESForm,			 // 00
		  public BSISoundOutputModel // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSoundOutput };
		inline static constexpr auto VTABLE{ VTABLE::BGSSoundOutput };
		inline static constexpr auto FORM_TYPE{ FormType::kSoundOutput };

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
			kAttenuatesWithDistance = 1 << 0,
			kAllowsRumble = 1 << 1,
			kAppliesDoppler = 1 << 2,
			kAppliesDistantDelay = 1 << 3,
			kPlayerOutputModel = 1 << 4,
			kTryPlayOnController = 1 << 5,
			kCausesDucking = 1 << 6,
			kAvoidsDucking = 1 << 7
		};

		enum class SPEAKER_OUTPUT_MODE : std::int32_t
		{
			kUsesHRTF = 0,
			kDefinedSpeakerOutput = 1
		};

		class DynamicAttenuationCharacteristics; // TODO
		class SpeakerArrays;					 // TODO

		// members
		DynamicAttenuationCharacteristics* attenuation;	   // 28
		SpeakerArrays* speakerOutputArrays;				   // 30
		BGSAudioEffectChain* effectChain;				   // 38
		REX::EnumSet<Flags, std::uint32_t> flags;		   // 40
		REX::Enum<SPEAKER_OUTPUT_MODE, std::int32_t> mode; // 44
		std::uint16_t staticAttenuation;				   // 48
	};
	static_assert(sizeof(BGSSoundOutput) == 0x50);
}
