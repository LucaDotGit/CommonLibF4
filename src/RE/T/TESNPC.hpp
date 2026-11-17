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
#include "RE/N/NiPoint3.hpp"
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

	class __declspec(novtable) TESNPC :
		public TESActorBase,					// 0x000
		public TESRaceForm,						// 0x1B0
		public BGSOverridePackCollection,		// 0x1C0
		public BGSForcedLocRefType,				// 0x1F8
		public BGSNativeTerminalForm,			// 0x208
		public BSTEventSink<MenuOpenCloseEvent> // 0x218
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESNPC;
		inline static constexpr const auto& VTABLE = VTABLE::TESNPC;
		inline static constexpr auto FORM_TYPE = FormType::ActorBase;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				Data = 1 << 1,
				Attributes = 1 << 2,
				AIData = 1 << 3,
				SpellList = 1 << 4,
				FullName = 1 << 5,
				Factions = 1 << 6,
				Skills = 1 << 9,
				Class = 1 << 10,
				Face = 1 << 11,
				DefaultOutfit = 1 << 12,
				SleepOutfit = 1 << 13,
				BodyScales = 1 << 14,
				Gender = 1 << 24,
				Race = 1 << 25
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				Compressed = 1 << 18,
				BleedoutOverride = 1 << 29
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class HeadRelatedData
		{
		public:
			GAME_HEAP_REDEFINE_NEW(HeadRelatedData);

			// members
			BGSColorForm* hairColor;	   // 0x00
			BGSColorForm* facialHairColor; // 0x08
			BGSTextureSet* faceDetails;	   // 0x10
		};

		static_assert(sizeof(HeadRelatedData) == 0x18);

		~TESNPC() override; // 0x00

		[[nodiscard]]
		static auto GetAlternateHeadPartListMap() noexcept -> BSTHashMap<const TESNPC*, BSTArray<BGSHeadPart*>>&;

		[[nodiscard]]
		auto HasApplicableKeywordString(std::string_view a_editorID) const -> bool;
		[[nodiscard]]
		auto GetFacialHairColor() const noexcept -> BGSColorForm*;
		[[nodiscard]]
		auto GetFacialBoneMorphIntensity() const -> REX::Float32;
		[[nodiscard]]
		auto GetFaceDetails() const noexcept -> BGSTextureSet*;
		[[nodiscard]]
		auto GetHairColor() const noexcept -> BGSColorForm*;
		[[nodiscard]]
		auto GetHeadParts(bool a_alternate = true) -> std::span<BGSHeadPart*>;
		[[nodiscard]]
		auto GetHeadParts(bool a_alternate = true) const -> std::span<BGSHeadPart* const>;
		[[nodiscard]]
		auto GetRootFaceNPC() const noexcept -> const TESNPC*;
		[[nodiscard]]
		auto GetRootFaceNPC() noexcept -> TESNPC*;
		[[nodiscard]]
		auto GetSex() const noexcept -> SEX;
		[[nodiscard]]
		auto GetShortName() const -> const char*;
		[[nodiscard]]
		auto IsInFaction(const TESFaction* a_faction) const -> bool;
		void SetFaceDetails(BGSTextureSet* a_faceDetails);
		void SetFacialHairColor(BGSColorForm* a_facialHairColor);
		void SetHairColor(BGSColorForm* a_hairColor);
		void SetHeadParts(std::span<BGSHeadPart*> a_headParts, bool a_alternate = true);
		void SetTintingData(std::uint16_t a_uniqueID, REX::Float32 a_value, std::uint32_t a_color);
		[[nodiscard]]
		auto UsesAlternateHeadPartList() const -> bool;

		// members
		BGSAttachParentArray attachParents; // 0x220
		NPC_DATA data;						// 0x238
		TESClass* cl;						// 0x240
		HeadRelatedData* headRelatedData;	// 0x248
		BGSListForm* giftFilter;			// 0x250
		TESCombatStyle* combatStyle;		// 0x258
		std::uint32_t fileOffset;			// 0x260
		TESRace* originalRace;				// 0x268
		TESNPC* faceNPC;					// 0x270
		NiPoint3 morphWeight;				// 0x278
		REX::Float32 minHeight;				// 0x284
		REX::Float32 maxHeight;				// 0x288

		union
		{
		public:
			TESNPC* soundCreature;
			CreatureSounds* creatureSounds;
		}; // 0x290

		BGSLocalizedString shortName;														   // 0x298
		TESObjectARMO* farSkin;																   // 0x2A0
		TESFurniture* powerArmorFurniture;													   // 0x2A8
		BGSOutfit* defaultOutfit;															   // 0x2B0
		BGSOutfit* sleepOutfit;																   // 0x2B8
		BGSListForm* defaultPackList;														   // 0x2C0
		TESFaction* crimeFaction;															   // 0x2C8
		SimpleArray<BGSHeadPart*> headParts;												   // 0x2D0
		BSTArray<REX::Float32>* morphRegionSliderValues;									   // 0x2D8
		BSTHashMap<std::uint32_t, BGSCharacterMorph::Transform>* facialBoneRegionSliderValues; // 0x2E0
		std::uint8_t numHeadParts;															   // 0x2E8
		std::int8_t soundLevel;																   // 0x2E9
		std::uint8_t bodyTintColorR;														   // 0x2EA
		std::uint8_t bodyTintColorG;														   // 0x2EB
		std::uint8_t bodyTintColorB;														   // 0x2EC
		std::uint8_t bodyTintColorA;														   // 0x2ED
		BSTArray<BGSRelationship*>* relationships;											   // 0x2F0
		BSTHashMap<std::uint32_t, REX::Float32>* morphSliderValues;							   // 0x2F8
		BGSCharacterTint::Entries* tintingData;												   // 0x300
	};

	static_assert(sizeof(TESNPC) == 0x308);
}
