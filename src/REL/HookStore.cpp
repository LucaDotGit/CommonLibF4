#include "REL/HookStore.hpp"

#include "REL/IHook.hpp"

#include "REX/Log.hpp"
#include "REX/Stopwatch.hpp"

namespace REL
{
	bool HookStore::Contains(const REX::NotNull<std::shared_ptr<REL::IHook>>& a_hook) const noexcept
	{
		const auto hookHandle = a_hook->GetHandle();
		if (hookHandle == REL::INVALID_HOOK_HANDLE) {
			return false;
		}

		const auto mapLock = std::shared_lock(_mapMutex);
		return _hookMap.contains(hookHandle);
	}

	bool HookStore::Add(REX::NotNull<std::shared_ptr<REL::IHook>> a_hook)
	{
		const auto hookHandle = a_hook->GetHandle();
		if (hookHandle == REL::INVALID_HOOK_HANDLE) {
			return false;
		}

		const auto mapLock = std::scoped_lock(_mapMutex);

		const auto&& [_, hasInserted] = _hookMap.emplace(hookHandle, std::move(a_hook));
		return hasInserted;
	}

	bool HookStore::Remove(const REX::NotNull<std::shared_ptr<REL::IHook>>& a_hook) noexcept
	{
		const auto hookHandle = a_hook->GetHandle();
		if (hookHandle == REL::INVALID_HOOK_HANDLE) {
			return false;
		}

		const auto mapLock = std::scoped_lock(_mapMutex);

		const auto hookIt = _hookMap.find(hookHandle);
		if (hookIt == _hookMap.end()) {
			return false;
		}

		_hookMap.erase(hookIt);
		return true;
	}

	void HookStore::Clear() noexcept
	{
		const auto mapLock = std::scoped_lock(_mapMutex);
		_hookMap.clear();
	}

	void HookStore::Init()
	{
		const auto mapLock = std::scoped_lock(_mapMutex);

		REX::LogDebug("Initializing {} hooks"sv,
			_hookMap.size());

		auto stopwatch = REX::Stopwatch::StartNew();

		auto hookCount = static_cast<REL::HookHandle>(0);
		for (auto& [_, hook] : _hookMap) {
			if (hook->Init()) {
				hookCount++;
			}
		}

		stopwatch.Stop();

		REX::LogDebug("Initialized {} hooks in {}"sv,
			hookCount, std::chrono::duration_cast<std::chrono::duration<REX::Float64, std::milli>>(stopwatch.GetElapsedTime()));
	}

	void HookStore::Init(HookStep a_step)
	{
		const auto mapLock = std::scoped_lock(_mapMutex);

		REX::LogDebug("Initializing {} {} hooks"sv,
			_hookMap.size(), a_step);

		auto stopwatch = REX::Stopwatch::StartNew();

		auto hookCount = static_cast<REL::HookHandle>(0);
		for (auto& [_, hook] : _hookMap) {
			if (hook->GetStep() == a_step && hook->Init()) {
				hookCount++;
			}
		}

		stopwatch.Stop();

		REX::LogDebug("Initialized {} {} hooks in {}"sv,
			hookCount, a_step, std::chrono::duration_cast<std::chrono::duration<REX::Float64, std::milli>>(stopwatch.GetElapsedTime()));
	}

	void HookStore::Enable() noexcept
	{
		const auto mapLock = std::scoped_lock(_mapMutex);

		REX::LogDebug("Enabling {} hooks"sv,
			_hookMap.size());

		auto stopwatch = REX::Stopwatch::StartNew();

		auto hookCount = static_cast<REL::HookHandle>(0);
		for (auto& [_, hook] : _hookMap) {
			if (hook->Enable()) {
				hookCount++;
			}
		}

		stopwatch.Stop();

		REX::LogDebug("Enabled {} hooks in {}"sv,
			hookCount, std::chrono::duration_cast<std::chrono::duration<REX::Float64, std::milli>>(stopwatch.GetElapsedTime()));
	}

	bool HookStore::Enable(HookStep a_step) noexcept
	{
		const auto mapLock = std::scoped_lock(_mapMutex);

		REX::LogDebug("Enabling {} {} hooks"sv,
			_hookMap.size(), a_step);

		auto stopwatch = REX::Stopwatch::StartNew();

		auto hookCount = static_cast<REL::HookHandle>(0);
		for (auto& [_, hook] : _hookMap) {
			if (hook->GetStep() == a_step && hook->Enable()) {
				hookCount++;
			}
		}

		stopwatch.Stop();

		REX::LogDebug("Enabled {} {} hooks in {}"sv,
			hookCount, a_step, std::chrono::duration_cast<std::chrono::duration<REX::Float64, std::milli>>(stopwatch.GetElapsedTime()));

		return hookCount > 0;
	}

	void HookStore::Disable() noexcept
	{
		const auto mapLock = std::scoped_lock(_mapMutex);

		REX::LogDebug("Disabling {} hooks"sv,
			_hookMap.size());

		auto stopwatch = REX::Stopwatch::StartNew();

		auto hookCount = static_cast<REL::HookHandle>(0);
		for (auto& [_, hook] : _hookMap) {
			if (hook->Disable()) {
				hookCount++;
			}
		}

		stopwatch.Stop();

		REX::LogDebug("Disabled {} hooks in {}"sv,
			hookCount, std::chrono::duration_cast<std::chrono::duration<REX::Float64, std::milli>>(stopwatch.GetElapsedTime()));
	}

	bool HookStore::Disable(HookStep a_step) noexcept
	{
		const auto mapLock = std::scoped_lock(_mapMutex);

		REX::LogDebug("Disabling {} {} hooks"sv,
			_hookMap.size(), a_step);

		auto stopwatch = REX::Stopwatch::StartNew();

		auto hookCount = static_cast<REL::HookHandle>(0);
		for (auto& [_, hook] : _hookMap) {
			if (hook->GetStep() == a_step && hook->Disable()) {
				hookCount++;
			}
		}

		stopwatch.Stop();

		REX::LogDebug("Disabled {} {} hooks in {}"sv,
			hookCount, a_step, std::chrono::duration_cast<std::chrono::duration<REX::Float64, std::milli>>(stopwatch.GetElapsedTime()));

		return hookCount > 0;
	}

	REL::HookHandle HookStore::GetTrampolineSize() const noexcept
	{
		const auto mapLock = std::shared_lock(_mapMutex);

		auto totalSize = static_cast<REL::HookHandle>(0);
		for (const auto& [_, hook] : _hookMap) {
			totalSize += hook->GetTrampolineSize();
		}

		return totalSize;
	}

	auto GetHookStore()
		-> const REX::NotNull<std::unique_ptr<HookStore>>&
	{
		static const auto INSTANCE = REX::NotNull(std::make_unique<REL::HookStore>());
		return INSTANCE;
	}
}
