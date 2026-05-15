#include "RE/B/BSTimer.hpp"

namespace RE
{
	BSTimer* BSTimer::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<BSTimer*>{ ID::BSTimer::Singleton };
		return SINGLETON.get();
	}

	BSTimer::RuntimeData& BSTimer::GetRuntimeData() noexcept
	{
		return REL::GetMemberAt<RuntimeData>(Offset::BSTimer::RuntimeData, this);
	}

	const BSTimer::RuntimeData& BSTimer::GetRuntimeData() const noexcept
	{
		return REL::GetMemberAt<const RuntimeData>(Offset::BSTimer::RuntimeData, this);
	}

	REX::Float32& BSTimer::QGlobalTimeMultiplier()
	{
		static const auto GLOBAL_TIME_MULTIPLIER = REL::Relocation<REX::Float32*>{ ID::BSTimer::GlobalTimeMultiplier };
		return *GLOBAL_TIME_MULTIPLIER;
	}

	REX::Float32& BSTimer::QGlobalTimeMultiplierTarget()
	{
		static const auto GLOBAL_TIME_MULTIPLIER_TARGET = REL::Relocation<REX::Float32*>{ ID::BSTimer::GlobalTimeMultiplierTarget };
		return *GLOBAL_TIME_MULTIPLIER_TARGET;
	}

	BSTimer::Seconds BSTimer::GetGlobalTimeMultiplier()
	{
		return Seconds(QGlobalTimeMultiplier());
	}

	BSTimer::Seconds BSTimer::GetGlobalTimeMultiplierTarget()
	{
		return Seconds(QGlobalTimeMultiplierTarget());
	}

	void BSTimer::SetGlobalTimeMultiplier(REX::Float32 a_mult, bool a_now)
	{
		using FuncType = decltype(&BSTimer::SetGlobalTimeMultiplier);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSTimer::SetGlobalTimeMultiplier };
		std::invoke(FUNC, this, a_mult, a_now);
	}

	BSTimer::Milliseconds BSTimer::GetInitTime() const noexcept
	{
		return Milliseconds(highPrecisionInitTime);
	}

	BSTimer::Seconds BSTimer::GetDeltaTime() const noexcept
	{
		return Seconds(delta);
	}

	BSTimer::Seconds BSTimer::GetRealTimeDeltaTime() const noexcept
	{
		return Seconds(realTimeDelta);
	}

	BSTimer::Milliseconds BSTimer::GetLastTime() const noexcept
	{
		return Milliseconds(lastTime);
	}

	BSTimer::Milliseconds BSTimer::GetFirstTime() const noexcept
	{
		return Milliseconds(GetRuntimeData().firstTime);
	}

	BSTimer::Milliseconds BSTimer::GetDisabledLastTime() const noexcept
	{
		return Milliseconds(GetRuntimeData().disabledLastTime);
	}

	BSTimer::Milliseconds BSTimer::GetDisabledFirstTime() const noexcept
	{
		return Milliseconds(GetRuntimeData().disabledFirstTime);
	}
}
