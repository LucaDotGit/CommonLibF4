#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/T/TESPackage.hpp"

namespace RE
{
	class __declspec(novtable) DialoguePackage
		: public TESPackage // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::DialoguePackage };
		inline static constexpr auto VTABLE{ VTABLE::DialoguePackage };
		inline static constexpr auto FORM_TYPE{ FormType::kPackage };

		~DialoguePackage() override; // 00

		// members
		ActorHandle talkingActor;			   // C8
		ObjectRefHandle genericSecondLocation; // CC
		ActorHandle actor;					   // D0
		ActorHandle targetActor;			   // D4
		bool actorHeadTrack;				   // D8
		bool createdPack;					   // D9
		REX::Float32 eventWaitTimer;		   // DC
		REX::Float32 listenTimer;			   // E0
		bool sceneGenerated;				   // E4
	};
	static_assert(sizeof(DialoguePackage) == 0xE8);
}
