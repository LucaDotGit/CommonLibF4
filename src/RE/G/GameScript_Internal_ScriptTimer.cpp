#include "RE/G/GameScript_Internal_ScriptTimer.hpp"

namespace RE::GameScript::Internal
{
	static constexpr auto MILLIS_IN_SECOND = static_cast<REX::Float32>(std::chrono::duration_cast<std::chrono::milliseconds>(1s).count());
	static constexpr auto HOURS_PER_REAL_HOUR = 1.0_f32 / 24.0_f32;

	REX::Float32 ScriptTimer::GetRemainingSeconds(std::uint32_t a_currentTime) const noexcept
	{
		return static_cast<REX::Float32>(targetTime - a_currentTime) / MILLIS_IN_SECOND;
	}

	void ScriptTimer::SetRemainingSeconds(std::uint32_t a_currentTime, REX::Float32 a_seconds) noexcept
	{
		targetTime = a_currentTime + static_cast<std::uint32_t>(a_seconds * MILLIS_IN_SECOND);
	}

	REX::Float32 ScriptTimer::GetRemainingGameTimeSeconds(std::uint32_t a_currentGameTime) const noexcept
	{
		return static_cast<REX::Float32>(targetTime - a_currentGameTime) / MILLIS_IN_SECOND / HOURS_PER_REAL_HOUR;
	}

	void ScriptTimer::SetRemainingGameTimeSeconds(std::uint32_t a_currentGameTime, REX::Float32 a_seconds) noexcept
	{
		targetTime = a_currentGameTime + static_cast<std::uint32_t>(a_seconds * MILLIS_IN_SECOND * HOURS_PER_REAL_HOUR);
	}
}
