#pragma once

#include "REL/IHook.hpp"
#include "REL/Id.hpp"
#include "REL/Memory.hpp"
#include "REL/Relocation.hpp"
#include "REL/Size.hpp"
#include "REX/Casting.hpp"
#include "REX/Logging/ILogger.hpp"
#include "REX/Message.hpp"

namespace REL::Hooks
{
	template <class T>
	class Vft final : public REL::IHook
	{
	public:
		using value_type = std::decay_t<T>;

		static_assert(std::is_function_v<std::remove_pointer_t<T>>);

		explicit Vft() noexcept = default;

		explicit Vft(
			const REL::IId& a_id,
			std::size_t a_index,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index), std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		explicit Vft(
			const REL::IId& a_id,
			const REL::ISize& a_index,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index.GetSize()), std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		explicit Vft(
			HookStep a_step,
			const REL::IId& a_id,
			std::size_t a_index,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index), a_step, std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		explicit Vft(
			HookStep a_step,
			const REL::IId& a_id,
			const REL::ISize& a_index,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index.GetSize()), a_step, std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		explicit Vft(
			std::string a_name,
			const REL::IId& a_id,
			std::size_t a_index,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index), std::move(a_name), std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		explicit Vft(
			std::string a_name,
			const REL::IId& a_id,
			const REL::ISize& a_index,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(
				a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index.GetSize()),
				std::move(a_name),
				std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		explicit Vft(
			std::string a_name,
			HookStep a_step,
			const REL::IId& a_id,
			std::size_t a_index,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(
				a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index),
				std::move(a_name),
				a_step,
				std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		explicit Vft(
			std::string a_name,
			HookStep a_step,
			const REL::IId& a_id,
			const REL::ISize& a_index,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(
				a_id.GetAddress() + (sizeof(std::uintptr_t) * a_index.GetSize()),
				std::move(a_name),
				a_step,
				std::move(a_logger)),
			_newFunction(REX::UnrestrictedCast<std::uintptr_t>(a_newFunc))
		{
		}

		~Vft() noexcept override = default;

		Vft(const Vft&) = delete;
		Vft(Vft&&) noexcept = default;

		auto operator=(const Vft&) -> Vft& = delete;
		auto operator=(Vft&&) noexcept -> Vft& = default;

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

		[[nodiscard]]
		auto GetTypeName() const noexcept -> std::string_view override
		{
			return "Vft"sv;
		}

		[[nodiscard]]
		auto GetSize() const noexcept -> std::size_t override
		{
			return sizeof(std::uintptr_t);
		}

		[[nodiscard]]
		auto GetTrampolineSize() const noexcept -> std::size_t override
		{
			return 0;
		}

		auto Setup([[maybe_unused]] REL::Trampoline& a_trampoline) -> bool override
		{
			if (GetIsSetup()) {
				return false;
			}

			if (GetAddress() == REL::INVALID_ADDRESS) [[unlikely]] {
				REX::Fail("{}: Address is null."sv, *this);
			}

			if (_newFunction.GetAddress() == REL::INVALID_ADDRESS) [[unlikely]] {
				REX::Fail("{}: New function is null."sv, *this);
			}

			_oldFunction = *std::bit_cast<std::uintptr_t*>(GetAddress());

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

			const auto writeResult = REL::WriteSafeData(GetAddress(), _newFunction.GetAddress());
			if (!writeResult.has_value()) [[unlikely]] {
				REX::Fail(
					"{}: Failed to write new function.\n"
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

			const auto writeResult = REL::WriteSafeData(GetAddress(), _oldFunction.GetAddress());
			if (!writeResult.has_value()) [[unlikely]] {
				REX::Fail(
					"{}: Failed to write old function.\n"
					"System Error (0x{:08X}): {}"sv,
					*this,
					writeResult.error().value(),
					writeResult.error().message());
			}

			SetIsEnabled(false);

			if (GetLogger()) {
				GetLogger()->LogTrace("{}: Disabled"sv, *this);
			}

			return true;
		}

	private:
		REL::Relocation<value_type> _oldFunction;
		REL::Relocation<value_type> _newFunction;
	};

	template <class T>
	Vft(const REL::IId&, std::size_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {}) -> Vft<std::decay_t<T>>;

	template <class T>
	Vft(const REL::IId&, const REL::ISize&, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Vft<std::decay_t<T>>;

	template <class T>
	Vft(HookStep, const REL::IId&, std::size_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Vft<std::decay_t<T>>;

	template <class T>
	Vft(HookStep, const REL::IId&, const REL::ISize&, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Vft<std::decay_t<T>>;

	template <class T>
	Vft(std::string, const REL::IId&, std::size_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Vft<std::decay_t<T>>;

	template <class T>
	Vft(std::string, const REL::IId&, const REL::ISize&, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Vft<std::decay_t<T>>;

	template <class T>
	Vft(std::string, HookStep, const REL::IId&, std::size_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Vft<std::decay_t<T>>;

	template <class T>
	Vft(std::string,
		HookStep,
		const REL::IId&,
		const REL::ISize&,
		const T&,
		std::shared_ptr<REX::Logging::ILogger> = {}) -> Vft<std::decay_t<T>>;
}
