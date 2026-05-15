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
		std::invoke(FUNC, this, a_newState);
	}

	void PlayerCamera::SetState(const BSTSmartPointer<TESCameraState>& a_newState)
	{
		SetState(a_newState.get());
	}

	bool PlayerCamera::GetCameraPosition(NiPoint3& a_outPosition, bool a_addPlayerPos) const
	{
		using FuncType = decltype(&PlayerCamera::GetCameraPosition);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerCamera::GetCameraPosition };
		return std::invoke(FUNC, this, std::ref(a_outPosition), a_addPlayerPos);
	}

	void PlayerCamera::ToggleFreeCameraMode(bool a_freezeTime)
	{
		using FuncType = decltype(&PlayerCamera::ToggleFreeCameraMode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerCamera::ToggleFreeCameraMode };
		std::invoke(FUNC, this, a_freezeTime);
	}

	void PlayerCamera::StartPipboyMode(bool a_forcePipboyModeCamera)
	{
		using FuncType = decltype(&PlayerCamera::StartPipboyMode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerCamera::StartPipboyMode };
		std::invoke(FUNC, this, a_forcePipboyModeCamera);
	}

	void PlayerCamera::StopPipboyMode()
	{
		using FuncType = decltype(&PlayerCamera::StopPipboyMode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerCamera::StopPipboyMode };
		std::invoke(FUNC, this);
	}
}
