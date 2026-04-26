#include "RE/P/PlayerControls.hpp"

namespace RE
{
	PlayerControls* PlayerControls::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<PlayerControls**>{ ID::PlayerControls::Singleton };
		return *SINGLETON;
	}

	bool PlayerControls::CanPerformAction(DEFAULT_OBJECT a_action)
	{
		using FuncType = decltype(&PlayerControls::CanPerformAction);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerControls::CanPerformAction };
		return std::invoke(FUNC, this, a_action);
	}

	bool PlayerControls::DoAction(DEFAULT_OBJECT a_action, ActionInput::ACTIONPRIORITY a_priority)
	{
		using FuncType = decltype(&PlayerControls::DoAction);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerControls::DoAction };
		return std::invoke(FUNC, this, a_action, a_priority);
	}

	void PlayerControls::RegisterHandler(PlayerInputHandler* a_handler)
	{
		const auto arrayLock = BSAutoLock(actorArraySpinLock);
		handlers.push_back(a_handler);
	}
	void PlayerControls::RegisterHandler(HeldStateHandler* a_handler)
	{
		const auto arrayLock = BSAutoLock(actorArraySpinLock);
		heldStateHandlers.push_back(a_handler);
	}
}
