#pragma once

#include "RE/B/BGSChargenUtils.hpp"
#include "RE/B/BGSHeadPart.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/L/LooksInputRepeatHandler.hpp"
#include "RE/N/NiPoint2.hpp"
#include "RE/N/NiPointer.hpp"
#include "msvc/memory.hpp"

namespace RE
{
	class BSGFxShaderFXTarget;
	class BSInputEnableLayer;
	class ChargenCharacterUpdateEvent;

	class __declspec(novtable) LooksMenu :
		public GameMenuBase, // 0x000
		public BSTEventSink<ChargenCharacterUpdateEvent>
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::LooksMenu;
		inline static constexpr const auto& VTABLE = VTABLE::LooksMenu;
		inline static constexpr auto MENU_NAME = "LooksMenu"sv;
		// To-Do: `inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::LooksMenu;`

		class QueuedPresetIntensityChangeData
		{
		public:
			// members
			std::uint32_t region;	// 0x00
			REX::Float32 intensity; // 0x04
		};

		static_assert(sizeof(QueuedPresetIntensityChangeData) == 0x08);

		class QueuedSaveData
		{
		public:
			// members
			REX::Enum<BGSChargenUtils::UndoType, std::int32_t> type; // 0x00
			std::uint32_t region;									 // 0x04
		};

		static_assert(sizeof(QueuedSaveData) == 0x08);

		~LooksMenu() override; // 0x00

		// members
		BSTSmartPointer<BSInputEnableLayer> inputLayer;		  // 0x0E8
		LooksInputRepeatHandler inputRepeatHandler;			  // 0x0F0
		msvc::unique_ptr<BSGFxShaderFXTarget> bracketExtents; // 0x138
		std::array<void*, 2>
			facePickMask; // 0x140 - To-Do: `std::array<BSResource::RHandleType<BSResource::Entry<NiPointer<NiTexture>,
						  // BSResource::EntryDBTraits<BSTextureDB::DBTraits,
						  // BSResource::EntryDB<BSTextureDB::DBTraits>>::CArgs>,
						  // BSResource::EntryDB<BSTextureDB::DBTraits>>, 2>`
		std::uint32_t currentRegionID;															  // 0x150
		std::uint32_t lastRegionID;																  // 0x154
		std::array<LooksMenu::QueuedPresetIntensityChangeData, 2> queuedPresetIntensityChange;	  // 0x158
		std::array<BSTHashMap<BGSHeadPart::HeadPartType, std::uint32_t>, 2> queuedHeadPartChange; // 0x168
		std::array<std::uint32_t, 2> queuedEyeColorChange;										  // 0x1C8
		std::array<std::uint32_t, 2> queuedHairColorChange;										  // 0x1D0
		std::array<std::uint32_t, 2> queuedSkinColorChange;										  // 0x1D8
		LooksMenu::QueuedSaveData queuedSave;													  // 0x1E0
		NiPointer<TESObjectREFR> lookTarget;													  // 0x1E8
		NiPointer<TESObjectREFR> mirrorTarget;													  // 0x1F0
		std::time_t lastFaceUpdateTime;															  // 0x1F8
		REX::Float32 lookAtOnGain;																  // 0x200
		std::array<bool, 2> dirtyArray;															  // 0x204
		bool changesCanceled;																	  // 0x206
		bool queueHeadtracking;																	  // 0x207
		bool motionBlurActive;																	  // 0x208
		bool leftMouseDrag;																		  // 0x209
		bool rightMouseDrag;																	  // 0x20A
		NiPoint2 oldMousePosition;																  // 0x20C
	};

	static_assert(sizeof(LooksMenu) == 0x218);
}
