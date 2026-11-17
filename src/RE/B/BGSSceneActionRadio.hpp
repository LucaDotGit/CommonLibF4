#pragma once

#include "RE/B/BGSSceneAction.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionRadio : public BGSSceneAction // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSceneActionRadio;
		inline static constexpr auto VTABlE = VTABLE::BGSSceneActionRadio;

		~BGSSceneActionRadio() override; // 0x00

		// members
		TESTopic* topic;					// 0x20
		BGSSoundDescriptorForm* sound;		// 0x28
		BGSSoundOutput* outputModel;		// 0x30
		BGSKeyword* subtypeKeyword;			// 0x38
		BGSSoundDescriptorForm* topicSound; // 0x40
		REX::Float32 soundDuration;			// 0x48
		std::uint32_t soundID;				// 0x4C
		bool soundDone;						// 0x50
		TESTopic* currentTopic;				// 0x58
		REX::Float32 failTimer;				// 0x60
	};

	static_assert(sizeof(BGSSceneActionRadio) == 0x68);
}
