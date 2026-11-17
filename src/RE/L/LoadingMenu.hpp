#pragma once

#include "RE/B/BSSoundHandle.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/I/ImageSpaceLUTData.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint2.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class BGSModelMaterialSwap;
	class NiAVObject;

	class __declspec(novtable) LoadingMenu : public GameMenuBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::LoadingMenu;
		inline static constexpr const auto& VTABLE = VTABLE::LoadingMenu;
		inline static constexpr auto MENU_NAME = "LoadingMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::LoadingMenu;

		~LoadingMenu() override; // 0x00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;									  // 0x01
		void MapCodeObjectFunctions() override;										  // 0x02
		auto ProcessMessage(UIMessage& a_message) -> UI_MESSAGE_RESULTS override;	  // 0x03
		void AdvanceMovie(DeltaTime a_deltaTime, std::time_t a_time) override;		  // 0x04
		auto OnButtonEventRelease(const BSFixedString& a_eventName) -> bool override; // 0x0F

		// override (BSInputEventUser)
		auto ShouldHandleEvent(const InputEvent* a_event) -> bool override; // 0x01
		void OnThumbstickEvent(const ThumbstickEvent* a_event) override;	// 0x04
		void OnButtonEvent(const ButtonEvent* a_event) override;			// 0x08

		static void StartTestingLoadingMenu()
		{
			using FuncType = decltype(&LoadingMenu::StartTestingLoadingMenu);
			static const auto FUNC = REL::Relocation<FuncType>(ID::LoadingMenu::StartTestingLoadingMenu);
			std::invoke(FUNC);
		}

		void PopulateLoadScreens()
		{
			using FuncType = decltype(&LoadingMenu::PopulateLoadScreens);
			static const auto FUNC = REL::Relocation<FuncType>(ID::LoadingMenu::PopulateLoadScreens);
			std::invoke(FUNC, this);
		}

		// members
		BGSLocation* loadLocation; // 0x0E0
		TESLoadScreen* artScreen;  // 0x0E8
		std::array<std::byte, 0x10>
			upgrader; // 0x0F0 - To-Do: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>,
					  // BSResource::EntryDBTraits<BSModelDB::DBTraits,
					  // BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>`
		BSTArray<TESLoadScreen*> validScreens;	 // 0x100
		void* foregroundModel;					 // 0x118 - BDModelDB::Handle
		NiAVObject* zoomTarget;					 // 0x120
		ImageSpaceLUTData lut;					 // 0x128
		std::uint32_t numNonDefaultScreens;		 // 0x198
		REX::Float32 modelAggregateRotation;	 // 0x19C
		REX::Float32 modelMinAggregateRotation;	 // 0x1A0
		REX::Float32 modelMaxAggregateRotation;	 // 0x1A4
		REX::Float32 frameTimeDelta;			 // 0x1A8
		REX::Float32 currentZoom;				 // 0x1AC
		REX::Float32 minZoom;					 // 0x1B0
		REX::Float32 maxZoom;					 // 0x1B4
		REX::Float32 horizontalBound;			 // 0x1B8
		REX::Float32 verticalBound;				 // 0x1BC
		REX::Float32 verticalBoundOffset;		 // 0x1BC
		NiMatrix3 initialRotation;				 // 0x1D0
		NiPoint2 calculatedPanMaxima;			 // 0x200
		NiPoint2 calculatedPanMinima;			 // 0x208
		std::uint64_t lastAdvanceMovieTime;		 // 0x210
		std::uint64_t lastUserInteractTime;		 // 0x218
		std::uint64_t lastPanTime;				 // 0x220
		std::uint64_t lastRotationTime;			 // 0x228
		std::uint64_t lastZoomTime;				 // 0x230
		BSSoundHandle rotationSoundLoop;		 // 0x238
		BSSoundHandle zoomSoundLoop;			 // 0x240
		BGSModelMaterialSwap* modelMaterialSwap; // 0x248
		NiPoint3 modelInitialRotation;			 // 0x250
		NiPoint3 modelTranslationOffset;		 // 0x25C
		REX::Float32 modelScale;				 // 0x268
		std::uint32_t numFrames;				 // 0x26C
		bool loadingIntoInterior;				 // 0x270
		bool menuAdded;							 // 0x271
		bool leftButtonDown;					 // 0x272
		bool rightButtonDown;					 // 0x273
		bool allowRotation;						 // 0x274
		bool autoRotate;						 // 0x275
		bool autoRotateInvert;					 // 0x276
		bool holoMode;							 // 0x277
		bool loadScreenShown;					 // 0x278
		bool leftStickReady;					 // 0x279
		bool rightStickReady;					 // 0x27A
		bool leftStickWasPreviouslyActive;		 // 0x27B
		bool rightStickWasPreviouslyActive;		 // 0x27C
		bool modelRequested;					 // 0x27D
		bool pcKeysDebounced;					 // 0x27E
	};

	static_assert(sizeof(LoadingMenu) == 0x280);
}
