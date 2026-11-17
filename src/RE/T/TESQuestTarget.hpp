#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TeleportPath.hpp"

namespace RE
{
	class BSActorPathingMessageQueue;

	class TESQuestTarget
	{
	public:
		enum class Flags : std::uint8_t; // To-Do

		class REF_DATA
		{
		public:
			GAME_HEAP_REDEFINE_NEW(REF_DATA);

			// members
			TeleportPath teleportPath;									  // 0x00
			ObjectRefHandle refHandle;									  // 0x50
			BSTSmartPointer<BSActorPathingMessageQueue> pathMessageQueue; // 0x58
			bool forceRebuildQueue;										  // 0x60
		};

		static_assert(sizeof(REF_DATA) == 0x68);

		GAME_HEAP_REDEFINE_NEW(TESQuestTarget);

		// members
		REX::EnumSet<Flags, std::uint8_t> flags; // 0x00
		TESCondition conditions;				 // 0x08
		std::uint32_t targetAlias;				 // 0x20
		BGSKeyword* keyword;					 // 0x24
		BSTArray<REF_DATA*> targets;			 // 0x28
	};

	static_assert(sizeof(TESQuestTarget) == 0x38);
}
