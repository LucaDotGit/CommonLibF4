#pragma once

#include "RE/B/BSIAudioEffectChain.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class BSIAudioEffectParameters;

	class __declspec(novtable) BGSAudioEffectChain
		: public TESForm,			 // 00
		  public BSIAudioEffectChain // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAudioEffectChain };
		inline static constexpr auto VTABLE{ VTABLE::BGSAudioEffectChain };
		inline static constexpr auto FORM_TYPE{ FormType::kAudioEffectChain };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BSTArray<BSIAudioEffectParameters*> effects; // 28
	};
	static_assert(sizeof(BGSAudioEffectChain) == 0x40);
}
