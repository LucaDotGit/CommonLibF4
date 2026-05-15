#pragma once

#include "RE/B/BGSAttachParentArray.hpp"
#include "RE/B/BGSCharacterMorph_Transform.hpp"
#include "RE/B/BGSForcedLocRefType.hpp"
#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BGSNativeTerminalForm.hpp"
#include "RE/B/BGSOverridePackCollection.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NPC_DATA.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/S/SEX.hpp"
#include "RE/S/SimpleArray.hpp"
#include "RE/T/TESActorBase.hpp"
#include "RE/T/TESRaceForm.hpp"

namespace RE::BGSCharacterTint
{
	class Entries;
}

namespace RE
{
	class BGSRelationship;
	class CreatureSounds;
	class MenuOpenCloseEvent;

	class __declspec(novtable) TESNPC
		: public TESActorBase,					  // 000
		  public TESRaceForm,					  // 1B0
		  public BGSOverridePackCollection,		  // 1C0
		  public BGSForcedLocRefType,			  // 1F8
		  public BGSNativeTerminalForm,			  // 208
		  public BSTEventSink<MenuOpenCloseEvent> // 218
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESNPC };
		inline static constexpr auto VTABLE{ VTABLE::TESNPC };
		inline static constexpr auto FORM_TYPE{ FormType::kActorBase };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kData = 1 << 1,
				kAttributes = 1 << 2,
				kAIData = 1 << 3,
				kSpellList = 1 << 4,
				kFullName = 1 << 5,
				kFactions = 1 << 6,
				kSkills = 1 << 9,
				kClass = 1 << 10,
				kFace = 1 << 11,
				kDefaultOutfit = 1 << 12,
				kSleepOutfit = 1 << 13,
				kBodyScales = 1 << 14,
				kGender = 1 << 24,
				kRace = 1 << 25
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kCompressed = 1 << 18,
				kBleedoutOverride = 1 << 29
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class HeadRelatedData
		{
		public:
			GAME_HEAP_REDEFINE_NEW(HeadRelatedData);

			// members
			BGSColorForm* hairColor;	   // 00
			BGSColorForm* facialHairColor; // 08
			BGSTextureSet* faceDetails;	   // 10
		};
		static_assert(sizeof(HeadRelatedData) == 0x18);

		[[nodiscard]] static auto GetAlternateHeadPartListMap()
			-> BSTHashMap<const TESNPC*, BSTArray<BGSHeadPart*>>&;

		[[nodiscard]] bool HasApplicableKeywordString(std::string_view a_editorID) const;
		[[nodiscard]] BGSColorForm* GetFacialHairColor() const noexcept;
		[[nodiscard]] REX::Float32 GetFacialBoneMorphIntensity() const;
		[[nodiscard]] BGSTextureSet* GetFaceDetails() const noexcept;
		[[nodiscard]] BGSColorForm* GetHairColor() const noexcept;
		[[nodiscard]] std::span<BGSHeadPart*> GetHeadParts(bool a_alternate = true);
		[[nodiscard]] std::span<BGSHeadPart* const> GetHeadParts(bool a_alternate = true) const;
		[[nodiscard]] const TESNPC* GetRootFaceNPC() const noexcept;
		[[nodiscard]] TESNPC* GetRootFaceNPC() noexcept;
		[[nodiscard]] SEX GetSex() const noexcept;
		[[nodiscard]] const char* GetShortName() const;
		[[nodiscard]] bool IsInFaction(const TESFaction* a_faction) const;
		void SetFaceDetails(BGSTextureSet* a_faceDetails);
		void SetFacialHairColor(BGSColorForm* a_facialHairColor);
		void SetHairColor(BGSColorForm* a_hairColor);
		void SetHeadParts(std::span<BGSHeadPart*> a_headParts, bool a_alternate = true);
		void SetTintingData(std::uint16_t a_uniqueID, REX::Float32 a_value, std::uint32_t a_color);
		[[nodiscard]] bool UsesAlternateHeadPartList() const;

		// members
		BGSAttachParentArray attachParents; // 220
		NPC_DATA data;						// 238
		TESClass* cl;						// 240
		HeadRelatedData* headRelatedData;	// 248
		BGSListForm* giftFilter;			// 250
		TESCombatStyle* combatStyle;		// 258
		std::uint32_t fileOffset;			// 260
		TESRace* originalRace;				// 268
		TESNPC* faceNPC;					// 270
		NiPoint3 morphWeight;				// 278
		REX::Float32 minHeight;				// 284
		REX::Float32 maxHeight;				// 288
		union
		{
			TESNPC* soundCreature;
			CreatureSounds* creatureSounds;
		}; // 290
		BGSLocalizedString shortName;														   // 298
		TESObjectARMO* farSkin;																   // 2A0
		TESFurniture* powerArmorFurniture;													   // 2A8
		BGSOutfit* defaultOutfit;															   // 2B0
		BGSOutfit* sleepOutfit;																   // 2B8
		BGSListForm* defaultPackList;														   // 2C0
		TESFaction* crimeFaction;															   // 2C8
		SimpleArray<BGSHeadPart*> headParts;												   // 2D0
		BSTArray<REX::Float32>* morphRegionSliderValues;									   // 2D8
		BSTHashMap<std::uint32_t, BGSCharacterMorph::Transform>* facialBoneRegionSliderValues; // 2E0
		std::uint8_t numHeadParts;															   // 2E8
		std::int8_t soundLevel;																   // 2E9
		std::uint8_t bodyTintColorR;														   // 2EA
		std::uint8_t bodyTintColorG;														   // 2EB
		std::uint8_t bodyTintColorB;														   // 2EC
		std::uint8_t bodyTintColorA;														   // 2ED
		BSTArray<BGSRelationship*>* relationships;											   // 2F0
		BSTHashMap<std::uint32_t, REX::Float32>* morphSliderValues;							   // 2F8
		BGSCharacterTint::Entries* tintingData;												   // 300
	};
	static_assert(sizeof(TESNPC) == 0x308);
}
