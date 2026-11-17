#include "RE/B/BSTimer.hpp"

namespace RE
{
	auto BSTimer::GetSingleton() noexcept -> BSTimer*
	{
		static const auto SINGLETON = REL::Relocation<BSTimer*>(ID::BSTimer::Singleton);
		return SINGLETON.get();
	}

	auto BSTimer::GetRuntimeData() noexcept -> BSTimer::RuntimeData&
	{
		return REL::GetMemberAt<RuntimeData>(Offset::BSTimer::RuntimeData, this);
	}

	auto BSTimer::GetRuntimeData() const noexcept -> const BSTimer::RuntimeData&
	{
		return REL::GetMemberAt<const RuntimeData>(Offset::BSTimer::RuntimeData, this);
	}

	auto BSTimer::GetGlobalTimeMultiplier() noexcept -> REX::Float32&
	{
		static const auto GLOBAL_TIME_MULTIPLIER = REL::Relocation<REX::Float32*>(ID::BSTimer::GlobalTimeMultiplier);
		return *GLOBAL_TIME_MULTIPLIER;
	}

	auto BSTimer::GetGlobalTimeMultiplierTarget() noexcept -> REX::Float32&
	{
		static const auto GLOBAL_TIME_MULTIPLIER_TARGET =
			REL::Relocation<REX::Float32*>{ID::BSTimer::GlobalTimeMultiplierTarget};
		return *GLOBAL_TIME_MULTIPLIER_TARGET;
	}

	void BSTimer::SetGlobalTimeMultiplier(REX::Float32 a_timeMult, bool a_now)
	{
		using FuncType = decltype(&BSTimer::SetGlobalTimeMultiplier);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSTimer::SetGlobalTimeMultiplier);
		std::invoke(FUNC, this, a_timeMult, a_now);
	}
}
