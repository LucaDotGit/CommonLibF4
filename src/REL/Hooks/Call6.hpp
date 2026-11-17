#pragma once

#include "REL/ASM/Call6.hpp"
#include "REL/IHookFn.hpp"
#include "REL/Trampoline.hpp"

namespace REL
{
	enum class HookStep : std::int32_t;

	class IId;
	class IOffset;
}

namespace REL::Hooks
{
	template <class T>
	class Call6 final : public REL::IHookFn<T>
	{
	public:
		using value_type = std::decay_t<T>;

		static_assert(std::is_function_v<std::remove_pointer_t<T>>);

		explicit Call6() noexcept = default;

		explicit Call6(
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		explicit Call6(
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		explicit Call6(
			HookStep a_step,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(a_step, a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		explicit Call6(
			HookStep a_step,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(a_step, a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		explicit Call6(
			std::string a_name,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(std::move(a_name), a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		explicit Call6(
			std::string a_name,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(std::move(a_name), a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		explicit Call6(
			std::string a_name,
			HookStep a_step,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(std::move(a_name), a_step, a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		explicit Call6(
			std::string a_name,
			HookStep a_step,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(std::move(a_name), a_step, a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		~Call6() noexcept override = default;

		Call6(const Call6&) = delete;
		Call6(Call6&&) noexcept = default;

		auto operator=(const Call6&) -> Call6& = delete;
		auto operator=(Call6&&) noexcept -> Call6& = default;

		[[nodiscard]]
		auto GetTypeName() const noexcept -> std::string_view override
		{
			return "Call6"sv;
		}

		[[nodiscard]]
		auto GetSize() const noexcept -> std::size_t override
		{
			return sizeof(REL::ASM::Call6);
		}

		[[nodiscard]]
		auto GetTrampolineSize() const noexcept -> std::size_t override
		{
			return sizeof(REL::Trampoline::Branch6MemoryType);
		}

	protected:
		[[nodiscard]]
		auto GetBranchAddress(std::uintptr_t a_address) const noexcept -> std::uintptr_t override
		{
			return REL::ASM::Call6::TARGET(a_address);
		}

		[[nodiscard]]
		auto AllocateBranch(REL::Trampoline& a_trampoline, std::uintptr_t a_functionAddress) -> std::uintptr_t override
		{
			return a_trampoline.AllocateBranch6(a_functionAddress);
		}

		void WriteBranch(
			std::span<std::uint8_t> a_targetBytes,
			std::uintptr_t a_targetAddress,
			std::uintptr_t a_functionAddress) noexcept override
		{
			const auto assembly = REL::ASM::Call6(a_targetAddress, a_functionAddress);
			REL::WriteData(a_targetBytes, assembly);
		}
	};

	template <class T>
	Call6(const REL::IId&, std::ptrdiff_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Call6<std::decay_t<T>>;

	template <class T>
	Call6(const REL::IId&, const REL::IOffset&, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Call6<std::decay_t<T>>;

	template <class T>
	Call6(HookStep, const REL::IId&, std::ptrdiff_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Call6<std::decay_t<T>>;

	template <class T>
	Call6(HookStep, const REL::IId&, const REL::IOffset&, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Call6<std::decay_t<T>>;

	template <class T>
	Call6(std::string, const REL::IId&, std::ptrdiff_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Call6<std::decay_t<T>>;

	template <class T>
	Call6(std::string, const REL::IId&, const REL::IOffset&, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Call6<std::decay_t<T>>;

	template <class T>
	Call6(std::string, HookStep, const REL::IId&, std::ptrdiff_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Call6<std::decay_t<T>>;

	template <class T>
	Call6(
		std::string,
		HookStep,
		const REL::IId&,
		const REL::IOffset&,
		const T&,
		std::shared_ptr<REX::Logging::ILogger> = {}) -> Call6<std::decay_t<T>>;
}
