#pragma once

#include "REL/Cast.hpp"
#include "REL/IHook.hpp"
#include "REL/Id.hpp"
#include "REL/Memory.hpp"
#include "REL/Relocation.hpp"
#include "REL/Size.hpp"

#include "REX/Log.hpp"
#include "REX/Message.hpp"

namespace REL
{
	template <class T>
	class HookVft final
		: public IHook
	{
	public:
		using value_type = std::decay_t<T>;

		static_assert(std::is_function_v<std::remove_pointer_t<T>>);

		HookVft() = default;

		HookVft(const REL::IId& a_id, std::size_t a_index, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index)),
			  _oldFunc(*std::bit_cast<std::uintptr_t*>(_address)),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		HookVft(const REL::IId& a_id, const REL::ISize& a_index, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index.GetSize())),
			  _oldFunc(*std::bit_cast<std::uintptr_t*>(_address)),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		HookVft(HookStep a_step, const REL::IId& a_id, std::size_t a_index, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index), a_step),
			  _oldFunc(*std::bit_cast<std::uintptr_t*>(_address)),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		HookVft(HookStep a_step, const REL::IId& a_id, const REL::ISize& a_index, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index.GetSize()), a_step),
			  _oldFunc(*std::bit_cast<std::uintptr_t*>(_address)),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		HookVft(std::string a_name, const REL::IId& a_id, std::size_t a_index, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index), std::move(a_name)),
			  _oldFunc(*std::bit_cast<std::uintptr_t*>(_address)),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		HookVft(std::string a_name, const REL::IId& a_id, const REL::ISize& a_index, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index.GetSize()), std::move(a_name)),
			  _oldFunc(*std::bit_cast<std::uintptr_t*>(_address)),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		HookVft(std::string a_name, HookStep a_step, const REL::IId& a_id, std::size_t a_index, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index), std::move(a_name), a_step),
			  _oldFunc(*std::bit_cast<std::uintptr_t*>(_address)),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		HookVft(std::string a_name, HookStep a_step, const REL::IId& a_id, const REL::ISize& a_index, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index.GetSize()), std::move(a_name), a_step),
			  _oldFunc(*std::bit_cast<std::uintptr_t*>(_address)),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		~HookVft() noexcept override = default;

		HookVft(const HookVft&) = delete;
		HookVft(HookVft&&) noexcept = default;

		HookVft& operator=(const HookVft&) = delete;
		HookVft& operator=(HookVft&&) noexcept = default;

		template <class... Args>
		auto operator()(Args&&... a_args) const //
			noexcept(std::is_nothrow_invocable_v<const value_type&, Args...>)
				-> std::invoke_result_t<const value_type&, Args...>
			requires(std::is_invocable_v<const value_type&, Args...>)
		{
			return _oldFunc.Invoke(std::forward<Args>(a_args)...);
		}

		[[nodiscard]] constexpr value_type get() const //
			noexcept(noexcept(_oldFunc.get()))
		{
			return _oldFunc.get();
		}

		[[nodiscard]] std::string_view GetTypeName() const noexcept override { return "Vft"sv; }

		bool Init() override
		{
			if (IsInitialized()) {
				return false;
			}

			if (_address == REL::INVALID_ADDRESS) [[unlikely]] {
				REX::Fail("{}: Address is null."sv,
					*this);
			}

			if (_newFunc.GetAddress() == REL::INVALID_ADDRESS) [[unlikely]] {
				REX::Fail("{}: New function is null."sv,
					*this);
			}

			_initialized = true;

			REX::LogTrace("{}: Init"sv,
				*this);

			return true;
		}

		bool Enable() override
		{
			if (!CanBeEnabled()) {
				return false;
			}

			const auto writeError = REL::WriteSafeData(_address, _newFunc.GetAddress());
			if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				REX::Fail(
					"{}: Failed to write new function.\n"
					"System Error (0x{:08X}): {}"sv,
					*this, writeError.value(), writeError.message());
			}

			_enabled = true;

			REX::LogTrace("{}: Enabled"sv,
				*this);

			return true;
		}

		bool Disable() override
		{
			if (!CanBeDisabled()) {
				return false;
			}

			const auto writeError = REL::WriteSafeData(_address, _oldFunc.GetAddress());
			if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				REX::Fail(
					"{}: Failed to write old function.\n"
					"System Error (0x{:08X}): {}"sv,
					*this, writeError.value(), writeError.message());
			}

			_enabled = false;

			REX::LogTrace("{}: Disabled"sv,
				*this);

			return true;
		}

	private:
		REL::Relocation<value_type> _oldFunc{ REL::INVALID_ADDRESS };
		REL::Relocation<value_type> _newFunc{ REL::INVALID_ADDRESS };
	};

	template <class T>
	HookVft(const REL::IId&, std::size_t, const T&) -> HookVft<std::decay_t<T>>;

	template <class T>
	HookVft(const REL::IId&, const REL::ISize&, const T&) -> HookVft<std::decay_t<T>>;

	template <class T>
	HookVft(HookStep, const REL::IId&, std::size_t, const T&) -> HookVft<std::decay_t<T>>;

	template <class T>
	HookVft(HookStep, const REL::IId&, const REL::ISize&, const T&) -> HookVft<std::decay_t<T>>;

	template <class T>
	HookVft(std::string, const REL::IId&, std::size_t, const T&) -> HookVft<std::decay_t<T>>;

	template <class T>
	HookVft(std::string, const REL::IId&, const REL::ISize&, const T&) -> HookVft<std::decay_t<T>>;

	template <class T>
	HookVft(std::string, HookStep, const REL::IId&, std::size_t, const T&) -> HookVft<std::decay_t<T>>;

	template <class T>
	HookVft(std::string, HookStep, const REL::IId&, const REL::ISize&, const T&) -> HookVft<std::decay_t<T>>;
}
