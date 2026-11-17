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
	class __declspec(novtable) BGSHeadPart :
		public TESForm,				// 0x000
		public TESFullName,			// 0x020
		public BGSModelMaterialSwap // 0x030
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSHeadPart;
		inline static constexpr const auto& VTABLE = VTABLE::BGSHeadPart;
		inline static constexpr auto FORM_TYPE = FormType::HeadPart;

		enum class Flags : std::uint8_t
		{
			None = 0,
			Playable = 1 << 0,
			CantBeFemale = 1 << 1,
			CantBeMale = 1 << 2,
			ExtraPart = 1 << 3,
			UseSolidTint = 1 << 4,
			UseBodyTexture = 1 << 5
		};

		enum class HeadPartType : std::int32_t
		{
			Misc = 0,
			Face = 1,
			Eyes = 2,
			Hair = 3,
			FacialHair = 4,
			Scar = 5,
			Eyebrows = 6,
			Meatcaps = 7,
			Teeth = 8,
			HeadRear = 9
		};

		enum class MorphIndex : std::int32_t
		{
			RaceMorph = 0,
			DefaultMorph = 1,
			ChargenMorph = 2,

			_Count = 3
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> flags;								// 0x070
		REX::Enum<HeadPartType, std::int32_t> type;								// 0x074
		BSTArray<BGSHeadPart*> extraParts;										// 0x078
		BGSTextureSet* textureSet;												// 0x090
		TESModel ChargenModel;													// 0x098
		std::array<TESModelTri, std::to_underlying(MorphIndex::_Count)> morphs; // 0x0C8
		BGSColorForm* colorForm;												// 0x158
		BGSListForm* validRaces;												// 0x160
		TESCondition chargenConditions;											// 0x168
		BSFixedString formEditorID;												// 0x170
	};

	static_assert(sizeof(BGSHeadPart) == 0x178);
}
