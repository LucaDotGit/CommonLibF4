#pragma once

#include "RE/B/BSIAudioEffectChain.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class BSIAudioEffectParameters;

	class __declspec(novtable) BGSAudioEffectChain :
		public TESForm,			   // 0x00
		public BSIAudioEffectChain // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSAudioEffectChain;
		inline static constexpr const auto& VTABLE = VTABLE::BGSAudioEffectChain;
		inline static constexpr auto FORM_TYPE = FormType::AudioEffectChain;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		~BGSAudioEffectChain() override; // 0x00

		// members
		BSTArray<BSIAudioEffectParameters*> effects; // 0x28
	};

	static_assert(sizeof(BGSAudioEffectChain) == 0x40);
}
