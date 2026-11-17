#include "RE/I/IMenu.hpp"

#include "RE/B/ButtonEvent.hpp"
#include "RE/I/IUIMessageData.hpp"
#include "RE/P/PauseMenu.hpp"
#include "RE/U/UIMessage.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"
#include "RE/U/UI_MENU_FLAGS.hpp"
#include "RE/U/UI_MESSAGE_RESULTS.hpp"
#include "RE/U/UserEvents.hpp"
#include "Scaleform/G/GFx_ASMovieRootBase.hpp"
#include "Scaleform/G/GFx_Movie.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace RE
{
	IMenu::IMenu() :
		menuFlags(UI_MENU_FLAGS::None),
		depthPriority(UI_DEPTH_PRIORITY::Standard),
		inputContext(UserEvents::INPUT_CONTEXT_ID::None)
	{
		// REL::EmplaceVtable(this);
	}

	IMenu::~IMenu()
	{
		if (!uiMovie) {
			return;
		}

		const auto threadId = Scaleform::GetCurrentThreadId();
		uiMovie->SetCaptureThread(threadId);

		auto* heap = uiMovie->GetHeap();
		if (heap) {
			heap->AssignToCurrentThread();
		}
	}

	auto IMenu::ShouldHandleEvent(const InputEvent* a_event) -> bool
	{
		using FuncType = decltype(&IMenu::ShouldHandleEvent);
		static const auto FUNC = REL::Relocation<FuncType>(ID::IMenu::ShouldHandleEvent);
		return std::invoke(FUNC, this, a_event);
	}

	void IMenu::OnButtonEvent(const ButtonEvent* a_event)
	{
		if (!a_event || !inputEventHandlingEnabled || !menuObj.IsAnyObject()) {
			return;
		}

		if (!menuObj.HasMember(PROCESS_USER_EVENT_FUNC_NAME.data())) {
			return;
		}

		const auto userEventName =
			a_event->disabled && CanHandleWhenDisabled(a_event) ? a_event->QRawUserEvent() : a_event->QUserEvent();

		const auto args =
			std::array{Scaleform::GFx::Value(userEventName.data()), Scaleform::GFx::Value(a_event->QJustPressed())};

		menuObj.Invoke(PROCESS_USER_EVENT_FUNC_NAME.data(), args);
	}

	auto IMenu::ProcessMessage(UIMessage& a_message) -> UI_MESSAGE_RESULTS
	{
		switch (a_message.type.get()) {
			case UI_MESSAGE_TYPE::Show:
			case UI_MESSAGE_TYPE::Hide: {
				return UI_MESSAGE_RESULTS::Handled;
			}
			case UI_MESSAGE_TYPE::ScaleformEvent: {
				return ProcessScaleformEvent(uiMovie.get(), a_message.QData());
			}
			case UI_MESSAGE_TYPE::UpdateController: {
				RefreshPlatform();
				return UI_MESSAGE_RESULTS::PassOn;
			}
			default: {
				return UI_MESSAGE_RESULTS::PassOn;
			}
		}
	}

	void IMenu::AdvanceMovie(DeltaTime a_deltaTime, [[maybe_unused]] std::time_t a_time)
	{
		if (!uiMovie) {
			return;
		}

		DoAdvanceMovie(a_deltaTime);
		hasDoneFirstAdvanceMovie = true;
	}

	void IMenu::PreDisplay()
	{
		return;
	}

	void IMenu::PostDisplay()
	{
		return;
	}

	auto IMenu::PassesRenderConditionText(MENU_RENDER_CONTEXT a_reason, const BSFixedString& a_customRendererName) const
		-> bool
	{
		using FuncType = decltype(&IMenu::PassesRenderConditionText);
		static const auto FUNC = REL::Relocation<FuncType>(ID::IMenu::PassesRenderConditionText);
		return std::invoke(FUNC, this, a_reason, a_customRendererName);
	}

	void IMenu::SetIsTopButtonBar([[maybe_unused]] bool a_isTopButtonBar)
	{
		return;
	}

	void IMenu::OnMenuStackChanged(const BSFixedString& a_topMenuName, bool a_passesTopMenuTest)
	{
		const auto topMenuTest = a_passesTopMenuTest || (a_topMenuName == PauseMenu::MENU_NAME &&
														 menuFlags.any(UI_MENU_FLAGS::AdvancesUnderPauseMenu));
		if (passesTopMenuTest != topMenuTest) {
			passesTopMenuTest = topMenuTest;
			OnMenuDisplayStateChanged();
		}
	}

	void IMenu::OnMenuDisplayStateChanged()
	{
		return;
	}

	void IMenu::OnAddedToMenuStack()
	{
		menuFlags.set(UI_MENU_FLAGS::OnStack);
		OnMenuDisplayStateChanged();
	}

	void IMenu::OnRemovedFromMenuStack()
	{
		menuFlags.reset(UI_MENU_FLAGS::OnStack);
		OnMenuDisplayStateChanged();
	}

	auto IMenu::CanAdvanceMovie(bool a_pauseMenuShowing) -> bool
	{
		return !a_pauseMenuShowing ||
			   depthPriority > UI_DEPTH_PRIORITY::GameMessage ||
			   menuFlags.any(UI_MENU_FLAGS::AdvancesUnderPauseMenu);
	}

	auto IMenu::CanHandleWhenDisabled([[maybe_unused]] const ButtonEvent* a_event) -> bool
	{
		return false;
	}

	auto IMenu::OnButtonEventRelease([[maybe_unused]] const BSFixedString& a_eventName) -> bool
	{
		return false;
	}

	auto IMenu::CacheShaderFXQuadsForRenderer_Impl() -> bool
	{
		return false;
	}

	void IMenu::TransferCachedShaderFXQuadsForRenderer([[maybe_unused]] const BSFixedString& a_rendererName)
	{
		return;
	}

	void IMenu::SetViewportRect([[maybe_unused]] const NiRectF& a_viewportRect)
	{
		return;
	}

	void IMenu::DoAdvanceMovie(DeltaTime a_deltaTime)
	{
		advanceWithoutRenderCount++;
		uiMovie->Advance(a_deltaTime);
	}

	auto IMenu::GetNativeCodeObject() const -> Scaleform::GFx::Value
	{
		if (!menuObj.IsAnyObject()) {
			return {};
		}

		auto nativeCodeObject = Scaleform::GFx::Value();
		if (!menuObj.GetMember(CODE_OBJECT_VAR_NAME.data(), std::addressof(nativeCodeObject)) ||
			!nativeCodeObject.IsAnyObject()) {
			return {};
		}

		return nativeCodeObject;
	}

	auto IMenu::IsMenuDisplayEnabled() const noexcept -> bool
	{
		return passesTopMenuTest && menuCanBeVisible;
	}

	void IMenu::OnSetSafeRect()
	{
		using FuncType = decltype(&IMenu::OnSetSafeRect);
		static const auto FUNC = REL::Relocation<FuncType>(ID::IMenu::OnSetSafeRect);
		std::invoke(FUNC, this);
	}

	auto IMenu::ProcessScaleformEvent(Scaleform::GFx::Movie* a_movie, const IUIMessageData* a_data)
		-> UI_MESSAGE_RESULTS
	{
		using FuncType = decltype(&IMenu::ProcessScaleformEvent);
		static const auto FUNC = REL::Relocation<FuncType>(ID::IMenu::ProcessScaleformEvent);
		return std::invoke(FUNC, this, a_movie, a_data);
	}

	void IMenu::RefreshPlatform()
	{
		using FuncType = decltype(&IMenu::RefreshPlatform);
		static const auto FUNC = REL::Relocation<FuncType>(ID::IMenu::RefreshPlatform);
		std::invoke(FUNC, this);
	}

	void IMenu::SetMenuCodeObject(Scaleform::GFx::Movie& a_movie, const char* a_menuObjPath)
	{
		auto newMenuObject = Scaleform::GFx::Value();
		if (!a_movie.GetVariable(std::addressof(newMenuObject), a_menuObjPath) || !newMenuObject.IsAnyObject()) {
			return;
		}

		menuObj = std::move(newMenuObject);
		RegisterCodeObject(a_movie, menuObj);
	}
}
