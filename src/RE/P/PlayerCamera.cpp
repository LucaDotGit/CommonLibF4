#include "RE/P/PlayerCamera.hpp"

namespace RE
{
	PlayerCamera* PlayerCamera::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<PlayerCamera**>{ ID::PlayerCamera::Singleton };
		return *SINGLETON;
	}

	bool PlayerCamera::IsStateActive(CameraStates a_state) const noexcept
	{
		return currentState && currentState->id == a_state;
	}

	bool PlayerCamera::IsStateActive(const BSTSmartPointer<TESCameraState>& a_state) const noexcept
	{
		return currentState && a_state && currentState->id == a_state->id;
	}

	BSTSmartPointer<TESCameraState> PlayerCamera::GetState(CameraStates a_state) const
	{
		REX::Assert(a_state >= CameraStates::kMin && a_state < CameraStates::kMax);
		return cameraStates[std::to_underlying(a_state)];
	}

	BSTSmartPointer<TESCameraState> PlayerCamera::GetState() const
	{
		return currentState;
	}

	void PlayerCamera::SetState(TESCameraState* a_newState)
	{
		// F4SE injects into this function
		using FuncType = void(PlayerCamera*, TESCameraState*);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerCamera::SetState };
		FUNC(this, a_newState);
	}

	void PlayerCamera::SetState(const BSTSmartPointer<TESCameraState>& a_newState)
	{
		SetState(a_newState.get());
	}

	void PlayerCamera::ToggleFreeCameraMode(bool a_freezeTime)
	{
		using FuncType = decltype(&PlayerCamera::ToggleFreeCameraMode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerCamera::ToggleFreeCameraMode };
		FUNC(this, a_freezeTime);
	}

	void PlayerCamera::StartPipboyMode(bool a_forcePipboyModeCamera)
	{
		using FuncType = decltype(&PlayerCamera::StartPipboyMode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerCamera::StartPipboyMode };
		FUNC(this, a_forcePipboyModeCamera);
	}

	void PlayerCamera::StopPipboyMode()
	{
		using FuncType = decltype(&PlayerCamera::StopPipboyMode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerCamera::StopPipboyMode };
		FUNC(this);
	}
}
