#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/FormComponents.hpp"
#include "RE/Bethesda/TESCondition.hpp"
#include "RE/Bethesda/TESForms.hpp"

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
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kHDPT };

		enum class Flags
		{
			kNone = 0,
			kPlayable = 1u << 0,
			kCantBeFemale = 1u << 1,
			kCantBeMale = 1u << 2,
			kExtraPart = 1u << 3,
			kUseSolidTint = 1u << 4,
			kUseBodyTexture = 1u << 5
		};

		enum class HeadPartType
		{
			kMisc,
			kFace,
			kEyes,
			kHair,
			kFacialHair,
			kScar,
			kEyebrows,
			kMeatcaps,
			kTeeth,
			kHeadRear
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> flags;	 // 070
		REX::Enum<HeadPartType, std::uint32_t> type; // 074
		BSTArray<BGSHeadPart*> extraParts;			 // 078
		BGSTextureSet* textureSet;					 // 090
		TESModel ChargenModel;						 // 098
		TESModelTri morphs[3];						 // 0C8
		BGSColorForm* colorForm;					 // 158
		BGSListForm* validRaces;					 // 160
		TESCondition chargenConditions;				 // 168
		BSFixedString formEditorID;					 // 170
	};
	static_assert(sizeof(BGSHeadPart) == 0x178);
}
