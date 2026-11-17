#pragma once

#include "RE/B/BGSCharacterTint_Entries.hpp"
#include "RE/B/BGSHeadPart.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/L/LooksMenuEvent.hpp"

namespace RE::BGSCharacterMorph
{
	class Group;
	class Preset;
}

namespace RE::BGSCharacterTint::Template
{
	class Group;
	class Entry;
	class Palette;
}

namespace RE::BSFaceGenUtils
{
	class FaceGenData;
}

namespace RE
{
	class Actor;
	class BGSColorForm;
	class BGSTextureSet;
	class CharGenCharacterUpdateEvent;
	class TESNPC;

	class BGSChargenUtils : public BSTEventSource<CharGenCharacterUpdateEvent> // 0x00
	{
	public:
		enum class EditMode : std::int32_t
		{
			CharGen = 0,
			Remake = 1,
			Haircut = 2,
			BodyMod = 3
		};

		enum class UndoType : std::int32_t
		{
			Weight = 0,
			Sculpt = 1,
			HairColor = 2,
			HairStyle = 3,
			Beard = 4,
			Details = 5,
			Color = 6,
			Morphs = 7,

			None = 8
		};

		class AxisRemappingData
		{
		public:
			// members
			std::array<std::int32_t, 6> axisMap; // 0x00
		};

		static_assert(sizeof(AxisRemappingData) == 0x18);

		class UndoData
		{
		public:
			class Vec3
			{
			public:
				// members
				REX::Float32 x; // 0x00
				REX::Float32 y; // 0x04
				REX::Float32 z; // 0x08
			};

			static_assert(sizeof(Vec3) == 0x0C);

			class Transform
			{
			public:
				// members
				Vec3 position;		// 0x00
				Vec3 rotation;		// 0x0C
				REX::Float32 scale; // 0x18
			};

			static_assert(sizeof(Transform) == 0x1C);

			// members
			REX::Enum<UndoType, std::int32_t> type; // 0x00
			std::uint32_t targetID;					// 0x04
			REX::Float32 featureModifier;			// 0x08

			union
			{
			public:
				Vec3 weight;
				Transform transform;
				std::uint32_t featureIndex;
			}; // 0x0C

			BGSCharacterTint::Entries tintEntries;					   // 0x28
			BSTHashMap<std::uint32_t, REX::Float32> morphSliderValues; // 0x40
		};

		static_assert(sizeof(UndoData) == 0x70);

		// members
		Actor* targetActor;																				 // 0x058
		TESNPC* targetNPC;																				 // 0x060
		TESNPC* cacheNPC;																				 // 0x068
		BSTArray<TESNPC*>* characterPresets;															 // 0x070
		BSTArray<BGSColorForm*> hairColors;																 // 0x078
		BSTArray<BGSTextureSet*>* complexions;															 // 0x090
		std::array<BSTArray<BGSHeadPart*>, 10> headParts;												 // 0x098
		BSTHashMap<std::uint32_t, BGSChargenUtils::AxisRemappingData> facialBoneRegionAxisRemapping;	 // 0x188
		BSTHashMap<std::uint32_t, std::uint32_t> textureValueToFacialBoneRegionMap;						 // 0x1B8
		BSTHashMap<std::uint32_t, std::int32_t> sliderAxisMapping;										 // 0x1E8
		BSTHashMap<std::uint32_t, const BGSCharacterMorph::Group*> regionIDToMorphGroupMap;				 // 0x218
		BSTHashMap<std::uint32_t, const BGSCharacterTint::Template::Group*> regionIDToTintGroupMap;		 // 0x248
		BSTHashMap<BGSHeadPart::HeadPartType, std::uint32_t> headPartTypeToRegionIDMap;					 // 0x278
		BSTHashMap<std::uint32_t, LooksMenuEvent::EventType> regionIDToEventTypeMap;					 // 0x2A8
		BSTArray<const BGSCharacterMorph::Group*> morphGroups;											 // 0x2D8
		BSTHashMap<const BGSCharacterMorph::Group*, BSTArray<BGSCharacterMorph::Preset>*> morphPresets;	 // 0x2F0
		BSTArray<const BGSCharacterTint::Template::Group*> facePartCustomizationGroups;					 // 0x320
		BSTArray<BSTArray<const BGSCharacterTint::Template::Entry*>*> facePartCustomizationGroupEntries; // 0x338
		BGSCharacterTint::Template::Palette* skinToneCustomizationPalette;								 // 0x350
		BSTArray<const BGSCharacterTint::Template::Group*> faceExtraGroups;								 // 0x358
		BSTArray<BSTArray<const BGSCharacterTint::Template::Entry*>*> faceExtraEntries;					 // 0x370
		std::uint32_t tempFaceExtra;																	 // 0x388
		UndoData undoData;																				 // 0x390
		UndoData saveData;																				 // 0x400
		UndoData detailUndoData;																		 // 0x470
		BSTHashMap<BSFixedString, REX::Float32> morphSliderDeltas;										 // 0x4E0
		std::uint32_t lastCharacterPreset;																 // 0x510
		bool needsCustomizationUpdate;																	 // 0x514
		bool needsFaceUpdate;																			 // 0x515
		bool needsBodyUpdate;																			 // 0x516
		bool needsMorphUpdate;																			 // 0x517
		bool needsFullUpdate;																			 // 0x518
		bool playableOnly;																				 // 0x519
		std::array<void*, 4>
			characterCustomizationTextureArraysHandles; // 0x520 - To-Do: `std::array<BSResource::RHandleType, 4>`
		BSTSmartPointer<BSFaceGenUtils::FaceGenData> customizationData; // 0x540
	};

	static_assert(sizeof(BGSChargenUtils) == 0x548);
}
