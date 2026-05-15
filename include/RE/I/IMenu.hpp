#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSInputEventUser.hpp"
#include "RE/B/BSTAtomicValue.hpp"
#include "RE/N/NiRect.hpp"
#include "RE/S/SWFToCodeFunctionHandler.hpp"

#include "Scaleform/P/Ptr.hpp"

namespace RE
{
	enum class MENU_RENDER_CONTEXT : std::int32_t;
	enum class UI_DEPTH_PRIORITY : std::int32_t;
	enum class UI_MENU_FLAGS : std::uint32_t;
	enum class UI_MESSAGE_RESULTS : std::int32_t;

	class ButtonEvent;
	class UIMessage;
	class IUIMessageData;
}

namespace RE::UserEvents
{
	enum class INPUT_CONTEXT_ID : std::int32_t;
}

namespace RE
{
	class /*__declspec(novtable)*/ IMenu
		: public SWFToCodeFunctionHandler, // 00
		  public BSInputEventUser		   // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IMenu };
		inline static constexpr auto VTABLE{ VTABLE::IMenu };

		// Has to be an instance of `MovieClip`.
		inline static constexpr auto ROOT_VAR_NAME = "root1"sv;
		// `function get BGSCodeObj():Object;`, `function set BGSCodeObj(value:Object):void;`
		inline static constexpr auto CODE_OBJECT_VAR_NAME = "BGSCodeObj"sv;
		// `function get f4se():Object;`, `function set f4se(value:Object):void;`
		inline static constexpr auto F4SE_CODE_OBJECT_VAR_NAME = "f4se"sv;
		// `function onCodeObjCreate();`
		inline static constexpr auto ON_CODE_OBJECT_CREATED_FUNC_NAME = "onCodeObjCreate"sv;
		// `function onCodeObjDestruction();`
		inline static constexpr auto ON_CODE_OBJECT_DESTROYED_FUNC_NAME = "onCodeObjDestruction"sv;
		// `function onApplyColorChange(red:Number, green:Number, blue:Number, multiplier:Number):Array;`
		inline static constexpr auto F4SE_ON_APPLY_COLOR_CHANGE_FUNC_NAME = "onApplyColorChange"sv;
		// `function ProcessUserEvent(eventName:String, isPressed:Boolean):void;`
		inline static constexpr auto PROCESS_USER_EVENT_FUNC_NAME = "ProcessUserEvent"sv;
		// `function SetSafeRect(safeX:Number, safeY:Number):void;`
		inline static constexpr auto SET_SAFE_RECT_FUNC_NAME = "SetSafeRect"sv;
		// `function SetPlatform(platformType:uint, ps3Switch:Boolean):void;`
		inline static constexpr auto SET_PLATFORM_FUNC_NAME = "SetPlatform"sv;

		IMenu();

		~IMenu() override; // 00

		// override (BSInputEventUser)
		bool ShouldHandleEvent(const InputEvent* a_event) override; // 01
		void OnButtonEvent(const ButtonEvent* a_event) override;	// 08

		// add
		virtual UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message);													   // 03
		virtual void AdvanceMovie(REX::Float32 a_timeDelta, std::uint64_t a_time);											   // 04
		virtual void PreDisplay() { return; }																				   // 05
		virtual void PostDisplay() { return; }																				   // 06
		virtual bool PassesRenderConditionText(MENU_RENDER_CONTEXT a_reason, const BSFixedString& a_customRendererName) const; // 07
		virtual void SetIsTopButtonBar([[maybe_unused]] bool a_isTopButtonBar) { return; }									   // 08
		virtual void OnMenuStackChanged(const BSFixedString& a_topMenuName, bool a_passesTopMenuTest);						   // 09
		virtual void OnMenuDisplayStateChanged() { return; }																   // 0A
		virtual void OnAddedToMenuStack();																					   // 0B
		virtual void OnRemovedFromMenuStack();																				   // 0C
		virtual bool CanAdvanceMovie(bool a_pauseMenuShowing);																   // 0D
		virtual bool CanHandleWhenDisabled([[maybe_unused]] const ButtonEvent* a_event) { return false; }					   // 0E
		virtual bool OnButtonEventRelease([[maybe_unused]] const BSFixedString& a_eventName) { return false; }				   // 0F
		virtual bool CacheShaderFXQuadsForRenderer_Impl() { return false; }													   // 10
		virtual void TransferCachedShaderFXQuadsForRenderer([[maybe_unused]] const BSFixedString& a_rendererName) { return; }  // 11
		virtual void SetViewportRect([[maybe_unused]] const NiRect<REX::Float32>& a_viewportRect) { return; }				   // 12

		SF_HEAP_REDEFINE_NEW(IMenu);

		void DoAdvanceMovie(REX::Float32 a_timeDelta);
		[[nodiscard]] bool IsMenuDisplayEnabled() const noexcept;
		[[nodiscard]] ::Scaleform::GFx::Value GetNativeCodeObject() const;
		void OnSetSafeRect();
		UI_MESSAGE_RESULTS ProcessScaleformEvent(::Scaleform::GFx::Movie* a_movie, const IUIMessageData* a_data);
		void RefreshPlatform();
		void SetMenuCodeObject(::Scaleform::GFx::Movie& a_movie, const char* a_menuObjPath);

		// members
		::Scaleform::GFx::Value menuObj;									// 20
		::Scaleform::Ptr<::Scaleform::GFx::Movie> uiMovie;					// 40
		BSFixedString customRendererName;									// 48
		BSFixedString menuName;												// 50
		REX::EnumSet<UI_MENU_FLAGS, std::uint32_t> menuFlags;				// 58
		BSTAtomicValue<std::uint32_t> advanceWithoutRenderCount{ 0 };		// 5C
		bool passesTopMenuTest{ true };										// 60
		bool menuCanBeVisible{ true };										// 61
		bool hasQuadsForCustomRenderer{ false };							// 62
		bool hasDoneFirstAdvanceMovie{ false };								// 63
		REX::Enum<UI_DEPTH_PRIORITY, std::int32_t> depthPriority;			// 64
		REX::Enum<UserEvents::INPUT_CONTEXT_ID, std::int32_t> inputContext; // 68
	};
	static_assert(sizeof(IMenu) == 0x70);
}
