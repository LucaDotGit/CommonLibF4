#pragma once

#include "RE/B/BSISoundOutputModel.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSSoundOutput :
		public TESForm,			   // 0x00
		public BSISoundOutputModel // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSoundOutput;
		inline static constexpr const auto& VTABLE = VTABLE::BGSSoundOutput;
		inline static constexpr auto FORM_TYPE = FormType::SoundOutput;

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
			AttenuatesWithDistance = 1 << 0,
			AllowsRumble = 1 << 1,
			AppliesDoppler = 1 << 2,
			AppliesDistantDelay = 1 << 3,
			PlayerOutputModel = 1 << 4,
			TryPlayOnController = 1 << 5,
			CausesDucking = 1 << 6,
			AvoidsDucking = 1 << 7
		};

		enum class SPEAKER_OUTPUT_MODE : std::int32_t
		{
			UsesHRTF = 0,
			DefinedSpeakerOutput = 1
		};

		class DynamicAttenuationCharacteristics; // To-Do
		class SpeakerArrays;					 // To-Do

		~BGSSoundOutput() override; // 0x00

		// members
		DynamicAttenuationCharacteristics* attenuation;	   // 0x28
		SpeakerArrays* speakerOutputArrays;				   // 0x30
		BGSAudioEffectChain* effectChain;				   // 0x38
		REX::EnumSet<Flags, std::uint32_t> flags;		   // 0x40
		REX::Enum<SPEAKER_OUTPUT_MODE, std::int32_t> mode; // 0x44
		std::uint16_t staticAttenuation;				   // 0x48
	};

	static_assert(sizeof(BGSSoundOutput) == 0x50);
}
