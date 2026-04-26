#pragma once

#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESModel.hpp"
#include "RE/T/TESModelTri.hpp"

namespace RE
{
	class __declspec(novtable) BGSHeadPart
		: public TESForm,			  // 000
		  public TESFullName,		  // 020
		  public BGSModelMaterialSwap // 030
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSHeadPart };
		inline static constexpr auto VTABLE{ VTABLE::BGSHeadPart };
		inline static constexpr auto FORM_TYPE{ FormType::kHeadPart };

		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kPlayable = 1 << 0,
			kCantBeFemale = 1 << 1,
			kCantBeMale = 1 << 2,
			kExtraPart = 1 << 3,
			kUseSolidTint = 1 << 4,
			kUseBodyTexture = 1 << 5
		};

		enum class HeadPartType : std::uint32_t
		{
			kMisc = 0,
			kFace = 1,
			kEyes = 2,
			kHair = 3,
			kFacialHair = 4,
			kScar = 5,
			kEyebrows = 6,
			kMeatcaps = 7,
			kTeeth = 8,
			kHeadRear = 9
		};

		enum class MorphIndex : std::int32_t
		{
			kRaceMorph = 0,
			kDefaultMorph = 1,
			kChargenMorph = 2,

			kTotal = 3
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> flags;								// 070
		REX::Enum<HeadPartType, std::int32_t> type;								// 074
		BSTArray<BGSHeadPart*> extraParts;										// 078
		BGSTextureSet* textureSet;												// 090
		TESModel ChargenModel;													// 098
		std::array<TESModelTri, std::to_underlying(MorphIndex::kTotal)> morphs; // 0C8
		BGSColorForm* colorForm;												// 158
		BGSListForm* validRaces;												// 160
		TESCondition chargenConditions;											// 168
		BSFixedString formEditorID;												// 170
	};
	static_assert(sizeof(BGSHeadPart) == 0x178);
}
