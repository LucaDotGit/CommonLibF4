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

	class __declspec(novtable) NiControllerSequence : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiControllerSequence;
		inline static constexpr const auto& VTABLE = VTABLE::NiControllerSequence;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiControllerSequence;

		enum class AnimState : std::int32_t
		{
			Inactive = 0,
			Animating = 1,
			EaseIn = 2,
			EaseOut = 3,
			TransSource = 4,
			TransDest = 5,
			MorphSource = 6
		};

		class IDTag
		{
		public:
			// members
			BSFixedString avObjectName;	  // 0x00
			BSFixedString propertyType;	  // 0x08
			BSFixedString ctrlType;		  // 0x10
			BSFixedString ctrlID;		  // 0x18
			BSFixedString interpolatorID; // 0x20
		};

		static_assert(sizeof(IDTag) == 0x28);

		class InterpArrayItem;

		auto Activate(
			std::uint8_t a_priority,
			bool a_startOver,
			REX::Float32 a_weight,
			REX::Float32 a_easeInTime,
			NiControllerSequence* a_timeSyncSeq,
			bool a_transition) -> bool
		{
			using FuncType = decltype(&NiControllerSequence::Activate);
			static const auto FUNC = REL::Relocation<FuncType>(ID::NiControllerSequence::Activate);
			return std::invoke(
				FUNC,
				this,
				a_priority,
				a_startOver,
				a_weight,
				a_easeInTime,
				a_timeSyncSeq,
				a_transition);
		}

		// members
		BSFixedString name;									// 0x10
		std::uint32_t arraySize;							// 0x18
		std::uint32_t arrayGrowBy;							// 0x1C
		InterpArrayItem* interpArray;						// 0x20
		IDTag* idTagArray;									// 0x28
		REX::Float32 seqWeight;								// 0x30
		NiPointer<NiTextKeyExtraData> textKeys;				// 0x38
		std::array<std::byte, 0x04> cycleType;				// 0x40
		REX::Float32 frequency;								// 0x44
		REX::Float32 beginKeyTime;							// 0x48
		REX::Float32 endKeyTime;							// 0x4C
		REX::Float32 lastTime;								// 0x50
		REX::Float32 weightedLastTime;						// 0x54
		REX::Float32 lastScaledTime;						// 0x58
		NiControllerManager* owner;							// 0x60
		REX::Enum<AnimState, std::int32_t> state;			// 0x68
		REX::Float32 offset;								// 0x6C
		REX::Float32 startTime;								// 0x70
		REX::Float32 endTime;								// 0x74
		REX::Float32 destFrame;								// 0x78
		NiControllerSequence* partnerSequence;				// 0x80
		BSFixedString accumRootName;						// 0x88
		NiAVObject* accumRoot;								// 0x90
		NiPointer<NiStringPalette> deprecatedStringPalette; // 0x98
		std::int16_t curAnimNIndex;							// 0xA0
		NiPointer<BSAnimNote>* animNotes;					// 0xA8
		std::uint16_t numNotes;								// 0xB0
		bool removableObjects;								// 0xB2
	};

	static_assert(sizeof(NiControllerSequence) == 0xB8);
}
