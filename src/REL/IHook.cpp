#include "REL/IHook.hpp"

#include "REL/Memory.hpp"
#include "REX/Formatting.hpp"

namespace REL::Impl
{
	namespace
	{
		constexpr auto DEFAULT_HOOK_NAME = "Hook"sv;
		constexpr auto INVALID_HOOK_NAME = "<Invalid Hook>"sv;

		[[nodiscard]]
		auto CreateHookHandle() noexcept -> HookHandle
		{
			static constinit auto HookHandleCount = std::atomic<HookHandle>(0);
			return HookHandleCount.fetch_add(1, std::memory_order_acq_rel) + 1;
		}
	}
}

namespace REL
{
	IHook::IHook() noexcept :
		_handle(INVALID_HOOK_HANDLE),
		_address(REL::INVALID_ADDRESS),
		_name(Impl::INVALID_HOOK_NAME)
	{
	}

	IHook::IHook(std::uintptr_t a_address, std::shared_ptr<REX::Logging::ILogger> a_logger) noexcept :
		_handle(Impl::CreateHookHandle()),
		_address(a_address),
		_name(Impl::DEFAULT_HOOK_NAME),
		_logger(std::move(a_logger))
	{
	}

	IHook::IHook(std::uintptr_t a_address, HookStep a_step, std::shared_ptr<REX::Logging::ILogger> a_logger) noexcept :
		_handle(Impl::CreateHookHandle()),
		_address(a_address),
		_name(Impl::DEFAULT_HOOK_NAME),
		_step(a_step),
		_logger(std::move(a_logger))
	{
	}

	IHook::IHook(std::uintptr_t a_address, std::string a_name, std::shared_ptr<REX::Logging::ILogger> a_logger) noexcept
		:
		_handle(Impl::CreateHookHandle()),
		_address(a_address),
		_name(std::move(a_name)),
		_logger(std::move(a_logger))
	{
	}

	IHook::IHook(
		std::uintptr_t a_address,
		std::string a_name,
		HookStep a_step,
		std::shared_ptr<REX::Logging::ILogger> a_logger) noexcept :
		_handle(Impl::CreateHookHandle()),
		_address(a_address),
		_name(std::move(a_name)),
		_step(a_step),
		_logger(std::move(a_logger))
	{
	}

	IHook::~IHook() noexcept = default;

	auto IHook::operator==(const IHook& a_rhs) const noexcept -> bool
	{
		return GetHandle() == a_rhs.GetHandle();
	}

	auto IHook::operator<=>(const IHook& a_rhs) const noexcept
	{
		return GetHandle() <=> a_rhs.GetHandle();
	}

	IHook::operator bool() const noexcept
	{
		return GetAddress() != REL::INVALID_ADDRESS;
	}

	auto IHook::Setup([[maybe_unused]] REL::Trampoline& a_trampoline) -> bool
	{
		if (GetIsSetup()) {
			return false;
		}

		SetIsSetup(true);
		return true;
	}

	auto IHook::ToString() const -> std::string
	{
		return REX::Format("[{}::{} ({})]"sv, GetTypeName(), GetName(), GetHandle());
	}
}
