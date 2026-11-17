#include "REL/HookList.hpp"

#include "REL/IHook.hpp"
#include "REX/Logging/ILogger.hpp"
#include "REX/NotNull.hpp"
#include "REX/Stopwatch.hpp"

namespace REL
{
	HookList::HookList() noexcept = default;

	HookList::HookList(std::shared_ptr<REX::Logging::ILogger> a_logger) noexcept :
		_logger(std::move(a_logger))
	{
	}

	HookList::~HookList() noexcept = default;

	auto HookList::Contains(const REX::NotNull<std::shared_ptr<REL::IHook>>& a_key) const noexcept -> bool
	{
		const auto hookHandle = a_key->GetHandle();
		if (hookHandle == REL::INVALID_HOOK_HANDLE) {
			return false;
		}

		const auto hookLock = std::shared_lock(_hookMutex);
		return _hookMap.contains(hookHandle);
	}

	auto HookList::GetValue(const REX::NotNull<std::shared_ptr<REL::IHook>>& a_key) const noexcept
		-> std::shared_ptr<REL::IHook>
	{
		const auto hookHandle = a_key->GetHandle();
		if (hookHandle == REL::INVALID_HOOK_HANDLE) {
			return nullptr;
		}

		const auto hookLock = std::shared_lock(_hookMutex);

		const auto hookIt = _hookMap.find(hookHandle);
		if (hookIt == _hookMap.end()) {
			return nullptr;
		}

		return hookIt->second.get();
	}

	auto HookList::Add(REX::NotNull<std::shared_ptr<REL::IHook>> a_key) -> bool
	{
		const auto hookHandle = a_key->GetHandle();
		if (hookHandle == REL::INVALID_HOOK_HANDLE) {
			return false;
		}

		const auto hookLock = std::scoped_lock(_hookMutex);

		const auto&& [_, hasInserted] = _hookMap.emplace(hookHandle, std::move(a_key));
		return hasInserted;
	}

	auto HookList::Remove(const REX::NotNull<std::shared_ptr<REL::IHook>>& a_key) noexcept -> bool
	{
		const auto hookHandle = a_key->GetHandle();
		if (hookHandle == REL::INVALID_HOOK_HANDLE) {
			return false;
		}

		const auto hookLock = std::scoped_lock(_hookMutex);

		const auto hookIt = _hookMap.find(hookHandle);
		if (hookIt == _hookMap.end()) {
			return false;
		}

		_hookMap.erase(hookIt);
		return true;
	}

	void HookList::Clear() noexcept
	{
		const auto hookLock = std::scoped_lock(_hookMutex);
		_hookMap.clear();
	}

	void HookList::Setup(REL::Trampoline& a_trampoline)
	{
		const auto hookLock = std::scoped_lock(_hookMutex);

		if (_logger) {
			_logger->LogDebug("Setting up {} hooks"sv, _hookMap.size());
		}

		auto stopwatch = REX::Stopwatch::StartNew();

		auto hookCount = static_cast<std::size_t>(0);
		for (auto&& [_, hook] : _hookMap) {
			if (hook->Setup(a_trampoline)) {
				hookCount++;
			}
		}

		stopwatch.Stop();

		if (_logger) {
			_logger->LogDebug(
				"Setup {} hooks in {}"sv,
				hookCount,
				std::chrono::duration_cast<std::chrono::duration<REX::Float64, std::milli>>(
					stopwatch.GetElapsedTime()));
		}
	}

	void HookList::Enable()
	{
		const auto hookLock = std::scoped_lock(_hookMutex);

		if (_logger) {
			_logger->LogDebug("Enabling {} hooks"sv, _hookMap.size());
		}

		auto stopwatch = REX::Stopwatch::StartNew();

		auto hookCount = static_cast<std::size_t>(0);
		for (auto&& [_, hook] : _hookMap) {
			if (hook->Enable()) {
				hookCount++;
			}
		}

		stopwatch.Stop();

		if (_logger) {
			_logger->LogDebug(
				"Enabled {} hooks in {}"sv,
				hookCount,
				std::chrono::duration_cast<std::chrono::duration<REX::Float64, std::milli>>(
					stopwatch.GetElapsedTime()));
		}
	}

	auto HookList::Enable(HookStep a_step) -> bool
	{
		const auto hookLock = std::scoped_lock(_hookMutex);

		if (_logger) {
			_logger->LogDebug("Enabling {} {} hooks"sv, _hookMap.size(), a_step);
		}

		auto stopwatch = REX::Stopwatch::StartNew();

		auto hookCount = static_cast<std::size_t>(0);
		for (auto&& [_, hook] : _hookMap) {
			if (hook->GetStep() == a_step && hook->Enable()) {
				hookCount++;
			}
		}

		stopwatch.Stop();

		if (_logger) {
			_logger->LogDebug(
				"Enabled {} {} hooks in {}"sv,
				hookCount,
				a_step,
				std::chrono::duration_cast<std::chrono::duration<REX::Float64, std::milli>>(
					stopwatch.GetElapsedTime()));
		}

		return hookCount > 0;
	}

	void HookList::Disable()
	{
		const auto hookLock = std::scoped_lock(_hookMutex);

		if (_logger) {
			_logger->LogDebug("Disabling {} hooks"sv, _hookMap.size());
		}

		auto stopwatch = REX::Stopwatch::StartNew();

		auto hookCount = static_cast<std::size_t>(0);
		for (auto&& [_, hook] : _hookMap) {
			if (hook->Disable()) {
				hookCount++;
			}
		}

		stopwatch.Stop();

		if (_logger) {
			_logger->LogDebug(
				"Disabled {} hooks in {}"sv,
				hookCount,
				std::chrono::duration_cast<std::chrono::duration<REX::Float64, std::milli>>(
					stopwatch.GetElapsedTime()));
		}
	}

	auto HookList::Disable(HookStep a_step) -> bool
	{
		const auto hookLock = std::scoped_lock(_hookMutex);

		if (_logger) {
			_logger->LogDebug("Disabling {} {} hooks"sv, _hookMap.size(), a_step);
		}

		auto stopwatch = REX::Stopwatch::StartNew();

		auto hookCount = static_cast<std::size_t>(0);
		for (auto&& [_, hook] : _hookMap) {
			if (hook->GetStep() == a_step && hook->Disable()) {
				hookCount++;
			}
		}

		stopwatch.Stop();

		if (_logger) {
			_logger->LogDebug(
				"Disabled {} {} hooks in {}"sv,
				hookCount,
				a_step,
				std::chrono::duration_cast<std::chrono::duration<REX::Float64, std::milli>>(
					stopwatch.GetElapsedTime()));
		}

		return hookCount > 0;
	}

	auto HookList::GetTrampolineSize() const noexcept -> std::size_t
	{
		const auto hookLock = std::shared_lock(_hookMutex);

		auto totalSize = static_cast<std::size_t>(0);
		for (auto&& [_, hook] : _hookMap) {
			totalSize += hook->GetTrampolineSize();
		}

		return totalSize;
	}
}
