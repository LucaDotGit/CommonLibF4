#pragma once

#include "msvc/type_info.hpp"
#include "msvc/type_traits.hpp"

namespace msvc::detail
{
	inline constexpr auto STORAGE_SIZE = static_cast<std::size_t>((msvc::detail::SMALL_OBJECT_PTR_COUNT - 1) * sizeof(std::uintptr_t));
	inline constexpr auto STORAGE_SIZE_OLD = static_cast<std::size_t>((msvc::detail::SMALL_OBJECT_PTR_COUNT_OLD - 1) * sizeof(std::uintptr_t));

	template <class T>
	concept large_object =
		sizeof(T) > STORAGE_SIZE ||
		alignof(T) > alignof(std::max_align_t) ||
		!std::is_nothrow_move_constructible_v<T>;

	template <class T>
	concept large_object_old =
		sizeof(T) > STORAGE_SIZE_OLD ||
		alignof(T) > alignof(std::max_align_t) ||
		!std::is_nothrow_move_constructible_v<T>;

	template <class T>
	concept testable_callable =
		requires(T a_callable) { std::invoke(a_callable); };

	[[nodiscard]] inline std::size_t get_small_object_ptr_count() noexcept
	{
		if (F4SE::IsRuntimeAtLeastNG()) {
			return msvc::detail::SMALL_OBJECT_PTR_COUNT;
		}

		return msvc::detail::SMALL_OBJECT_PTR_COUNT_OLD;
	}

	template <class T>
	[[nodiscard]] bool is_large_object() noexcept
	{
		if (F4SE::IsRuntimeAtLeastNG()) {
			return large_object<T>;
		}

		return large_object_old<T>;
	}

	template <class T>
	[[nodiscard]] bool do_test_callable(const T& a_callable) noexcept
	{
		if constexpr (testable_callable<T>) {
			return !!a_callable;
		}
		else {
			return true;
		}
	}

	template <class T, class... Args>
	[[nodiscard]] T* global_new(Args&&... a_args)
	{
		struct guard_type
		{
		public:
			~guard_type()
			{
				if (ptr) {
					std::allocator<T>().deallocate(ptr, 1);
				}
			}

			T* ptr;
		};

		auto guard = guard_type{ .ptr = std::allocator<T>().allocate(1) };
		std::construct_at(guard.ptr, std::forward<Args>(a_args)...);
		return static_cast<T*>(std::exchange(guard.ptr, nullptr));
	}
}

namespace msvc::detail
{
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

		func_base& operator=(const func_base&) = delete;
		func_base& operator=(func_base&&) = delete;

		// add
		[[nodiscard]] virtual func_base* copy(void* a_storage) const = 0;			   // 00
		[[nodiscard]] virtual func_base* move(void* a_storage) noexcept = 0;		   // 01
		virtual result_type do_call(Args&&... a_args) = 0;							   // 02
		[[nodiscard]] virtual const msvc::type_info& target_type() const noexcept = 0; // 03
		virtual void delete_this(bool a_deallocate) noexcept = 0;					   // 04
		[[nodiscard]] virtual const void* get() const noexcept = 0;					   // 05

		[[nodiscard]] const void* target(const msvc::type_info& a_typeInfo) const noexcept
		{
			return target_type() == a_typeInfo ? get() : nullptr;
		}
	};

	// class `std::_Func_impl_no_alloc`
	template <class Callable, class Result, class... Args>
	class func_impl_no_alloc final
		: public func_base<Result, Args...>
	{
	private:
		using base_type = func_base<Result, Args...>;

	public:
		using callable_type = Callable;
		using result_type = Result;

		template <class Func>
		explicit func_impl_no_alloc(Func&& a_func)
			requires(!std::same_as<std::decay_t<Func>, func_impl_no_alloc>)
			: _callable(std::forward<Func>(a_func))
		{
		}

		~func_impl_no_alloc() noexcept = default;

		[[nodiscard]] base_type* copy(void* a_storage) const override // 00
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

		[[nodiscard]] base_type* move(void* a_storage) noexcept override // 01
		{
			if (detail::is_large_object<func_impl_no_alloc>()) {
				return nullptr;
			}

			return std::construct_at(static_cast<func_impl_no_alloc*>(a_storage), std::move(_callable));
		}

		result_type do_call(Args&&... a_args) override // 02
		{
			if constexpr (std::same_as<result_type, void>) {
				std::invoke(_callable, std::forward<Args>(a_args)...);
			}
			else {
				return std::invoke(_callable, std::forward<Args>(a_args)...);
			}
		}

		[[nodiscard]] const msvc::type_info& target_type() const noexcept override // 03
		{
			return reinterpret_cast<const msvc::type_info&>(typeid(callable_type));
		}

		void delete_this(bool a_deallocate) noexcept override // 04
		{
			this->~func_impl_no_alloc();

			if (a_deallocate) {
				std::allocator<func_impl_no_alloc>().deallocate(this, 1);
			}
		}

		[[nodiscard]] const void* get() const noexcept override // 05
		{
			return static_cast<const void*>(std::addressof(_callable));
		}

	private:
		// members
		callable_type _callable; // 08
	};

	// class `std::_Func_class`
	template <class Result, class... Args>
	class func_class
		: public msvc::arg_types<Args...>
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

		result_type operator()(Args... a_args) const
		{
			REX::Assert(!empty());
			return get_impl()->do_call(std::forward<Args>(a_args)...);
		}

	protected:
		template <class LFunc, class RFunc>
		using enable_if_callable_t =
			std::enable_if_t<
				std::conjunction_v<
					std::negation<
						std::is_same<std::remove_cvref_t<LFunc>, RFunc>>,
					std::is_invocable_r<Result, std::decay_t<LFunc>, Args...>>,
				std::int32_t>;

		[[nodiscard]] bool empty() const noexcept
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

			auto* ptr = std::construct_at(reinterpret_cast<func_t*>(std::addressof(_storage)), std::forward<Func>(a_func));
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

		[[nodiscard]] const msvc::type_info& target_type() const noexcept
		{
			return !empty() ? get_impl()->target_type() : reinterpret_cast<const msvc::type_info&>(typeid(void));
		}

		[[nodiscard]] const void* target(const msvc::type_info& a_typeInfo) const noexcept
		{
			return !empty() ? get_impl()->target(a_typeInfo) : nullptr;
		}

	private:
		[[nodiscard]] bool is_local_impl() const noexcept
		{
			return get_impl() == static_cast<const void*>(std::addressof(_storage));
		}

		[[nodiscard]] base_type* get_impl() const noexcept
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
		storage_union _storage; // 00
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

namespace msvc::detail
{
	// class `std::_Func_base`
	template <class Result, class... Args>
	class __declspec(novtable) func_base_old
	{
	public:
		using result_type = Result;

		func_base_old() noexcept = default;

		func_base_old(const func_base_old&) = delete;
		func_base_old(func_base_old&&) = delete;

		func_base_old& operator=(const func_base_old&) = delete;
		func_base_old& operator=(func_base_old&&) = delete;

		// add
		[[nodiscard]] virtual func_base_old* copy(void* a_storage) const = 0;		   // 00
		[[nodiscard]] virtual func_base_old* move(void* a_storage) noexcept = 0;	   // 01
		virtual result_type do_call(Args&&... a_args) = 0;							   // 02
		[[nodiscard]] virtual const msvc::type_info& target_type() const noexcept = 0; // 03
		virtual void delete_this(bool a_deallocate) noexcept = 0;					   // 04
		virtual ~func_base_old() noexcept = default;								   // 05
		[[nodiscard]] virtual const void* get() const noexcept = 0;					   // 06

		[[nodiscard]] const void* target(const msvc::type_info& a_typeInfo) const noexcept
		{
			return target_type() == a_typeInfo ? get() : nullptr;
		}
	};

	// class `std::_Func_impl_no_alloc`
	template <class Callable, class Result, class... Args>
	class func_impl_no_alloc_old final
		: public func_base_old<Result, Args...>
	{
	private:
		using base_type = func_base_old<Result, Args...>;

	public:
		using callable_type = Callable;
		using result_type = Result;

		template <class Func>
		explicit func_impl_no_alloc_old(Func&& a_func)
			requires(!std::same_as<std::decay_t<Func>, func_impl_no_alloc_old>)
			: _callable(std::forward<Func>(a_func))
		{
		}

		[[nodiscard]] base_type* copy(void* a_storage) const override // 00
		{
			if constexpr (!std::is_copy_constructible_v<callable_type>) {
				std::terminate();
			}
			else {
				if constexpr (large_object_old<func_impl_no_alloc_old>) {
					return detail::global_new<func_impl_no_alloc_old>(_callable);
				}
				{
					return std::construct_at(static_cast<func_impl_no_alloc_old*>(a_storage), _callable);
				}
			}
		}

		[[nodiscard]] base_type* move(void* a_storage) noexcept override // 01
		{
			if constexpr (large_object_old<func_impl_no_alloc_old>) {
				return nullptr;
			}
			else {
				return std::construct_at(static_cast<func_impl_no_alloc_old*>(a_storage), std::move(_callable));
			}
		}

		result_type do_call(Args&&... a_args) override // 02
		{
			if constexpr (std::same_as<result_type, void>) {
				std::invoke(_callable, std::forward<Args>(a_args)...);
			}
			else {
				return std::invoke(_callable, std::forward<Args>(a_args)...);
			}
		}

		[[nodiscard]] const msvc::type_info& target_type() const noexcept override // 03
		{
			return reinterpret_cast<const msvc::type_info&>(typeid(callable_type));
		}

		void delete_this(bool a_deallocate) noexcept override // 04
		{
			this->~func_impl_no_alloc_old();

			if (a_deallocate) {
				std::allocator<func_impl_no_alloc_old>().deallocate(this, 1);
			}
		}

		~func_impl_no_alloc_old() noexcept override = default; // 05

		[[nodiscard]] const void* get() const noexcept override // 05
		{
			return static_cast<const void*>(std::addressof(_callable));
		}

	private:
		// members
		callable_type _callable; // 08
	};

	// class `std::_Func_class`
	template <class Result, class... Args>
	class func_class_old
		: public msvc::arg_types<Args...>
	{
	private:
		using base_type = func_base_old<Result, Args...>;

	public:
		using result_type = Result;

		func_class_old() noexcept
		{
			set_impl(nullptr);
		}

		~func_class_old() noexcept
		{
			reset();
		}

		result_type operator()(Args... a_args) const
		{
			REX::Assert(!empty());
			return get_impl()->do_call(std::forward<Args>(a_args)...);
		}

	protected:
		template <class LFunc, class RFunc>
		using enable_if_callable_t =
			std::enable_if_t<
				std::conjunction_v<
					std::negation<
						std::is_same<std::remove_cvref_t<LFunc>, RFunc>>,
					std::is_invocable_r<Result, std::decay_t<LFunc>, Args...>>,
				std::int32_t>;

		[[nodiscard]] bool empty() const noexcept
		{
			return get_impl() == nullptr;
		}

		void reset_copy(const func_class_old& a_rhs)
		{
			if (!a_rhs.empty()) {
				set_impl(a_rhs.get_impl()->copy(std::addressof(_storage)));
			}
		}

		void reset_move(func_class_old& a_rhs) noexcept
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

			if constexpr (detail::large_object_old<func_t>) {
				auto* ptr = detail::global_new<func_t>(std::forward<Func>(a_func));
				set_impl(ptr);
			}
			else {
				auto* ptr = std::construct_at(reinterpret_cast<func_t*>(std::addressof(_storage)), std::forward<Func>(a_func));
				set_impl(ptr);
			}
		}

		void reset() noexcept
		{
			if (!empty()) {
				get_impl()->delete_this(!is_local_impl());
				set_impl(nullptr);
			}
		}

		void swap(func_class_old& a_other) noexcept
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

			auto temp = func_class_old();
			temp.reset_move(*this);
			this->reset_move(a_other);
			a_other.reset_move(temp);
		}

		[[nodiscard]] const msvc::type_info& target_type() const noexcept
		{
			return !empty() ? get_impl()->target_type() : reinterpret_cast<const msvc::type_info&>(typeid(void));
		}

		[[nodiscard]] const void* target(const msvc::type_info& a_typeInfo) const noexcept
		{
			return !empty() ? get_impl()->target(a_typeInfo) : nullptr;
		}

	private:
		[[nodiscard]] bool is_local_impl() const noexcept
		{
			return get_impl() == static_cast<const void*>(std::addressof(_storage));
		}

		[[nodiscard]] base_type* get_impl() const noexcept
		{
			return _storage.ptrs[msvc::detail::SMALL_OBJECT_PTR_COUNT_OLD - 1];
		}

		void set_impl(base_type* a_func) noexcept
		{
			_storage.ptrs[msvc::detail::SMALL_OBJECT_PTR_COUNT_OLD - 1] = a_func;
		}

		union storage_union
		{
			// members
			std::max_align_t alignment;
			std::array<std::byte, msvc::detail::STORAGE_SIZE_OLD> padding;
			std::array<base_type*, msvc::detail::SMALL_OBJECT_PTR_COUNT_OLD> ptrs;
		};
		static_assert(sizeof(storage_union) == msvc::detail::SMALL_OBJECT_PTR_COUNT_OLD * sizeof(std::uintptr_t));

		// members
		storage_union _storage; // 00
	};

	// struct std::_Get_function_impl
	template <class>
	struct get_function_impl_old
	{
		static_assert(false, "`msvc::function_old` only accepts function types as template arguments.");
	};

#define MSVC_GET_FUNCTION_IMPL(CALL_OPT, X1, X2, X3)       \
	template <class Result, class... Args>                 \
	struct get_function_impl_old<Result CALL_OPT(Args...)> \
	{                                                      \
		using type = func_class_old<Result, Args...>;      \
	};

	MSVC_NON_MEMBER_CALL(MSVC_GET_FUNCTION_IMPL, X1, X2, X3)

#undef MSVC_GET_FUNCTION_IMPL
}

namespace msvc::detail
{
	// struct std::_Deduce_from_call_operator
	template <class Func, class CallOperator, class = void>
	struct deduce_from_call_operator
		: public msvc::is_member_function_ptr<CallOperator>::_Guide_type
	{
	};

	// struct std::_Inspect_static_call_operator
	template <class>
	struct inspect_static_call_operator
	{
	};

	// NOLINTBEGIN(bugprone-macro-parentheses)
#define MSVC_STATIC_CALL_OPERATOR_GUIDES(CALL_OPT, CV_OPT, REF_OPT, NOEXCEPT_OPT) \
	template <class Result, class... Args>                                        \
	struct inspect_static_call_operator<Result(CALL_OPT*)(Args...) NOEXCEPT_OPT>  \
	{                                                                             \
		using type = Result(Args...);                                             \
	};
	// NOLINTEND(bugprone-macro-parentheses)

	MSVC_NON_MEMBER_CALL(MSVC_STATIC_CALL_OPERATOR_GUIDES, , , )
	MSVC_NON_MEMBER_CALL(MSVC_STATIC_CALL_OPERATOR_GUIDES, , , noexcept)

#undef MSVC_STATIC_CALL_OPERATOR_GUIDES

	// struct std::_Deduce_from_call_operator
	template <class Func, class CallOperator>
	struct deduce_from_call_operator<Func, CallOperator, std::void_t<decltype(std::declval<Func>()())>>
		: public inspect_static_call_operator<CallOperator>
	{
	};

	// struct std::_Deduce_signature
	template <class Func, class = void>
	struct deduce_signature
	{
	};

	template <class Func>
	struct deduce_signature<Func, std::void_t<decltype(&Func::operator())>>
		: public deduce_from_call_operator<Func, decltype(&Func::operator())>
	{
	};
}

namespace msvc
{
	template <class T>
	class function
		: public detail::get_function_impl<T>::type
	{
	private:
		using base_type = detail::get_function_impl<T>::type;

	public:
		function() noexcept = default;

		function(std::nullptr_t) noexcept
		{
		}

		template <class Func, base_type::template enable_if_callable_t<T, Func> = 0>
		function(Func&& a_func) // NOLINT(bugprone-forwarding-reference-overload)
		{
			static_assert(std::is_copy_constructible_v<std::decay_t<Func>>,
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

		function& operator=(std::nullptr_t) noexcept
		{
			base_type::reset();
			return *this;
		}

		template <class Func>
		function& operator=(std::reference_wrapper<Func> a_func) noexcept
		{
			base_type::reset();
			base_type::reset(a_func);
			return *this;
		}

		template <class Func, base_type::template enable_if_callable_t<T, Func> = 0>
		function& operator=(Func&& a_func)
		{
			base_type::reset(std::forward<Func>(a_func));
			return *this;
		}

		function& operator=(const function& a_rhs)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			base_type::reset();
			base_type::reset_copy(a_rhs);
			return *this;
		}

		function& operator=(function&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			base_type::reset();
			base_type::reset_move(a_rhs);
			return *this;
		}

		[[nodiscard]] explicit operator bool() const noexcept
		{
			return !base_type::empty();
		}

		void swap(function& a_other) noexcept
		{
			base_type::swap(a_other);
		}

		[[nodiscard]] const msvc::type_info& target_type() const noexcept
		{
			return base_type::target_type();
		}

		[[nodiscard]] T* target() noexcept
		{
			if constexpr (std::is_function_v<T>) {
				return nullptr;
			}
			else {
				// NOLINTNEXTLINE(bugprone-casting-through-void)
				return reinterpret_cast<T*>(const_cast<void*>(base_type::target(typeid(T))));
			}
		}

#if _MSC_VER > 0l
#pragma warning(push)
#pragma warning(disable : 4180) // qualifier applied to function type has no meaning; ignored
#endif

		[[nodiscard]] const T* target() const noexcept
		{
			if constexpr (std::is_function_v<T>) {
				return nullptr;
			}
			else {
				// NOLINTNEXTLINE(bugprone-casting-through-void)
				return reinterpret_cast<const T*>(base_type::target(typeid(T)));
			}
		}

#if _MSC_VER > 0l
#pragma warning(pop)
#endif
	};
	static_assert(sizeof(msvc::function<void()>) == 0x40);

	template <class T>
	function(T) -> function<typename detail::deduce_signature<T>::type>;

#define MSVC_FUNCTION_POINTER_DEDUCTION_GUIDE(CALL_OPT, X1, X2, X3) \
	template <class Result, class... Args>                          \
	function(Result(CALL_OPT*)(Args...)) -> function<Result(Args...)>;

	MSVC_NON_MEMBER_CALL(MSVC_FUNCTION_POINTER_DEDUCTION_GUIDE, X1, X2, X3)

#undef MSVC_FUNCTION_POINTER_DEDUCTION_GUIDE

	template <class T>
	[[nodiscard]] bool operator==(const function<T>& a_lhs, std::nullptr_t) noexcept
	{
		return !a_lhs;
	}

	template <class T>
	[[nodiscard]] bool operator==(std::nullptr_t, const function<T>& a_rhs) noexcept
	{
		return !a_rhs;
	}

	template <class T>
	void swap(function<T>& a_lhs, function<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

namespace msvc
{
	template <class T>
	class function_old
		: public detail::get_function_impl_old<T>::type
	{
	private:
		using base_type = detail::get_function_impl_old<T>::type;

	public:
		function_old() noexcept = default;

		function_old(std::nullptr_t) noexcept
		{
		}

		template <class Func, base_type::template enable_if_callable_t<T, Func> = 0>
		function_old(Func&& a_func) // NOLINT(bugprone-forwarding-reference-overload)
		{
			static_assert(std::is_copy_constructible_v<std::decay_t<Func>>,
				"The target function object type must be copy constructible.");

			base_type::reset(std::forward<Func>(a_func));
		}

		function_old(const function_old& a_rhs)
		{
			base_type::reset_copy(a_rhs);
		}

		function_old(function_old&& a_rhs) noexcept
		{
			base_type::reset_move(a_rhs);
		}

		function_old& operator=(std::nullptr_t) noexcept
		{
			base_type::reset();
			return *this;
		}

		template <class Func>
		function_old& operator=(std::reference_wrapper<Func> a_func) noexcept
		{
			base_type::reset();
			base_type::reset(a_func);
			return *this;
		}

		template <class Func, base_type::template enable_if_callable_t<T, Func> = 0>
		function_old& operator=(Func&& a_func)
		{
			base_type::reset(std::forward<Func>(a_func));
			return *this;
		}

		function_old& operator=(const function_old& a_rhs)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			base_type::reset();
			base_type::reset_copy(a_rhs);
			return *this;
		}

		function_old& operator=(function_old&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			base_type::reset();
			base_type::reset_move(a_rhs);
			return *this;
		}

		[[nodiscard]] explicit operator bool() const noexcept
		{
			return !base_type::empty();
		}

		void swap(function_old& a_other) noexcept
		{
			base_type::swap(a_other);
		}

		[[nodiscard]] const msvc::type_info& target_type() const noexcept
		{
			return base_type::target_type();
		}

		[[nodiscard]] T* target() noexcept
		{
			if constexpr (std::is_function_v<T>) {
				return nullptr;
			}
			else {
				// NOLINTNEXTLINE(bugprone-casting-through-void)
				return reinterpret_cast<T*>(const_cast<void*>(base_type::target(typeid(T))));
			}
		}

#if _MSC_VER > 0l
#pragma warning(push)
#pragma warning(disable : 4180) // qualifier applied to function type has no meaning; ignored
#endif

		[[nodiscard]] const T* target() const noexcept
		{
			if constexpr (std::is_function_v<T>) {
				return nullptr;
			}
			else {
				// NOLINTNEXTLINE(bugprone-casting-through-void)
				return reinterpret_cast<const T*>(base_type::target(typeid(T)));
			}
		}

#if _MSC_VER > 0l
#pragma warning(pop)
#endif
	};
	static_assert(sizeof(msvc::function_old<void()>) == 0x20);

	template <class T>
	function_old(T) -> function_old<typename detail::deduce_signature<T>::type>;

#define MSVC_FUNCTION_POINTER_DEDUCTION_GUIDE(CALL_OPT, X1, X2, X3) \
	template <class Result, class... Args>                          \
	function_old(Result(CALL_OPT*)(Args...)) -> function_old<Result(Args...)>;

	MSVC_NON_MEMBER_CALL(MSVC_FUNCTION_POINTER_DEDUCTION_GUIDE, X1, X2, X3)

#undef MSVC_FUNCTION_POINTER_DEDUCTION_GUIDE

	template <class T>
	[[nodiscard]] bool operator==(const function_old<T>& a_lhs, std::nullptr_t) noexcept
	{
		return !a_lhs;
	}

	template <class T>
	[[nodiscard]] bool operator==(std::nullptr_t, const function_old<T>& a_rhs) noexcept
	{
		return !a_rhs;
	}

	template <class T>
	void swap(function_old<T>& a_lhs, function_old<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}
