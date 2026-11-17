#pragma once

#include "msvc/functional_base.hpp"
#include "msvc/type_info.hpp"
#include "msvc/type_traits.hpp"

namespace msvc::detail
{
#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// class `std::_Func_base`
	template <class Result, class... Args>
	class __declspec(novtable) func_base
	{
	public:
		using result_type = Result;

		func_base() noexcept = default;
		~func_base() noexcept = default;

		func_base(const func_base&) = delete;
		func_base(func_base&&) = delete;

		auto operator=(const func_base&) -> func_base& = delete;
		auto operator=(func_base&&) -> func_base& = delete;

		// add
		[[nodiscard]]
		virtual auto copy(void* a_storage) const -> func_base* = 0; // 0x00
		[[nodiscard]]
		virtual auto move(void* a_storage) noexcept -> func_base* = 0; // 0x01
		virtual auto do_call(Args&&... a_args) -> result_type = 0;	   // 0x02
		[[nodiscard]]
		virtual auto target_type() const noexcept -> const msvc::type_info& = 0; // 0x03
		virtual void delete_this(bool a_deallocate) noexcept = 0;				 // 0x04
		[[nodiscard]]
		virtual auto get() const noexcept -> const void* = 0; // 0x05

		[[nodiscard]]
		auto target(const msvc::type_info& a_typeInfo) const noexcept -> const void*
		{
			return target_type() == a_typeInfo ? get() : nullptr;
		}
	};

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif

	// class `std::_Func_impl_no_alloc`
	template <class Callable, class Result, class... Args>
	class func_impl_no_alloc final : public func_base<Result, Args...>
	{
	private:
		using base_type = func_base<Result, Args...>;

	public:
		using callable_type = Callable;
		using result_type = Result;

		template <class Func>
		explicit func_impl_no_alloc(Func&& a_func)
			requires(!std::same_as<std::decay_t<Func>, func_impl_no_alloc>)
			:
			_callable(std::forward<Func>(a_func))
		{
		}

		~func_impl_no_alloc() noexcept = default;

		[[nodiscard]]
		auto copy(void* a_storage) const -> base_type* override // 0x00
		{
			if constexpr (!std::is_copy_constructible_v<callable_type>) {
				std::terminate();
			}
			else {
				if (detail::is_large_object<func_impl_no_alloc>()) {
					return detail::global_new<func_impl_no_alloc>(_callable);
				}

				return std::construct_at(static_cast<func_impl_no_alloc*>(a_storage), _callable);
			}
		}

		[[nodiscard]]
		auto move(void* a_storage) noexcept -> base_type* override // 0x01
		{
			if (detail::is_large_object<func_impl_no_alloc>()) {
				return nullptr;
			}

			return std::construct_at(static_cast<func_impl_no_alloc*>(a_storage), std::move(_callable));
		}

		auto do_call(Args&&... a_args) -> result_type override // 0x02
		{
			if constexpr (std::same_as<result_type, void>) {
				std::invoke(_callable, std::forward<Args>(a_args)...);
			}
			else {
				return std::invoke(_callable, std::forward<Args>(a_args)...);
			}
		}

		[[nodiscard]]
		auto target_type() const noexcept -> const msvc::type_info& override // 0x03
		{
			return REX::CheckedReinterpretCast<const msvc::type_info&>(typeid(callable_type));
		}

		void delete_this(bool a_deallocate) noexcept override // 0x04
		{
			this->~func_impl_no_alloc();

			if (a_deallocate) {
				std::allocator<func_impl_no_alloc>().deallocate(this, 1);
			}
		}

		[[nodiscard]]
		auto get() const noexcept -> const void* override // 0x05
		{
			return static_cast<const void*>(std::addressof(_callable));
		}

	private:
		// members
		callable_type _callable; // 0x08
	};

	// class `std::_Func_class`
	template <class Result, class... Args>
	class func_class : public msvc::arg_types<Args...>
	{
	private:
		using base_type = func_base<Result, Args...>;

	public:
		using result_type = Result;

		func_class() noexcept
		{
			set_impl(nullptr);
		}

		~func_class() noexcept
		{
			reset();
		}

		func_class(const func_class&) = delete;
		func_class(func_class&&) = delete;

		auto operator=(const func_class&) -> func_class& = delete;
		auto operator=(func_class&&) -> func_class& = delete;

		auto operator()(Args... a_args) const -> result_type
		{
			REX::Assert(!empty());
			return get_impl()->do_call(std::forward<Args>(a_args)...);
		}

	protected:
		template <class LFunc, class RFunc>
		using enable_if_callable_t = std::enable_if_t<
			std::conjunction_v<
				std::negation<std::is_same<std::remove_cvref_t<LFunc>, RFunc>>,
				std::is_invocable_r<Result, std::decay_t<LFunc>, Args...>>,
			std::int32_t>;

		[[nodiscard]]
		auto empty() const noexcept -> bool
		{
			return get_impl() == nullptr;
		}

		void reset_copy(const func_class& a_rhs)
		{
			if (!a_rhs.empty()) {
				set_impl(a_rhs.get_impl()->copy(std::addressof(_storage)));
			}
		}

		void reset_move(func_class& a_rhs) noexcept
		{
			if (a_rhs.empty()) {
				return;
			}

			if (a_rhs.is_local_impl()) {
				set_impl(a_rhs.get_impl()->move(std::addressof(_storage)));
				a_rhs.reset();
				return;
			}

			set_impl(a_rhs.get_impl());
			a_rhs.set_impl(nullptr);
		}

		template <class Func>
		void reset(Func&& a_func)
			requires(std::is_invocable_r_v<Result, Func, Args...>)
		{
			if (!detail::do_test_callable(a_func)) {
				return;
			}

			using func_t = func_impl_no_alloc<std::decay_t<Func>, Result, Args...>;

			if (detail::is_large_object<func_t>()) {
				auto* ptr = detail::global_new<func_t>(std::forward<Func>(a_func));
				set_impl(ptr);
				return;
			}

			auto* ptr =
				std::construct_at(reinterpret_cast<func_t*>(std::addressof(_storage)), std::forward<Func>(a_func));
			set_impl(ptr);
		}

		void reset() noexcept
		{
			if (!empty()) {
				get_impl()->delete_this(!is_local_impl());
				set_impl(nullptr);
			}
		}

		void swap(func_class& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			if (!is_local_impl() && !a_other.is_local_impl()) {
				auto* temp = get_impl();
				set_impl(a_other.get_impl());
				a_other.set_impl(temp);
				return;
			}

			auto temp = func_class();
			temp.reset_move(*this);
			this->reset_move(a_other);
			a_other.reset_move(temp);
		}

		[[nodiscard]]
		auto target_type() const noexcept -> const msvc::type_info&
		{
			return !empty() ? get_impl()->target_type() :
							  REX::CheckedReinterpretCast<const msvc::type_info&>(typeid(void));
		}

		[[nodiscard]]
		auto target(const msvc::type_info& a_typeInfo) const noexcept -> const void*
		{
			return !empty() ? get_impl()->target(a_typeInfo) : nullptr;
		}

	private:
		[[nodiscard]]
		auto is_local_impl() const noexcept -> bool
		{
			return get_impl() == static_cast<const void*>(std::addressof(_storage));
		}

		[[nodiscard]]
		auto get_impl() const noexcept -> base_type*
		{
			return _storage.ptrs[detail::get_small_object_ptr_count() - 1];
		}

		void set_impl(base_type* a_func) noexcept
		{
			_storage.ptrs[detail::get_small_object_ptr_count() - 1] = a_func;
		}

		union storage_union
		{
			// members
			std::max_align_t alignment;
			std::array<std::byte, msvc::detail::STORAGE_SIZE> padding;
			std::array<base_type*, msvc::detail::SMALL_OBJECT_PTR_COUNT> ptrs;
		};

		static_assert(sizeof(storage_union) == msvc::detail::SMALL_OBJECT_PTR_COUNT * sizeof(std::uintptr_t));

		// members
		storage_union _storage; // 0x00
	};

	// struct std::_Get_function_impl
	template <class>
	struct get_function_impl
	{
		static_assert(false, "`msvc::function` only accepts function types as template arguments.");
	};

#define MSVC_GET_FUNCTION_IMPL(CALL_OPT, X1, X2, X3)   \
	template <class Result, class... Args>             \
	struct get_function_impl<Result CALL_OPT(Args...)> \
	{                                                  \
		using type = func_class<Result, Args...>;      \
	};

	MSVC_NON_MEMBER_CALL(MSVC_GET_FUNCTION_IMPL, X1, X2, X3)

#undef MSVC_GET_FUNCTION_IMPL
}

namespace msvc
{
	template <class T>
	class function : public detail::get_function_impl<T>::type
	{
	private:
		using base_type = detail::get_function_impl<T>::type;

	public:
		function() noexcept = default;
		~function() noexcept = default;

		// NOLINTNEXTLINE(misc-explicit-constructor)
		function(std::nullptr_t) noexcept
		{
		}

		template <class Func, base_type::template enable_if_callable_t<T, Func> = 0>
		// NOLINTNEXTLINE(bugprone-forwarding-reference-overload, misc-explicit-constructor)
		function(Func&& a_func)
		{
			static_assert(
				std::is_copy_constructible_v<std::decay_t<Func>>,
				"The target function object type must be copy constructible.");

			base_type::reset(std::forward<Func>(a_func));
		}

		function(const function& a_rhs)
		{
			base_type::reset_copy(a_rhs);
		}

		function(function&& a_rhs) noexcept
		{
			base_type::reset_move(a_rhs);
		}

		auto operator=(std::nullptr_t) noexcept -> function&
		{
			base_type::reset();
			return *this;
		}

		template <class Func>
		auto operator=(std::reference_wrapper<Func> a_func) noexcept -> function&
		{
			base_type::reset();
			base_type::reset(a_func);
			return *this;
		}

		template <class Func, base_type::template enable_if_callable_t<T, Func> = 0>
		auto operator=(Func&& a_func) -> function&
		{
			base_type::reset(std::forward<Func>(a_func));
			return *this;
		}

		auto operator=(const function& a_rhs) -> function&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			base_type::reset();
			base_type::reset_copy(a_rhs);
			return *this;
		}

		auto operator=(function&& a_rhs) noexcept -> function&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			base_type::reset();
			base_type::reset_move(a_rhs);
			return *this;
		}

		[[nodiscard]]
		explicit operator bool() const noexcept
		{
			return !base_type::empty();
		}

		void swap(function& a_other) noexcept
		{
			base_type::swap(a_other);
		}

		[[nodiscard]]
		auto target_type() const noexcept -> const msvc::type_info&
		{
			return base_type::target_type();
		}

		[[nodiscard]]
		auto target() noexcept -> T*
		{
			if constexpr (std::is_function_v<T>) {
				return nullptr;
			}
			else {
				// NOLINTNEXTLINE(bugprone-casting-through-void)
				return reinterpret_cast<T*>(const_cast<void*>(base_type::target(typeid(T))));
			}
		}

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'180)
#endif

		[[nodiscard]]
		auto target() const noexcept -> const T*
		{
			if constexpr (std::is_function_v<T>) {
				return nullptr;
			}
			else {
				return reinterpret_cast<const T*>(base_type::target(typeid(T)));
			}
		}

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif
	};

	static_assert(sizeof(msvc::function<void()>) == 0x40);

	template <class T>
	function(T) -> function<typename detail::deduce_signature<T>::type>;

#define MSVC_FUNCTION_POINTER_DEDUCTION_GUIDE(CALL_OPT, X1, X2, X3)    \
	template <class Result, class... Args>                             \
	function(Result(CALL_OPT*)(Args...)) -> function<Result(Args...)>;

	MSVC_NON_MEMBER_CALL(MSVC_FUNCTION_POINTER_DEDUCTION_GUIDE, X1, X2, X3)

#undef MSVC_FUNCTION_POINTER_DEDUCTION_GUIDE

	template <class T>
	[[nodiscard]]
	auto operator==(const function<T>& a_lhs, std::nullptr_t) noexcept -> bool
	{
		return !a_lhs;
	}

	template <class T>
	[[nodiscard]]
	auto operator==(std::nullptr_t, const function<T>& a_rhs) noexcept -> bool
	{
		return !a_rhs;
	}

	template <class T>
	void swap(function<T>& a_lhs, function<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}
