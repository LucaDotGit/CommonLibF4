#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiObject.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSAnimNote;
	class NiAVObject;
	class NiControllerManager;
	class NiStringPalette;
	class NiTextKeyExtraData;

	class __declspec(novtable) NiControllerSequence
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiControllerSequence };
		inline static constexpr auto VTABLE{ VTABLE::NiControllerSequence };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiControllerSequence };

		enum class AnimState : std::int32_t
		{
			kInactive = 0,
			kAnimating = 1,
			kEaseIn = 2,
			kEaseOut = 3,
			kTransSource = 4,
			kTransDest = 5,
			kMorphSource = 6
		};

		class IDTag
		{
		public:
			// members
			BSFixedString avObjectName;	  // 00
			BSFixedString propertyType;	  // 08
			BSFixedString ctrlType;		  // 10
			BSFixedString ctrlID;		  // 18
			BSFixedString interpolatorID; // 20
		};
		static_assert(sizeof(IDTag) == 0x28);

		class InterpArrayItem;

		bool Activate(std::uint8_t a_priority, bool a_startOver, REX::Float32 a_weight, REX::Float32 a_easeInTime, NiControllerSequence* a_timeSyncSeq, bool a_transition)
		{
			using FuncType = decltype(&NiControllerSequence::Activate);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::NiControllerSequence::Activate };
			return std::invoke(FUNC, this, a_priority, a_startOver, a_weight, a_easeInTime, a_timeSyncSeq, a_transition);
		}

		// members
		BSFixedString name;									// 10
		std::uint32_t arraySize;							// 18
		std::uint32_t arrayGrowBy;							// 1C
		InterpArrayItem* interpArray;						// 20
		IDTag* idTagArray;									// 28
		REX::Float32 seqWeight;								// 30
		NiPointer<NiTextKeyExtraData> textKeys;				// 38
		std::array<std::byte, 0x04> cycleType;				// 40
		REX::Float32 frequency;								// 44
		REX::Float32 beginKeyTime;							// 48
		REX::Float32 endKeyTime;							// 4C
		REX::Float32 lastTime;								// 50
		REX::Float32 weightedLastTime;						// 54
		REX::Float32 lastScaledTime;						// 58
		NiControllerManager* owner;							// 60
		REX::Enum<AnimState, std::int32_t> state;			// 68
		REX::Float32 offset;								// 6C
		REX::Float32 startTime;								// 70
		REX::Float32 endTime;								// 74
		REX::Float32 destFrame;								// 78
		NiControllerSequence* partnerSequence;				// 80
		BSFixedString accumRootName;						// 88
		NiAVObject* accumRoot;								// 90
		NiPointer<NiStringPalette> deprecatedStringPalette; // 98
		std::int16_t curAnimNIndex;							// A0
		NiPointer<BSAnimNote>* animNotes;					// A8
		std::uint16_t numNotes;								// B0
		bool removableObjects;								// B2
	};
	static_assert(sizeof(NiControllerSequence) == 0xB8);
}
