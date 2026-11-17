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

	class __declspec(novtable) NiControllerManager : public NiTimeController // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiControllerManager;
		inline static constexpr const auto& VTABLE = VTABLE::NiControllerManager;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiControllerManager;

		[[nodiscard]]
		static auto GetNiControllerManager(const NiObjectNET* a_object) -> NiControllerManager*
		{
			using FuncType = decltype(&NiControllerManager::GetNiControllerManager);
			static const auto FUNC = REL::Relocation<FuncType>(ID::NiControllerManager::GetNiControllerManager);
			return std::invoke(FUNC, a_object);
		}

		[[nodiscard]]
		auto GetSequenceByName(const BSFixedString& a_name) -> NiControllerSequence*
		{
			using FuncType = decltype(&NiControllerManager::GetSequenceByName);
			static const auto FUNC = REL::Relocation<FuncType>(ID::NiControllerManager::GetSequenceByName);
			return std::invoke(FUNC, this, a_name);
		}

		// members
		NiTObjectArray<NiPointer<NiControllerSequence>> sequenceArray; // 0x48
		std::array<std::byte, 0x70 - 0x60> activeSequences; // 0x60 - To-Do: `NiTPrimitiveSet<NiControllerSequence*>`
		BSTHashMap<BSFixedString, NiControllerSequence*> stringMap; // 0x70
		BSAnimNoteListener* listener;								// 0xA0
		bool cumulative;											// 0xA8
		std::array<std::byte, 0xC0 - 0xB0>
			tempBlendSeqs;							// 0xB0 - To-Do: `NiTObjectSet<NiPointer<NiControllerSequence>>`
		NiPointer<NiAVObjectPalette> objectPalette; // 0xC0
	};

	static_assert(sizeof(NiControllerManager) == 0xC8);
}
