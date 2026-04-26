#include "REL/IHook.hpp"

#include "REL/Memory.hpp"

#include "REX/Format.hpp"

namespace REL
{
	IHook::IHook()
		: _handle(INVALID_HOOK_HANDLE),
		  _address(REL::INVALID_ADDRESS),
		  _name(INVALID_HOOK_NAME)
	{
	}

	IHook::IHook(std::uintptr_t a_address)
		: _handle(CreateHookHandle()),
		  _address(a_address),
		  _name(DEFAULT_HOOK_NAME)
	{
	}

	IHook::IHook(std::uintptr_t a_address, std::string a_name)
		: _handle(CreateHookHandle()),
		  _address(a_address),
		  _name(std::move(a_name))
	{
	}

	IHook::IHook(std::uintptr_t a_address, HookStep a_step)
		: _handle(CreateHookHandle()),
		  _address(a_address),
		  _name(DEFAULT_HOOK_NAME),
		  _step(a_step)
	{
	}

	IHook::IHook(std::uintptr_t a_address, std::string a_name, HookStep a_step)
		: _handle(CreateHookHandle()),
		  _address(a_address),
		  _name(std::move(a_name)),
		  _step(a_step)
	{
	}

	IHook::~IHook() noexcept = default;

	bool IHook::operator==(const IHook& a_rhs) const noexcept
	{
		return _handle == a_rhs._handle;
	}

	bool IHook::operator!=(const IHook& a_rhs) const noexcept
	{
		return !(*this == a_rhs);
	}

	auto IHook::operator<=>(const IHook& a_rhs) const noexcept
	{
		return _handle <=> a_rhs._handle;
	}

	IHook::operator bool() const noexcept
	{
		return _address != REL::INVALID_ADDRESS;
	}

	bool IHook::Init()
	{
		if (_initialized) {
			return false;
		}

		_initialized = true;
		return true;
	}

	HookHandle IHook::CreateHookHandle() noexcept
	{
		return HookHandleCount.fetch_add(1, std::memory_order_acq_rel) + 1;
	}

	std::string IHook::ToString() const
	{
		return REX::Format("[{}::{} ({})]"sv, GetTypeName(), GetName(), GetHandle());
	}
}
