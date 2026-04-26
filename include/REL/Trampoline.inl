#pragma once

#include "REL/Trampoline.hpp"

#include "REL/Cast.hpp"

namespace REL
{
	template <class T, class... Args>
	[[nodiscard]] T* Trampoline::Allocate(Args&&... a_args) noexcept
		requires(std::is_constructible_v<T, Args...>)
	{
		auto* mem = Allocate(sizeof(T));
		if (!mem) {
			return nullptr;
		}

		return std::construct_at(reinterpret_cast<T*>(mem), std::forward<Args>(a_args)...);
	}

	template <std::size_t N>
	std::uintptr_t Trampoline::WriteCall(std::uintptr_t a_source, std::uintptr_t a_target) noexcept
		requires(Impl::valid_jump_size<N>)
	{
		if constexpr (N == sizeof(REL::Asm::Call5)) {
			return WriteCall5(a_source, a_target);
		}
		else if constexpr (N == sizeof(REL::Asm::Call6)) {
			return WriteCall6(a_source, a_target);
		}
		else {
			static_assert(false, "The call size is invalid.");
		}
	}

	template <std::size_t N, class F>
	std::uintptr_t Trampoline::WriteCall(std::uintptr_t a_source, const F& a_target) noexcept
		requires(Impl::valid_jump_size<N> &&
				 std::is_function_v<F>)
	{
		return WriteCall<N>(a_source, REL::UnrestrictedCast<std::uintptr_t>(a_target));
	}

	template <std::size_t N>
	std::uintptr_t Trampoline::WriteJump(std::uintptr_t a_source, std::uintptr_t a_target) noexcept
		requires(Impl::valid_jump_size<N>)
	{
		if constexpr (N == sizeof(REL::Asm::Jump5)) {
			return WriteJump5(a_source, a_target);
		}
		else if constexpr (N == sizeof(REL::Asm::Jump6)) {
			return WriteJump6(a_source, a_target);
		}
		else {
			static_assert(false, "The jump size is invalid.");
		}
	}

	template <std::size_t N, class F>
	std::uintptr_t Trampoline::WriteJump(std::uintptr_t a_source, const F& a_target) noexcept
		requires(Impl::valid_jump_size<N> &&
				 std::is_function_v<F>)
	{
		return WriteJump<N>(a_source, REL::UnrestrictedCast<std::uintptr_t>(a_target));
	}
}
