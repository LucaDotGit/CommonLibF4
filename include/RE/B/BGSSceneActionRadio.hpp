#pragma once

#include "RE/B/BGSSceneAction.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionRadio
		: public BGSSceneAction // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSceneActionRadio };
		inline static constexpr auto VTABlE{ VTABLE::BGSSceneActionRadio };

		~BGSSceneActionRadio() override; // 00

		// members
		TESTopic* topic;					// 20
		BGSSoundDescriptorForm* sound;		// 28
		BGSSoundOutput* outputModel;		// 30
		BGSKeyword* subtypeKeyword;			// 38
		BGSSoundDescriptorForm* topicSound; // 40
		REX::Float32 soundDuration;			// 48
		std::uint32_t soundID;				// 4C
		bool soundDone;						// 50
		TESTopic* currentTopic;				// 58
		REX::Float32 failTimer;				// 60
	};
	static_assert(sizeof(BGSSceneActionRadio) == 0x68);
}
