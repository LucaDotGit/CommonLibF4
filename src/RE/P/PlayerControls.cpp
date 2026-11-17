#include "RE/P/PlayerControls.hpp"

#include "RE/B/BSSpinLock.hpp"

namespace RE
{
	auto PlayerControls::GetSingleton() noexcept -> PlayerControls*
	{
		static const auto SINGLETON = REL::Relocation<PlayerControls**>(ID::PlayerControls::Singleton);
		return *SINGLETON;
	}

	auto PlayerControls::CanPerformAction(DEFAULT_OBJECT a_action) -> bool
	{
		using FuncType = decltype(&PlayerControls::CanPerformAction);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerControls::CanPerformAction);
		return std::invoke(FUNC, this, a_action);
	}

	auto PlayerControls::DoAction(DEFAULT_OBJECT a_action, ActionInput::ACTIONPRIORITY a_priority) -> bool
	{
		using FuncType = decltype(&PlayerControls::DoAction);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerControls::DoAction);
		return std::invoke(FUNC, this, a_action, a_priority);
	}

	void PlayerControls::RegisterHandler(PlayerInputHandler* a_handler)
	{
		const auto arrayLock = BSAutoSpinLock(actorArraySpinLock);
		handlers.push_back(a_handler);
	}

	void PlayerControls::RegisterHandler(HeldStateHandler* a_handler)
	{
		const auto arrayLock = BSAutoSpinLock(actorArraySpinLock);
		heldStateHandlers.push_back(a_handler);
	}
}
