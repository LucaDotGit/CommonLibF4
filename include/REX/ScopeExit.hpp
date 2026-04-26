#pragma once

namespace REX
{
	template <class T>
	class ScopeExit final
	{
	public:
		using value_type = T;

		static_assert(std::is_invocable_v<std::remove_reference_t<value_type>>,
			"`REX::ScopeExit` requires an invocable type.");

		template <class F>
		constexpr explicit ScopeExit(F&& a_func) //
			noexcept(std::is_nothrow_constructible_v<value_type, F> ||
					 std::is_nothrow_constructible_v<value_type, F&>)
			requires(!std::same_as<std::remove_cvref_t<F>, ScopeExit> &&
					 std::is_constructible_v<value_type, F> &&
					 std::is_invocable_v<F>)
		{
			if constexpr (!std::is_lvalue_reference_v<F> &&
						  std::is_nothrow_constructible_v<value_type, F>) {
				_func.emplace(std::forward<F>(a_func));
			}
			else {
				_func.emplace(a_func);
			}
		}

		constexpr ~ScopeExit() //
			noexcept(std::is_nothrow_invocable_v<value_type>)
		{
			if (_func) {
				std::invoke(*_func);
			}
		}

		constexpr ScopeExit(const ScopeExit&) = delete;

		constexpr ScopeExit(ScopeExit&& a_rhs) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type> ||
					 std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type> ||
					 std::is_move_constructible_v<value_type>)
		{
			if (!a_rhs) {
				return;
			}

			if constexpr (std::is_nothrow_move_constructible_v<value_type>) {
				_func.emplace(std::forward<value_type>(*a_rhs._func));
			}
			else {
				_func.emplace(a_rhs._func);
			}

			a_rhs.release();
		}

		constexpr ScopeExit& operator=(const ScopeExit&) = delete;
		constexpr ScopeExit& operator=(ScopeExit&&) = delete;

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return static_cast<bool>(_func); }

		constexpr void release() noexcept { _func.reset(); }

	private:
		std::optional<std::remove_reference_t<value_type>> _func;
	};

	template <class T>
	ScopeExit(T) -> ScopeExit<T>;
}
