#pragma once

#include "REL/Cast.hpp"
#include "REL/IHook.hpp"
#include "REL/Id.hpp"
#include "REL/Memory.hpp"
#include "REL/Offset.hpp"
#include "REL/Relocation.hpp"

#include "REX/ErrorCode.hpp"
#include "REX/Log.hpp"
#include "REX/Message.hpp"

namespace REL
{
	template <class T>
	class IHookFn
		: public IHook
	{
	public:
		using value_type = std::decay_t<T>;

		static_assert(std::is_function_v<std::remove_pointer_t<T>>);

		IHookFn() = default;

		IHookFn(const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + a_offset),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		IHookFn(const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + a_offset.GetOffset()),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		IHookFn(HookStep a_step, const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + a_offset, a_step),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		IHookFn(HookStep a_step, const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + a_offset.GetOffset(), a_step),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		IHookFn(std::string a_name, const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + a_offset, std::move(a_name)),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		IHookFn(std::string a_name, const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + a_offset.GetOffset(), std::move(a_name)),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		IHookFn(std::string a_name, HookStep a_step, const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + a_offset, std::move(a_name), a_step),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		IHookFn(std::string a_name, HookStep a_step, const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHook(a_id.GetAddress() + a_offset.GetOffset(), std::move(a_name), a_step),
			  _newFunc(REL::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		~IHookFn() noexcept override = default;

		IHookFn(const IHookFn&) = delete;
		IHookFn(IHookFn&&) noexcept = default;

		IHookFn& operator=(const IHookFn&) = delete;
		IHookFn& operator=(IHookFn&&) noexcept = default;

		template <class... Args>
		auto operator()(Args&&... a_args) const //
			noexcept(std::is_nothrow_invocable_v<const value_type&, Args...>)
				-> std::invoke_result_t<const value_type&, Args...>
			requires(std::is_invocable_v<const value_type&, Args...>)
		{
			return _newFunc.Invoke(std::forward<Args>(a_args)...);
		}

		[[nodiscard]] constexpr value_type get() const //
			noexcept(noexcept(_newFunc.get()))
		{
			return _newFunc.get();
		}

		bool Init() override
		{
			if (IsInitialized()) {
				return false;
			}

			if (_address == REL::INVALID_ADDRESS) [[unlikely]] {
				REX::Fail("{}: Address is null."sv,
					*this);
			}

			if (_size == REL::INVALID_SIZE) [[unlikely]] {
				REX::Fail("{}: Size is empty."sv,
					*this);
			}

			if (_oldFunc.GetAddress() == REL::INVALID_ADDRESS) [[unlikely]] {
				REX::Fail("{}: Old function is null."sv,
					*this);
			}

			if (_newFunc.GetAddress() == REL::INVALID_ADDRESS) [[unlikely]] {
				REX::Fail("{}: New function is null."sv,
					*this);
			}

			_oldBytes.resize(_size);
			_newBytes.resize(_size);

			REL::Write(std::span(_oldBytes), _address);

			InitNewBytes();

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

			const auto writeError = REL::WriteSafe(_address, std::span(_newBytes));
			if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				REX::Fail(
					"{}: Failed to write new bytes.\n"
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

			const auto writeError = REL::WriteSafe(_address, std::span(_oldBytes));
			if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				REX::Fail(
					"{}: Failed to write old bytes.\n"
					"System Error (0x{:08X}): {}"sv,
					*this, writeError.value(), writeError.message());
			}

			_enabled = false;

			REX::LogTrace("{}: Disabled"sv,
				*this);

			return false;
		}

	protected:
		virtual void InitNewBytes() = 0;

		REL::Relocation<value_type> _oldFunc;
		REL::Relocation<value_type> _newFunc;

		std::vector<std::uint8_t> _oldBytes;
		std::vector<std::uint8_t> _newBytes;
	};

	template <class T>
	IHookFn(const REL::IId&, std::ptrdiff_t, const T&) -> IHookFn<std::decay_t<T>>;

	template <class T>
	IHookFn(const REL::IId&, const REL::IOffset&, const T&) -> IHookFn<std::decay_t<T>>;

	template <class T>
	IHookFn(HookStep, const REL::IId&, std::ptrdiff_t, const T&) -> IHookFn<std::decay_t<T>>;

	template <class T>
	IHookFn(HookStep, const REL::IId&, const REL::IOffset&, const T&) -> IHookFn<std::decay_t<T>>;

	template <class T>
	IHookFn(std::string, const REL::IId&, std::ptrdiff_t, const T&) -> IHookFn<std::decay_t<T>>;

	template <class T>
	IHookFn(std::string, const REL::IId&, const REL::IOffset&, const T&) -> IHookFn<std::decay_t<T>>;

	template <class T>
	IHookFn(std::string, HookStep, const REL::IId&, std::ptrdiff_t, const T&) -> IHookFn<std::decay_t<T>>;

	template <class T>
	IHookFn(std::string, HookStep, const REL::IId&, const REL::IOffset&, const T&) -> IHookFn<std::decay_t<T>>;
}
