#pragma once

#include "msvc/type_info.hpp"
#include "msvc/type_traits.hpp"

namespace msvc::detail
{
	inline constexpr auto STORAGE_SIZE =
		static_cast<std::size_t>((msvc::detail::SMALL_OBJECT_PTR_COUNT - 1) * sizeof(std::uintptr_t));
	inline constexpr auto STORAGE_SIZE_OLD =
		static_cast<std::size_t>((msvc::detail::SMALL_OBJECT_PTR_COUNT_OLD - 1) * sizeof(std::uintptr_t));

	template <class T>
	concept large_object = sizeof(T) > STORAGE_SIZE ||
						   alignof(T) > alignof(std::max_align_t) ||
						   !std::is_nothrow_move_constructible_v<T>;

	template <class T>
	concept large_object_old = sizeof(T) > STORAGE_SIZE_OLD ||
							   alignof(T) > alignof(std::max_align_t) ||
							   !std::is_nothrow_move_constructible_v<T>;

	template <class T>
	concept testable_callable = requires(T a_callable) { std::invoke(a_callable); };

	[[nodiscard]]
	inline auto get_small_object_ptr_count() noexcept -> std::size_t
	{
		if (F4SE::IsRuntimeAtLeastNG()) {
			return msvc::detail::SMALL_OBJECT_PTR_COUNT;
		}

		return msvc::detail::SMALL_OBJECT_PTR_COUNT_OLD;
	}

	template <class T>
	[[nodiscard]]
	auto is_large_object() noexcept -> bool
	{
		if (F4SE::IsRuntimeAtLeastNG()) {
			return large_object<T>;
		}

		return large_object_old<T>;
	}

	template <class T>
	[[nodiscard]]
	auto do_test_callable(const T& a_callable) noexcept -> bool
	{
		if constexpr (testable_callable<T>) {
			return !!a_callable;
		}
		else {
			return true;
		}
	}

	template <class T, class... Args>
	[[nodiscard]]
	auto global_new(Args&&... a_args) -> T*
	{
		class guard_type
		{
		public:
			explicit guard_type(T* a_ptr) noexcept :
				_ptr(a_ptr)
			{
			}

			~guard_type() noexcept
			{
				if (_ptr) {
					std::allocator<T>().deallocate(_ptr, 1);
				}
			}

			guard_type(const guard_type&) = delete;
			guard_type(guard_type&&) = delete;

			auto operator=(const guard_type&) -> guard_type& = delete;
			auto operator=(guard_type&&) -> guard_type& = delete;

			[[nodiscard]]
			auto get() const noexcept -> T*
			{
				return _ptr;
			}

			[[nodiscard]]
			auto release() noexcept -> T*
			{
				return std::exchange(_ptr, nullptr);
			}

		private:
			T* _ptr{nullptr};
		};

		auto guard = guard_type(std::allocator<T>().allocate(1));
		std::construct_at(guard.get(), std::forward<Args>(a_args)...);
		return guard.release();
	}
}

namespace msvc::detail
{
	// struct std::_Deduce_from_call_operator
	template <class Func, class CallOperator, class = void>
	struct deduce_from_call_operator : public msvc::is_member_function_ptr<CallOperator>::_Guide_type
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
	struct deduce_from_call_operator<Func, CallOperator, std::void_t<decltype(std::declval<Func>()())>> :
		public inspect_static_call_operator<CallOperator>
	{
	};

	// struct std::_Deduce_signature
	template <class Func, class = void>
	struct deduce_signature
	{
	};

	template <class Func>
	struct deduce_signature<Func, std::void_t<decltype(&Func::operator())>> :
		public deduce_from_call_operator<Func, decltype(&Func::operator())>
	{
	};
}
