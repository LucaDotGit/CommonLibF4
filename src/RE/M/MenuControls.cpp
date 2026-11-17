#include "RE/M/MenuControls.hpp"

namespace RE
{
	auto MenuControls::GetSingleton() noexcept -> MenuControls*
	{
		static const auto SINGLETON = REL::Relocation<MenuControls**>(ID::MenuControls::Singleton);
		return *SINGLETON;
	}

	void MenuControls::ForcePauseGame() const
	{
		using FuncType = decltype(&MenuControls::ForcePauseGame);
		static const auto FUNC = REL::Relocation<FuncType>(RE::ID::MenuControls::ForcePauseGame);
		std::invoke(FUNC, this);
	}

	void MenuControls::ForceResumeGame() const
	{
		using FuncType = decltype(&MenuControls::ForceResumeGame);
		static const auto FUNC = REL::Relocation<FuncType>(RE::ID::MenuControls::ForceResumeGame);
		std::invoke(FUNC, this);
	}

	auto MenuControls::QueueScreenshot() const -> bool
	{
		if (!screenshotHandler || screenshotHandler->screenshotQueued) {
			return false;
		}

		screenshotHandler->screenshotQueued = true;
		return true;
	}

	auto MenuControls::IsInputHandlerRegistered(const BSInputEventUser* a_inputHandler) const -> bool
	{
		return std::ranges::contains(handlers, a_inputHandler);
	}

	auto MenuControls::RegisterInputHandler(BSInputEventUser* a_inputHandler) -> bool
	{
		if (IsInputHandlerRegistered(a_inputHandler)) {
			return false;
		}

		handlers.push_back(a_inputHandler);
		return true;
	}

	auto MenuControls::UnregisterInputHandler(const BSInputEventUser* a_inputHandler) -> bool
	{
		const auto* handlerIt = std::ranges::find(handlers, a_inputHandler);
		if (handlerIt == handlers.end()) {
			return false;
		}

		handlers.erase(handlerIt);
		return true;
	}
}
