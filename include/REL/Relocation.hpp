#pragma once

#include "REL/Asm.hpp"
#include "REL/Cast.hpp"
#include "REL/Id.hpp"
#include "REL/Memory.hpp"
#include "REL/Module.hpp"
#include "REL/Offset.hpp"
#include "REL/Size.hpp"
#include "REL/Trampoline.hpp"

#include "REX/Concepts.hpp"
#include "REX/Contract.hpp"
#include "REX/Error.hpp"
#include "REX/Message.hpp"

#define REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER_IMPL(a_nopropQual, a_propQual, ...)              \
	template <class R, class Cls, class... Args>                                                  \
	struct member_function_pod_type<R (Cls::*)(Args...) __VA_ARGS__ a_nopropQual a_propQual>      \
	{                                                                                             \
		using type = R(__VA_ARGS__ Cls*, Args...) a_propQual;                                     \
	};                                                                                            \
                                                                                                  \
	template <class R, class Cls, class... Args>                                                  \
	struct member_function_pod_type<R (Cls::*)(Args..., ...) __VA_ARGS__ a_nopropQual a_propQual> \
	{                                                                                             \
		using type = R(__VA_ARGS__ Cls*, Args..., ...) a_propQual;                                \
	};

#define REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER(a_qualifier, ...)              \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER_IMPL(a_qualifier, , ##__VA_ARGS__) \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER_IMPL(a_qualifier, noexcept, ##__VA_ARGS__)

#define REL_MAKE_MEMBER_FUNCTION_POD_TYPE(...)                 \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER(, __VA_ARGS__)    \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER(&, ##__VA_ARGS__) \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER(&&, ##__VA_ARGS__)

#define REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER_IMPL(a_nopropQual, a_propQual, ...)              \
	template <class R, class Cls, class... Args>                                                      \
	struct member_function_non_pod_type<R (Cls::*)(Args...) __VA_ARGS__ a_nopropQual a_propQual>      \
	{                                                                                                 \
		using type = R&(__VA_ARGS__ Cls*, void*, Args...)a_propQual;                                  \
	};                                                                                                \
                                                                                                      \
	template <class R, class Cls, class... Args>                                                      \
	struct member_function_non_pod_type<R (Cls::*)(Args..., ...) __VA_ARGS__ a_nopropQual a_propQual> \
	{                                                                                                 \
		using type = R&(__VA_ARGS__ Cls*, void*, Args..., ...)a_propQual;                             \
	};

#define REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER(a_qualifier, ...)              \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER_IMPL(a_qualifier, , ##__VA_ARGS__) \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER_IMPL(a_qualifier, noexcept, ##__VA_ARGS__)

#define REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE(...)                 \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER(, __VA_ARGS__)    \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER(&, ##__VA_ARGS__) \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER(&&, ##__VA_ARGS__)

namespace REL
{
	template <class>
	class Relocation;
}

namespace REL::Impl
{
	template <class>
	struct member_function_pod_type;

	REL_MAKE_MEMBER_FUNCTION_POD_TYPE();
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE(const);
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE(volatile);
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE(const volatile);

	template <class F>
	using member_function_pod_type_t = member_function_pod_type<F>::type;

	template <class>
	struct member_function_non_pod_type;

	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE();
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE(const);
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE(volatile);
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE(const volatile);

	template <class F>
	using member_function_non_pod_type_t = member_function_non_pod_type<F>::type;

	// Source: https://docs.microsoft.com/en-us/cpp/build/x64-calling-convention

	template <class T>
	concept meets_length_requirement =
		sizeof(T) == 1 ||
		sizeof(T) == 2 ||
		sizeof(T) == 4 ||
		sizeof(T) == 8;

	template <class T>
	concept meets_function_requirement =
		std::is_trivially_constructible_v<T> &&
		std::is_trivially_destructible_v<T> &&
		std::is_trivially_copy_assignable_v<T> &&
		!std::is_polymorphic_v<T>;

	template <class T>
	concept meets_member_requirement =
		std::is_standard_layout_v<T>;

	template <class T>
	concept is_x64_pod =
		!std::is_union_v<T> &&
		(!std::is_class_v<T> ||
			(meets_length_requirement<T> &&
				meets_function_requirement<T> &&
				meets_member_requirement<T>));

	template <class F, class... Args>
	__forceinline constexpr auto InvokeMemberFunctionPod(F&& a_func, Args&&... a_args) //
		noexcept(std::is_nothrow_invocable_v<F, Args...>)
			-> std::invoke_result_t<F, Args...>
		requires(std::is_invocable_v<F, Args...>)
	{
		using func_t = member_function_pod_type_t<std::decay_t<F>>;
		auto* funcPtr = REL::UnrestrictedCast<func_t*>(std::forward<F>(a_func));
		return std::invoke(funcPtr, std::forward<Args>(a_args)...);
	}

	template <class F, class First, class... Rest>
	__forceinline constexpr auto InvokeMemberFunctionNonPod(F&& a_func, First&& a_first, Rest&&... a_rest) //
		noexcept(std::is_nothrow_invocable_v<F, First, Rest...>)
			-> std::invoke_result_t<F, First, Rest...>
		requires(std::is_invocable_v<F, First, Rest...>)
	{
		using func_t = member_function_non_pod_type_t<std::decay_t<F>>;
		auto* funcPtr = REL::UnrestrictedCast<func_t*>(std::forward<F>(a_func));

		using result_t = std::invoke_result_t<F, First, Rest...>;
		alignas(result_t) auto result = std::array<std::byte, sizeof(result_t)>();

		return std::invoke(funcPtr, std::forward<First>(a_first), std::addressof(result), std::forward<Rest>(a_rest)...);
	}

	template <class F, class... Args>
	__forceinline constexpr auto InvokeFunction(F&& a_func, Args&&... a_args) //
		noexcept(std::is_nothrow_invocable_v<F, Args...>)
			-> std::invoke_result_t<F, Args...>
		requires(std::is_invocable_v<F, Args...>)
	{
		if constexpr (std::is_member_function_pointer_v<std::decay_t<F>>) {
			// member functions == free functions in x64
			if constexpr (is_x64_pod<std::invoke_result_t<F, Args...>>) {
				return InvokeMemberFunctionPod(std::forward<F>(a_func), std::forward<Args>(a_args)...);
			}
			else {
				// shift args to insert result
				return InvokeMemberFunctionNonPod(std::forward<F>(a_func), std::forward<Args>(a_args)...);
			}
		}
		else {
			return std::invoke(std::forward<F>(a_func), std::forward<Args>(a_args)...);
		}
	}

	template <class T, class Self>
	[[nodiscard]] __forceinline constexpr T& GetMemberAt(std::ptrdiff_t a_offset, Self* a_self) noexcept
		requires(std::is_class_v<Self>)
	{
		if (!a_self) [[unlikely]] {
			REX::Fail("Failed to get member on a null self pointer."sv);
		}

		const auto memberAddress = std::bit_cast<std::uintptr_t>(a_self) + a_offset;
		return *REL::UnrestrictedCast<T*>(memberAddress);
	}

	template <class T, class Self>
	[[nodiscard]] __forceinline T& GetVirtualMethodAt(std::size_t a_index, std::uintptr_t a_vtableAddress) noexcept
		requires(std::is_class_v<Self> &&
				 std::is_polymorphic_v<Self> &&
				 std::is_member_function_pointer_v<T>)
	{
		if (a_vtableAddress == 0) [[unlikely]] {
			REX::Fail("Failed to get virtual method on a null vtable address."sv);
		}

		const auto methodAddress = a_vtableAddress + (sizeof(std::uintptr_t) * a_index);
		if (methodAddress == 0) [[unlikely]] {
			REX::Fail("Failed to get virtual method on a null method pointer."sv);
		}

		return *REL::UnrestrictedCast<T*>(methodAddress);
	}

	template <class T, class Self, class... Args>
	__forceinline auto InvokeVirtualMethodAt(std::size_t a_index, std::uintptr_t a_vtableAddress, Self* a_self, Args&&... a_args) //
		noexcept(std::is_nothrow_invocable_v<T, Self*, Args...>)
			-> std::invoke_result_t<T, Self*, Args...>
		requires(std::is_class_v<Self> &&
				 std::is_polymorphic_v<Self> &&
				 std::is_member_function_pointer_v<T> &&
				 std::is_invocable_v<T, Self*, Args...>)
	{
		if (!a_self) [[unlikely]] {
			REX::Fail("Failed to invoke virtual method on a null self pointer."sv);
		}

		auto& method = GetVirtualMethodAt<T, Self>(a_index, a_vtableAddress);
		return Impl::InvokeFunction(std::forward<T>(method), a_self, std::forward<Args>(a_args)...);
	}

	template <class T, class Self>
	__forceinline T& GetVirtualMethodAt(std::size_t a_index, Self* a_self) noexcept
		requires(std::is_class_v<Self> &&
				 std::is_polymorphic_v<Self> &&
				 std::is_member_function_pointer_v<T>)
	{
		if (!a_self) [[unlikely]] {
			REX::Fail("Failed to get virtual method on a null self pointer."sv);
		}

		const auto vtableAddress = REL::GetVtableAddress(*a_self);
		return GetVirtualMethodAt<T, Self>(a_index, vtableAddress);
	}

	template <class T, class Self, class... Args>
	__forceinline auto InvokeVirtualMethodAt(std::size_t a_index, Self* a_self, Args&&... a_args) //
		noexcept(std::is_nothrow_invocable_v<T, Self*, Args...>)
			-> std::invoke_result_t<T, Self*, Args...>
		requires(std::is_class_v<Self> &&
				 std::is_polymorphic_v<Self> &&
				 std::is_member_function_pointer_v<T> &&
				 std::is_invocable_v<T, Self*, Args...>)
	{
		auto& method = GetVirtualMethodAt<T>(a_index, a_self);
		return Impl::InvokeFunction(std::forward<T>(method), a_self, std::forward<Args>(a_args)...);
	}
}

namespace REL
{
	template <class F, class... Args>
	constexpr auto InvokeFunction(F&& a_func, Args&&... a_args) //
		noexcept(std::is_nothrow_invocable_v<F, Args...>)
			-> std::invoke_result_t<F, Args...>
		requires(std::is_invocable_v<F, Args...>)
	{
		return Impl::InvokeFunction(std::forward<F>(a_func), std::forward<Args>(a_args)...);
	}

	template <class T, class Self>
	[[nodiscard]] constexpr T& GetMemberAt(std::ptrdiff_t a_offset, Self* a_self) noexcept
		requires(std::is_class_v<Self>)
	{
		return Impl::GetMemberAt<T>(a_offset, a_self);
	}

	template <class T, class Self>
	[[nodiscard]] constexpr const T& GetMemberAt(std::ptrdiff_t a_offset, const Self* a_self) noexcept
		requires(std::is_class_v<Self>)
	{
		return Impl::GetMemberAt<const T>(a_offset, a_self);
	}

	template <class T, class Self>
	[[nodiscard]] constexpr T& GetMemberAt(const REL::IOffset& a_offset, Self* a_self) noexcept
		requires(std::is_class_v<Self>)
	{
		return Impl::GetMemberAt<T>(a_offset.GetOffset(), a_self);
	}

	template <class T, class Self>
	[[nodiscard]] constexpr const T& GetMemberAt(const REL::IOffset& a_offset, const Self* a_self) noexcept
		requires(std::is_class_v<Self>)
	{
		return Impl::GetMemberAt<const T>(a_offset.GetOffset(), a_self);
	}

	template <class T, class Self>
	[[nodiscard]] T& GetVirtualMethodAt(std::size_t a_index, Self* a_self) noexcept
		requires(std::is_class_v<Self> &&
				 std::is_polymorphic_v<Self> &&
				 std::is_member_function_pointer_v<T>)
	{
		return Impl::GetVirtualMethodAt<T>(a_index, a_self);
	}

	template <class T, class Self>
	[[nodiscard]] T& GetVirtualMethodAt(const REL::ISize& a_index, Self* a_self) noexcept
		requires(std::is_class_v<Self> &&
				 std::is_polymorphic_v<Self> &&
				 std::is_member_function_pointer_v<T>)
	{
		return Impl::GetVirtualMethodAt<T>(a_index.GetSize(), a_self);
	}

	template <class T, class Self>
	[[nodiscard]] const T& GetVirtualMethodAt(std::size_t a_index, const Self* a_self) noexcept
		requires(std::is_class_v<Self> &&
				 std::is_polymorphic_v<Self> &&
				 std::is_member_function_pointer_v<T>)
	{
		return Impl::GetVirtualMethodAt<const T>(a_index, a_self);
	}

	template <class T, class Self>
	[[nodiscard]] const T& GetVirtualMethodAt(const REL::ISize& a_index, const Self* a_self) noexcept
		requires(std::is_class_v<Self> &&
				 std::is_polymorphic_v<Self> &&
				 std::is_member_function_pointer_v<T>)
	{
		return Impl::GetVirtualMethodAt<const T>(a_index.GetSize(), a_self);
	}

	template <class T, class Self, class... Args>
	auto InvokeVirtualMethodAt(std::size_t a_index, Self* a_self, Args&&... a_args) //
		noexcept(std::is_nothrow_invocable_v<T, Self*, Args...>)
			-> std::invoke_result_t<T, Self*, Args...>
		requires(std::is_class_v<Self> &&
				 std::is_polymorphic_v<Self> &&
				 std::is_member_function_pointer_v<T> &&
				 std::is_invocable_v<T, Self*, Args...>)
	{
		return Impl::InvokeVirtualMethodAt<T>(a_index, a_self, std::forward<Args>(a_args)...);
	}

	template <class T, class Self, class... Args>
	auto InvokeVirtualMethodAt(const REL::ISize& a_index, Self* a_self, Args&&... a_args) //
		noexcept(std::is_nothrow_invocable_v<T, Self*, Args...>)
			-> std::invoke_result_t<T, Self*, Args...>
		requires(std::is_class_v<Self> &&
				 std::is_polymorphic_v<Self> &&
				 std::is_member_function_pointer_v<T> &&
				 std::is_invocable_v<T, Self*, Args...>)
	{
		return Impl::InvokeVirtualMethodAt<T>(a_index.GetSize(), a_self, std::forward<Args>(a_args)...);
	}

	template <class T, class Self, class... Args>
	auto InvokeVirtualMethodAt(std::size_t a_index, const Self* a_self, Args&&... a_args) //
		noexcept(std::is_nothrow_invocable_v<T, const Self*, Args...>)
			-> std::invoke_result_t<T, const Self*, Args...>
		requires(std::is_class_v<Self> &&
				 std::is_polymorphic_v<Self> &&
				 std::is_member_function_pointer_v<T> &&
				 std::is_invocable_v<T, const Self*, Args...>)
	{
		return Impl::InvokeVirtualMethodAt<const T>(a_index, a_self, std::forward<Args>(a_args)...);
	}

	template <class T, class Self, class... Args>
	auto InvokeVirtualMethodAt(const REL::ISize& a_index, const Self* a_self, Args&&... a_args) //
		noexcept(std::is_nothrow_invocable_v<T, const Self*, Args...>)
			-> std::invoke_result_t<T, const Self*, Args...>
		requires(std::is_class_v<Self> &&
				 std::is_polymorphic_v<Self> &&
				 std::is_member_function_pointer_v<T> &&
				 std::is_invocable_v<T, const Self*, Args...>)
	{
		return Impl::InvokeVirtualMethodAt<const T>(a_index.GetSize(), a_self, std::forward<Args>(a_args)...);
	}
}

namespace REL
{
	template <class T = std::uintptr_t>
	class Relocation final
	{
	public:
		using value_type =
			std::conditional_t<
				std::is_member_pointer_v<T> || std::is_function_v<std::remove_pointer_t<T>>,
				std::decay_t<T>,
				T>;

		constexpr Relocation() noexcept = default;
		constexpr ~Relocation() noexcept = default;

		constexpr Relocation(const Relocation&) noexcept = default;
		constexpr Relocation(Relocation&&) noexcept = default;

		constexpr explicit Relocation(std::uintptr_t a_address) noexcept
			: _impl{ a_address }
		{
		}

		explicit Relocation(const REL::IId& a_id) noexcept
			: _impl{ a_id.GetAddress() }
		{
		}

		explicit Relocation(const REL::IOffset& a_offset) noexcept
			: _impl{ a_offset.GetAddress() }
		{
		}

		constexpr explicit Relocation(std::uintptr_t a_address, std::ptrdiff_t a_offset) noexcept
			: _impl{ a_address + a_offset }
		{
		}

		explicit Relocation(const REL::IId& a_id, std::ptrdiff_t a_offset) noexcept
			: _impl{ a_id.GetAddress() + a_offset }
		{
		}

		explicit Relocation(std::uintptr_t a_address, const REL::IOffset& a_offset) noexcept
			: _impl{ a_address + a_offset.GetOffset() }
		{
		}

		explicit Relocation(const REL::IId& a_id, const REL::IOffset& a_offset) noexcept
			: _impl{ a_id.GetAddress() + a_offset.GetOffset() }
		{
		}

		constexpr Relocation& operator=(const Relocation&) noexcept = default;
		constexpr Relocation& operator=(Relocation&&) noexcept = default;

		constexpr Relocation& operator=(std::uintptr_t a_address) noexcept
		{
			_impl = a_address;
			return *this;
		}

		Relocation& operator=(const REL::IId& a_id) noexcept
		{
			_impl = a_id.GetAddress();
			return *this;
		}

		Relocation& operator=(const REL::IOffset& a_offset) noexcept
		{
			_impl = a_offset.GetAddress();
			return *this;
		}

		[[nodiscard]] constexpr explicit operator bool() const noexcept
		{
			return _impl != INVALID_ADDRESS;
		}

		template <class U = value_type>
		[[nodiscard]] constexpr decltype(auto) operator*() const noexcept
			requires(std::is_pointer_v<U>)
		{
			return *get();
		}

		template <class U = value_type>
		[[nodiscard]] constexpr decltype(auto) operator->() const noexcept
			requires(std::is_pointer_v<U>)
		{
			return get();
		}

		template <class... Args>
		constexpr auto operator()(Args&&... a_args) const //
			noexcept(std::is_nothrow_invocable_v<const value_type&, Args...>)
				-> std::invoke_result_t<const value_type&, Args...>
			requires(std::is_invocable_v<const value_type&, Args...>)
		{
			return Impl::InvokeFunction(get(), std::forward<Args>(a_args)...);
		}

		[[nodiscard]] constexpr bool empty() const noexcept
		{
			return _impl == INVALID_ADDRESS;
		}

		[[nodiscard]] constexpr std::uintptr_t GetAddress() const noexcept
		{
			return _impl;
		}

		[[nodiscard]] std::uintptr_t GetOffset() const noexcept
		{
			REX::Assert(static_cast<bool>(*this));
			return _impl - REL::Module::GetSingleton()->GetBaseAddress();
		}

		[[nodiscard]] constexpr value_type get() const noexcept
		{
			REX::Assert(static_cast<bool>(*this));
			return REL::UnrestrictedCast<value_type>(_impl);
		}

		REX::SystemError Write(const void* a_newData, std::size_t a_size) const noexcept
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			return REL::WriteSafe(GetAddress(), a_newData, a_size);
		}

		template <REX::trivially_writable U>
		REX::SystemError Write(std::span<U> a_data) const noexcept
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			return REL::WriteSafe(GetAddress(), a_data);
		}

		template <REX::trivially_writable U>
		REX::SystemError Write(const U& a_data) const noexcept
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			return REL::WriteSafeData(GetAddress(), a_data);
		}

		REX::SystemError WriteFill(std::uint8_t a_value, std::size_t a_size) const noexcept
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			return REL::WriteSafeFill(GetAddress(), a_value, a_size);
		}

		template <std::size_t N>
		std::uintptr_t WriteJump(std::uintptr_t a_newAddress) const noexcept
			requires(std::same_as<value_type, std::uintptr_t> &&
					 REL::Impl::valid_jump_size<N>)
		{
			return REL::GetTrampoline()->WriteJump<N>(GetAddress(), a_newAddress);
		}

		template <std::size_t N, class F>
		std::uintptr_t WriteJump(const F& a_newFunc) const noexcept
			requires(std::same_as<value_type, std::uintptr_t> &&
					 REL::Impl::valid_jump_size<N> &&
					 std::is_function_v<F>)
		{
			return REL::GetTrampoline()->WriteJump<N>(GetAddress(), a_newFunc);
		}

		template <std::size_t N>
		std::uintptr_t WriteCall(std::uintptr_t a_newAddress) const noexcept
			requires(std::same_as<value_type, std::uintptr_t> &&
					 REL::Impl::valid_jump_size<N>)
		{
			return REL::GetTrampoline()->WriteCall<N>(GetAddress(), a_newAddress);
		}

		template <std::size_t N, class F>
		std::uintptr_t WriteCall(const F& a_newFunc) const noexcept
			requires(std::same_as<value_type, std::uintptr_t> &&
					 REL::Impl::valid_jump_size<N> &&
					 std::is_function_v<F>)
		{
			return REL::GetTrampoline()->WriteCall<N>(GetAddress(), a_newFunc);
		}

		std::uintptr_t WriteVirtualCall(std::size_t a_index, std::uintptr_t a_newFunc) const noexcept
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			const auto address = GetAddress() + (sizeof(std::uintptr_t) * a_index);
			const auto oldAddress = *std::bit_cast<const std::uintptr_t*>(address);

			const auto writeError = REL::WriteSafeData(address, a_newFunc);
			if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) {
				return INVALID_ADDRESS;
			}

			return oldAddress;
		}

		std::uintptr_t WriteVirtualCall(const REL::ISize& a_index, std::uintptr_t a_newFunc) const noexcept
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			return WriteVirtualCall(a_index.GetSize(), a_newFunc);
		}

		template <class F>
		std::uintptr_t WriteVirtualCall(std::size_t a_index, const F& a_newFunc) const noexcept
			requires(std::same_as<value_type, std::uintptr_t> &&
					 std::is_function_v<F>)
		{
			return WriteVirtualCall(a_index, REL::UnrestrictedCast<std::uintptr_t>(a_newFunc));
		}

		template <class F>
		std::uintptr_t WriteVirtualCall(const REL::ISize& a_index, const F& a_newFunc) const noexcept
			requires(std::same_as<value_type, std::uintptr_t> &&
					 std::is_function_v<F>)
		{
			return WriteVirtualCall(a_index.GetSize(), REL::UnrestrictedCast<std::uintptr_t>(a_newFunc));
		}

		REX::SystemError ReplaceFunction(std::size_t a_size, std::uintptr_t a_newAddress) const noexcept
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			const auto assembly = REL::Asm::Jump14(a_newAddress);

			const auto writeSafeFillErrorCode = REL::WriteSafeFill(GetAddress(), INT3, a_size);
			if (writeSafeFillErrorCode != REX::ERROR_NUMBER_SUCCESS) {
				return writeSafeFillErrorCode;
			}

			const auto writeSafeErrorCode = REL::WriteSafe(GetAddress(), std::addressof(assembly), sizeof(assembly));
			if (writeSafeErrorCode != REX::ERROR_NUMBER_SUCCESS) {
				return writeSafeErrorCode;
			}
		}

		template <class F>
		REX::SystemError ReplaceFunction(std::size_t a_size, const F& a_newFunc) const noexcept
			requires(std::same_as<value_type, std::uintptr_t> &&
					 std::is_function_v<F>)
		{
			return ReplaceFunction(a_size, REL::UnrestrictedCast<std::uintptr_t>(a_newFunc));
		}

		template <class... Args>
		auto Invoke(Args&&... a_args) const //
			noexcept(std::is_nothrow_invocable_v<const value_type&, Args...>)
				-> std::invoke_result_t<const value_type&, Args...>
			requires(std::is_invocable_v<const value_type&, Args...>)
		{
			return Impl::InvokeFunction(get(), std::forward<Args>(a_args)...);
		}

		template <class Self, class... Args>
		auto InvokeVirtual(std::size_t a_index, Self* a_self, Args&&... a_args) const //
			noexcept(std::is_nothrow_invocable_v<const value_type&, Self*, Args...>)
				-> std::invoke_result_t<const value_type&, Self*, Args...>
			requires(std::is_class_v<Self> &&
					 std::is_polymorphic_v<Self> &&
					 std::is_member_function_pointer_v<value_type> &&
					 std::is_invocable_v<const value_type&, Self*, Args...>)
		{
			return Impl::InvokeVirtualMethodAt<value_type>(a_index, GetAddress(), a_self, std::forward<Args>(a_args)...);
		}

		template <class Self, class... Args>
		auto InvokeVirtual(const REL::ISize& a_index, Self* a_self, Args&&... a_args) const //
			noexcept(std::is_nothrow_invocable_v<const value_type&, Self*, Args...>)
				-> std::invoke_result_t<const value_type&, Self*, Args...>
			requires(std::is_class_v<Self> &&
					 std::is_polymorphic_v<Self> &&
					 std::is_member_function_pointer_v<value_type> &&
					 std::is_invocable_v<const value_type&, Self*, Args...>)
		{
			return Impl::InvokeVirtualMethodAt<value_type>(a_index.GetSize(), GetAddress(), a_self, std::forward<Args>(a_args)...);
		}

		template <class Self, class... Args>
		auto InvokeVirtual(std::size_t a_index, const Self* a_self, Args&&... a_args) const //
			noexcept(std::is_nothrow_invocable_v<const value_type&, const Self*, Args...>)
				-> std::invoke_result_t<const value_type&, const Self*, Args...>
			requires(std::is_class_v<Self> &&
					 std::is_polymorphic_v<Self> &&
					 std::is_member_function_pointer_v<value_type> &&
					 std::is_invocable_v<const value_type&, const Self*, Args...>)
		{
			return Impl::InvokeVirtualMethodAt<const value_type>(a_index, GetAddress(), a_self, std::forward<Args>(a_args)...);
		}

		template <class Self, class... Args>
		auto InvokeVirtual(const REL::ISize& a_index, const Self* a_self, Args&&... a_args) const //
			noexcept(std::is_nothrow_invocable_v<const value_type&, const Self*, Args...>)
				-> std::invoke_result_t<const value_type&, const Self*, Args...>
			requires(std::is_class_v<Self> &&
					 std::is_polymorphic_v<Self> &&
					 std::is_member_function_pointer_v<value_type> &&
					 std::is_invocable_v<const value_type&, const Self*, Args...>)
		{
			return Impl::InvokeVirtualMethodAt<const value_type>(a_index.GetSize(), GetAddress(), a_self, std::forward<Args>(a_args)...);
		}

	private:
		std::uintptr_t _impl{ INVALID_ADDRESS };
	};
}

#undef REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE
#undef REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER
#undef REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER_IMPL

#undef REL_MAKE_MEMBER_FUNCTION_POD_TYPE
#undef REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER
#undef REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER_IMPL
