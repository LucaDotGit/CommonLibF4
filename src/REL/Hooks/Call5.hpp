#pragma once

#include "REL/ASM/Call5.hpp"
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
	class Call5 final : public REL::IHookFn<T>
	{
	public:
		using value_type = std::decay_t<T>;

		static_assert(std::is_function_v<std::remove_pointer_t<T>>);

		explicit Call5() noexcept = default;

		explicit Call5(
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		explicit Call5(
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		explicit Call5(
			HookStep a_step,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(a_step, a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		explicit Call5(
			HookStep a_step,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(a_step, a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		explicit Call5(
			std::string a_name,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(std::move(a_name), a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		explicit Call5(
			std::string a_name,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(std::move(a_name), a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		explicit Call5(
			std::string a_name,
			HookStep a_step,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(std::move(a_name), a_step, a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		explicit Call5(
			std::string a_name,
			HookStep a_step,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const value_type& a_newFunc,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHookFn<T>(std::move(a_name), a_step, a_id, a_offset, a_newFunc, std::move(a_logger))
		{
		}

		~Call5() noexcept override = default;

		Call5(const Call5&) = delete;
		Call5(Call5&&) noexcept = default;

		auto operator=(const Call5&) -> Call5& = delete;
		auto operator=(Call5&&) noexcept -> Call5& = default;

		[[nodiscard]]
		auto GetTypeName() const noexcept -> std::string_view override
		{
			return "Call5"sv;
		}

		[[nodiscard]]
		auto GetSize() const noexcept -> std::size_t override
		{
			return sizeof(REL::ASM::Call5);
		}

		[[nodiscard]]
		auto GetTrampolineSize() const noexcept -> std::size_t override
		{
			return sizeof(REL::Trampoline::Branch5MemoryType);
		}

	protected:
		[[nodiscard]]
		auto GetBranchAddress(std::uintptr_t a_address) const noexcept -> std::uintptr_t override
		{
			return REL::ASM::Call5::TARGET(a_address);
		}

		[[nodiscard]]
		auto AllocateBranch(REL::Trampoline& a_trampoline, std::uintptr_t a_functionAddress) -> std::uintptr_t override
		{
			return a_trampoline.AllocateBranch5(a_functionAddress);
		}

		void WriteBranch(
			std::span<std::uint8_t> a_targetBytes,
			std::uintptr_t a_targetAddress,
			std::uintptr_t a_functionAddress) noexcept override
		{
			const auto assembly = REL::ASM::Call5(a_targetAddress, a_functionAddress);
			REL::WriteData(a_targetBytes, assembly);
		}
	};

	template <class T>
	Call5(const REL::IId&, std::ptrdiff_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Call5<std::decay_t<T>>;

	template <class T>
	Call5(const REL::IId&, const REL::IOffset&, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Call5<std::decay_t<T>>;

	template <class T>
	Call5(HookStep, const REL::IId&, std::ptrdiff_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Call5<std::decay_t<T>>;

	template <class T>
	Call5(HookStep, const REL::IId&, const REL::IOffset&, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Call5<std::decay_t<T>>;

	template <class T>
	Call5(std::string, const REL::IId&, std::ptrdiff_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Call5<std::decay_t<T>>;

	template <class T>
	Call5(std::string, const REL::IId&, const REL::IOffset&, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Call5<std::decay_t<T>>;

	template <class T>
	Call5(std::string, HookStep, const REL::IId&, std::ptrdiff_t, const T&, std::shared_ptr<REX::Logging::ILogger> = {})
		-> Call5<std::decay_t<T>>;

	template <class T>
	Call5(
		std::string,
		HookStep,
		const REL::IId&,
		const REL::IOffset&,
		const T&,
		std::shared_ptr<REX::Logging::ILogger> = {}) -> Call5<std::decay_t<T>>;
}
