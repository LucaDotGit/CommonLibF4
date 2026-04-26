#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiControllerSequence.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTArray.hpp"
#include "RE/N/NiTimeController.hpp"

namespace RE
{
	class BSAnimNoteListener;
	class NiAVObjectPalette;

	class __declspec(novtable) NiControllerManager
		: public NiTimeController // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiControllerManager };
		inline static constexpr auto VTABLE{ VTABLE::NiControllerManager };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiControllerManager };

		[[nodiscard]] static NiControllerManager* GetNiControllerManager(const NiObjectNET* a_object)
		{
			using FuncType = decltype(&NiControllerManager::GetNiControllerManager);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::NiControllerManager::GetNiControllerManager };
			return std::invoke(FUNC, a_object);
		}

		[[nodiscard]] NiControllerSequence* GetSequenceByName(const BSFixedString& a_name)
		{
			using FuncType = decltype(&NiControllerManager::GetSequenceByName);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::NiControllerManager::GetSequenceByName };
			return std::invoke(FUNC, this, a_name);
		}

		// members
		NiTObjectArray<NiPointer<NiControllerSequence>> sequenceArray; // 48
		std::array<std::byte, 0x70 - 0x60> activeSequences;			   // 60 - TODO: `NiTPrimitiveSet<NiControllerSequence*>`
		BSTHashMap<BSFixedString, NiControllerSequence*> stringMap;	   // 70
		BSAnimNoteListener* listener;								   // A0
		bool cumulative;											   // A8
		std::array<std::byte, 0xC0 - 0xB0> tempBlendSeqs;			   // B0 - TODO: `NiTObjectSet<NiPointer<NiControllerSequence>>`
		NiPointer<NiAVObjectPalette> objectPalette;					   // C0
	};
	static_assert(sizeof(NiControllerManager) == 0xC8);
}
