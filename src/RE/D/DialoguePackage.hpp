#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/T/TESPackage.hpp"

namespace RE
{
	class __declspec(novtable) DialoguePackage : public TESPackage // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::DialoguePackage;
		inline static constexpr const auto& VTABLE = VTABLE::DialoguePackage;
		inline static constexpr auto FORM_TYPE = FormType::Package;

		~DialoguePackage() override; // 0x00

		// members
		ActorHandle talkingActor;			   // 0xC8
		ObjectRefHandle genericSecondLocation; // 0xCC
		ActorHandle actor;					   // 0xD0
		ActorHandle targetActor;			   // 0xD4
		bool actorHeadTrack;				   // 0xD8
		bool createdPack;					   // 0xD9
		REX::Float32 eventWaitTimer;		   // 0xDC
		REX::Float32 listenTimer;			   // 0xE0
		bool sceneGenerated;				   // 0xE4
	};

	static_assert(sizeof(DialoguePackage) == 0xE8);
}
