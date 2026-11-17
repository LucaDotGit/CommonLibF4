#pragma once

#include "RE/B/BSInputEventReceiver.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/S/ScreenshotHandler.hpp"

namespace RE
{
	class BSInputEventUser;
	class CameraZoomHandler;
	class ClickHandler;
	class DisconnectHandler;
	class GFxConvertHandler;
	class MenuOpenHandler;
	class PipboyHandler;
	class QuickSaveLoadHandler;

#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class MenuControls :
		public BSInputEventReceiver,		 // 0x00
		public BSTSingletonSDM<MenuControls> // 0x10
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::MenuControls;
		inline static constexpr const auto& VTABLE = VTABLE::MenuControls;

		// override (BSInputEventReceiver)
		void PerformInputProcessing(const InputEvent* a_queueHead) override; // 0x00

		[[nodiscard]]
		static auto GetSingleton() noexcept -> MenuControls*;

		[[nodiscard]]
		auto IsInputHandlerRegistered(const BSInputEventUser* a_inputHandler) const -> bool;
		auto RegisterInputHandler(BSInputEventUser* a_inputHandler) -> bool;
		auto UnregisterInputHandler(const BSInputEventUser* a_inputHandler) -> bool;

		void ForcePauseGame() const;
		void ForceResumeGame() const;
		auto QueueScreenshot() const -> bool;

		// members
		BSTArray<BSInputEventUser*> handlers;		// 0x18
		GFxConvertHandler* convertHandler;			// 0x30
		DisconnectHandler* disconnectHandler;		// 0x38
		ClickHandler* clickHandler;					// 0x40
		QuickSaveLoadHandler* quickSaveLoadHandler; // 0x48
		MenuOpenHandler* menuOpenHandler;			// 0x50
		ScreenshotHandler* screenshotHandler;		// 0x58
		CameraZoomHandler* cameraZoomHandler;		// 0x60
		PipboyHandler* pipboyHandler;				// 0x68
	};

	static_assert(sizeof(MenuControls) == 0x70);

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}
