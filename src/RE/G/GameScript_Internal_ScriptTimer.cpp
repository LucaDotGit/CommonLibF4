#include "RE/G/GameScript_Internal_ScriptTimer.hpp"

namespace RE::GameScript::Internal
{
	static constexpr auto MILLIS_IN_SECOND =
		static_cast<REX::Float32>(std::chrono::duration_cast<ScriptTimer::Miliseconds>(1s).count());
	static constexpr auto HOURS_PER_REAL_HOUR = static_cast<REX::Float32>(1.0) / static_cast<REX::Float32>(24.0);

	auto ScriptTimer::GetRemainingSeconds(ScriptTimer::Miliseconds a_currentTime) const noexcept -> ScriptTimer::Seconds
	{
		return Seconds{static_cast<REX::Float32>((targetTime - a_currentTime).count()) / MILLIS_IN_SECOND};
	}

	void ScriptTimer::SetRemainingSeconds(ScriptTimer::Miliseconds a_currentTime, ScriptTimer::Seconds a_seconds)
		noexcept
	{
		targetTime =
			Miliseconds{a_currentTime.count() + static_cast<std::uint32_t>(a_seconds.count() * MILLIS_IN_SECOND)};
	}

	auto ScriptTimer::GetRemainingGameTimeSeconds(ScriptTimer::Miliseconds a_currentGameTime) const noexcept
		-> ScriptTimer::Seconds
	{
		return Seconds{
			static_cast<REX::Float32>((targetTime - a_currentGameTime).count()) / MILLIS_IN_SECOND / HOURS_PER_REAL_HOUR
		};
	}

	void ScriptTimer::SetRemainingGameTimeSeconds(
		ScriptTimer::Miliseconds a_currentGameTime,
		ScriptTimer::Seconds a_seconds) noexcept
	{
		targetTime = Miliseconds{
			a_currentGameTime.count() +
			static_cast<std::uint32_t>(a_seconds.count() * MILLIS_IN_SECOND * HOURS_PER_REAL_HOUR)
		};
	}
}
