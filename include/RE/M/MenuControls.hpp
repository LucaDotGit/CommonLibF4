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

#if _MSC_VER > 0l
#pragma warning(push)
#pragma warning(disable : 4265) // 'class': class has virtual functions, but destructor is not virtual
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class MenuControls
		: public BSInputEventReceiver,		   // 00
		  public BSTSingletonSDM<MenuControls> // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::MenuControls };
		inline static constexpr auto VTABLE{ VTABLE::MenuControls };

		// override (BSInputEventReceiver)
		void PerformInputProcessing(const InputEvent* a_queueHead) override; // 00

		[[nodiscard]] static MenuControls* GetSingleton();

		bool QueueScreenshot() const;

		// members
		BSTArray<BSInputEventUser*> handlers;		// 18
		GFxConvertHandler* convertHandler;			// 30
		DisconnectHandler* disconnectHandler;		// 38
		ClickHandler* clickHandler;					// 40
		QuickSaveLoadHandler* quickSaveLoadHandler; // 48
		MenuOpenHandler* menuOpenHandler;			// 50
		ScreenshotHandler* screenshotHandler;		// 58
		CameraZoomHandler* cameraZoomHandler;		// 60
		PipboyHandler* pipboyHandler;				// 68
	};
	static_assert(sizeof(MenuControls) == 0x70);

#if _MSC_VER > 0l
#pragma warning(pop)
#endif
}
