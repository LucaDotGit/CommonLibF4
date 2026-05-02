#pragma once

#include "RE/B/BSSoundHandle.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/I/ImageSpaceLUTData.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class BGSModelMaterialSwap;
	class NiAVObject;

	class __declspec(novtable) LoadingMenu
		: public GameMenuBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::LoadingMenu };
		inline static constexpr auto VTABLE{ VTABLE::LoadingMenu };
		inline static constexpr auto MENU_NAME{ "LoadingMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kLoadingMenu };

		~LoadingMenu() override; // 00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;									// 01
		void MapCodeObjectFunctions() override;										// 02
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;			// 03
		void AdvanceMovie(REX::Float32 a_timeDelta, std::uint64_t a_time) override; // 04
		bool OnButtonEventRelease(const BSFixedString& a_eventName) override;		// 0F

		// override (BSInputEventUser)
		bool ShouldHandleEvent(const InputEvent* a_event) override;		 // 01
		void OnThumbstickEvent(const ThumbstickEvent* a_event) override; // 04
		void OnButtonEvent(const ButtonEvent* a_event) override;		 // 08

		static void StartTestingLoadingMenu()
		{
			using FuncType = decltype(&LoadingMenu::StartTestingLoadingMenu);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::LoadingMenu::StartTestingLoadingMenu };
			FUNC();
		}

		void PopulateLoadScreens()
		{
			using FuncType = decltype(&LoadingMenu::PopulateLoadScreens);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::LoadingMenu::PopulateLoadScreens };
			FUNC(this);
		}

		// members
		BGSLocation* loadLocation;				 // 0E0
		TESLoadScreen* artScreen;				 // 0E8
		std::array<std::byte, 0x10> upgrader;	 // 0F0 - TODO: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>, BSResource::EntryDBTraits<BSModelDB::DBTraits, BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>`
		BSTArray<TESLoadScreen*> validScreens;	 // 100
		void* foregroundModel;					 // 118 - BDModelDB::Handle
		NiAVObject* zoomTarget;					 // 120
		ImageSpaceLUTData lut;					 // 128
		std::uint32_t numNonDefaultScreens;		 // 198
		REX::Float32 modelAggregateRotation;	 // 19C
		REX::Float32 modelMinAggregateRotation;	 // 1A0
		REX::Float32 modelMaxAggregateRotation;	 // 1A4
		REX::Float32 frameTimeDelta;			 // 1A8
		REX::Float32 currentZoom;				 // 1AC
		REX::Float32 minZoom;					 // 1B0
		REX::Float32 maxZoom;					 // 1B4
		REX::Float32 horizontalBound;			 // 1B8
		REX::Float32 verticalBound;				 // 1BC
		REX::Float32 verticalBoundOffset;		 // 1BC
		NiMatrix3 initialRotation;				 // 1D0
		NiPoint2 calculatedPanMaxima;			 // 200
		NiPoint2 calculatedPanMinima;			 // 208
		std::uint64_t lastAdvanceMovieTime;		 // 210
		std::uint64_t lastUserInteractTime;		 // 218
		std::uint64_t lastPanTime;				 // 220
		std::uint64_t lastRotationTime;			 // 228
		std::uint64_t lastZoomTime;				 // 230
		BSSoundHandle rotationSoundLoop;		 // 238
		BSSoundHandle zoomSoundLoop;			 // 240
		BGSModelMaterialSwap* modelMaterialSwap; // 248
		NiPoint3 modelInitialRotation;			 // 250
		NiPoint3 modelTranslationOffset;		 // 25C
		REX::Float32 modelScale;				 // 268
		std::uint32_t numFrames;				 // 26C
		bool loadingIntoInterior;				 // 270
		bool menuAdded;							 // 271
		bool leftButtonDown;					 // 272
		bool rightButtonDown;					 // 273
		bool allowRotation;						 // 274
		bool autoRotate;						 // 275
		bool autoRotateInvert;					 // 276
		bool holoMode;							 // 277
		bool loadScreenShown;					 // 278
		bool leftStickReady;					 // 279
		bool rightStickReady;					 // 27A
		bool leftStickWasPreviouslyActive;		 // 27B
		bool rightStickWasPreviouslyActive;		 // 27C
		bool modelRequested;					 // 27D
		bool pcKeysDebounced;					 // 27E
	};
	static_assert(sizeof(LoadingMenu) == 0x280);
}
