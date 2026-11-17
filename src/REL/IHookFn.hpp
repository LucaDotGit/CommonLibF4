#pragma once

#include "REL/IHook.hpp"
#include "REL/Id.hpp"
#include "REL/Memory.hpp"
#include "REL/Offset.hpp"
#include "REL/Relocation.hpp"
#include "REX/Casting.hpp"
#include "REX/Logging/ILogger.hpp"
#include "REX/Message.hpp"

namespace REL
{
	template <class T>
	class IHookFn : public REL::IHook
	{
	public:
		using value_type = std::decay_t<T>;

		static_assert(std::is_function_v<std::remove_pointer_t<T>>);

		explicit IHookFn() noexcept = default;

		explicit IHookFn(
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			REL::IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset), std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		explicit IHookFn(
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			REL::IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()), std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		explicit IHookFn(
			HookStep a_step,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			REL::IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset), a_step, std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		explicit IHookFn(
			HookStep a_step,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			REL::IHook(
				a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()),
				a_step,
				std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		explicit IHookFn(
			std::string a_name,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			REL::IHook(
				a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset),
				std::move(a_name),
				std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		explicit IHookFn(
			std::string a_name,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			REL::IHook(
				a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()),
				std::move(a_name),
				std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		explicit IHookFn(
			std::string a_name,
			HookStep a_step,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			REL::IHook(
				a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset),
				std::move(a_name),
				a_step,
				std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		explicit IHookFn(
			std::string a_name,
			HookStep a_step,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			REL::IHook(
				a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()),
				std::move(a_name),
				a_step,
				std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		~IHookFn() noexcept override = default;

		IHookFn(const IHookFn&) = delete;
		IHookFn(IHookFn&&) noexcept = default;

		auto operator=(const IHookFn&) -> IHookFn& = delete;
		auto operator=(IHookFn&&) noexcept -> IHookFn& = default;

		template <class... Args>
		auto operator()(Args&&... a_args) const //
			noexcept(std::is_nothrow_invocable_v<const value_type&, Args...>)
				-> std::invoke_result_t<const value_type&, Args...>
			requires(std::is_invocable_v<const value_type&, Args...>)
		{
			return _oldFunction.Invoke(std::forward<Args>(a_args)...);
		}

		[[nodiscard]]
		constexpr auto get() const //
			noexcept(noexcept(_oldFunction.get())) -> value_type
		{
			return _oldFunction.get();
		}

		auto Setup(REL::Trampoline& a_trampoline) -> bool override
		{
			if (GetIsSetup()) {
				return false;
			}

			if (GetAddress() == REL::INVALID_ADDRESS) [[unlikely]] {
				REX::Fail("{}: Address is null."sv, *this);
			}

			if (GetSize() == 0) [[unlikely]] {
				REX::Fail("{}: Size is empty."sv, *this);
			}

			_oldFunction = GetBranchAddress(GetAddress());

			if (_oldFunction.GetAddress() == REL::INVALID_ADDRESS) [[unlikely]] {
				REX::Fail("{}: Old function is null."sv, *this);
			}

			if (_newFunction.GetAddress() == REL::INVALID_ADDRESS) [[unlikely]] {
				REX::Fail("{}: New function is null."sv, *this);
			}

			if (!_oldBytes) {
				// NOLINTNEXTLINE(modernize-avoid-c-arrays)
				_oldBytes = std::make_unique_for_overwrite<std::uint8_t[]>(GetSize());
			}

			if (!_newBytes) {
				// NOLINTNEXTLINE(modernize-avoid-c-arrays)
				_newBytes = std::make_unique_for_overwrite<std::uint8_t[]>(GetSize());
			}

			REL::Write(std::span{_oldBytes.get(), GetSize()}, GetAddress());
			WriteBranch(
				std::span{_newBytes.get(), GetSize()},
				GetAddress(),
				AllocateBranch(a_trampoline, _newFunction.GetAddress()));

			SetIsSetup(true);

			if (GetLogger()) {
				GetLogger()->LogTrace("{}: Setup"sv, *this);
			}

			return true;
		}

		auto Enable() -> bool override
		{
			if (!CanBeEnabled()) {
				return false;
			}

			const auto writeResult = REL::WriteSafe(GetAddress(), std::span{_newBytes.get(), GetSize()});
			if (!writeResult.has_value()) [[unlikely]] {
				REX::Fail(
					"{}: Failed to write new bytes.\n"
					"System Error (0x{:08X}): {}"sv,
					*this,
					writeResult.error().value(),
					writeResult.error().message());
			}

			SetIsEnabled(true);

			if (GetLogger()) {
				GetLogger()->LogTrace("{}: Enabled"sv, *this);
			}

			return true;
		}

		auto Disable() -> bool override
		{
			if (!CanBeDisabled()) {
				return false;
			}

			const auto writeResult = REL::WriteSafe(GetAddress(), std::span{_oldBytes.get(), GetSize()});
			if (!writeResult.has_value()) [[unlikely]] {
				REX::Fail(
					"{}: Failed to write old bytes.\n"
					"System Error (0x{:08X}): {}"sv,
					*this,
					writeResult.error().value(),
					writeResult.error().message());
			}

			SetIsEnabled(false);

			if (GetLogger()) {
				GetLogger()->LogTrace("{}: Disabled"sv, *this);
			}

			return false;
		}

	protected:
		virtual auto GetBranchAddress(std::uintptr_t a_address) const noexcept -> std::uintptr_t = 0;
		virtual auto AllocateBranch(REL::Trampoline& a_trampoline, std::uintptr_t a_functionAddress)
			-> std::uintptr_t = 0;
		virtual void WriteBranch(
			std::span<std::uint8_t> a_targetBytes,
			std::uintptr_t a_targetAddress,
			std::uintptr_t a_functionAddress) noexcept = 0;

		REL::Relocation<value_type> _oldFunction;
		REL::Relocation<value_type> _newFunction;

		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<std::uint8_t[]> _oldBytes;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<std::uint8_t[]> _newBytes;
	};

	template <class T>
	IHookFn(const REL::IId&, std::ptrdiff_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> IHookFn<std::decay_t<T>>;

	template <class T>
	IHookFn(const REL::IId&, const REL::IOffset&, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> IHookFn<std::decay_t<T>>;

	template <class T>
	IHookFn(HookStep, const REL::IId&, std::ptrdiff_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> IHookFn<std::decay_t<T>>;

	template <class T>
	IHookFn(HookStep, const REL::IId&, const REL::IOffset&, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> IHookFn<std::decay_t<T>>;

	template <class T>
	IHookFn(std::string, const REL::IId&, std::ptrdiff_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> IHookFn<std::decay_t<T>>;

	template <class T>
	IHookFn(std::string, const REL::IId&, const REL::IOffset&, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> IHookFn<std::decay_t<T>>;

	template <class T>
	IHookFn(
		std::string,
		HookStep,
		const REL::IId&,
		std::ptrdiff_t,
		const T&,
		std::shared_ptr<REX::Logging::ILogger> = {}) -> IHookFn<std::decay_t<T>>;

	template <class T>
	IHookFn(
		std::string,
		HookStep,
		const REL::IId&,
		const REL::IOffset&,
		const T&,
		std::shared_ptr<REX::Logging::ILogger> = {}) -> IHookFn<std::decay_t<T>>;
}
