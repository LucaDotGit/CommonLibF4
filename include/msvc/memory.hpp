#pragma once

namespace msvc
{
	// NOLINTBEGIN(modernize-avoid-c-arrays)

	template <class T>
	struct default_delete;

	template <class T, class Deleter = default_delete<T>>
	class unique_ptr;
}

namespace msvc::detail
{
	// struct `std::_Get_deleter_pointer_type`
	template <class T, class Deleter, class = void>
	struct _deleter_pointer_type
	{
		using type = std::add_pointer_t<std::remove_extent_t<T>>;
	};

	template <class T, class Deleter>
	struct _deleter_pointer_type<T, Deleter, std::void_t<typename Deleter::pointer>>
	{
		using type = Deleter::pointer;
	};

	template <class T, class Deleter>
	using deleter_pointer_type = _deleter_pointer_type<T, std::remove_reference_t<Deleter>>;

	template <class T, class Deleter>
	using deleter_pointer_type_t = deleter_pointer_type<T, Deleter>::type;

	// class `std::_Unique_ptr_base`
	template <class T, class Deleter, class = void>
	class unique_ptr
	{
	public:
		using pointer = deleter_pointer_type_t<T, Deleter>;
		using deleter_type = Deleter;

		template <class... Args>
		constexpr unique_ptr(pointer a_ptr, Args... a_args) noexcept //
			requires(std::is_nothrow_constructible_v<deleter_type, Args...>)
			: _pointer(a_ptr),
			  _deleter(std::forward<Args>(a_args)...)
		{
		}

		constexpr unique_ptr(unique_ptr&& a_rhs) noexcept //
			requires(std::is_nothrow_move_constructible_v<deleter_type>)
			: _pointer(std::move(a_rhs._pointer)),
			  _deleter(std::move(a_rhs._deleter))
		{
			a_rhs._pointer = pointer();
		}

		template <class U, class E>
		constexpr unique_ptr(unique_ptr<U, E>&& a_rhs) noexcept // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			requires(std::is_reference_v<E> &&
						std::is_nothrow_constructible_v<deleter_type, const E&>)
			: _pointer(std::move(a_rhs._pointer)),
			  _deleter(a_rhs._deleter)
		{
			a_rhs._pointer = typename unique_ptr<U, E>::pointer();
		}

		template <class U, class E>
		constexpr unique_ptr(unique_ptr<U, E>&& a_rhs) noexcept // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			requires(!std::is_reference_v<E> &&
						std::is_nothrow_constructible_v<deleter_type, E &&>)
			: _pointer(std::move(a_rhs._pointer)),
			  _deleter(std::move(a_rhs._deleter))
		{
			a_rhs._pointer = typename unique_ptr<U, E>::pointer();
		}

		[[nodiscard]] constexpr deleter_type& get_deleter() noexcept { return _deleter; }
		[[nodiscard]] constexpr const deleter_type& get_deleter() const noexcept { return _deleter; }

	protected:
		// members
		pointer _pointer; // 00

	private:
		template <class, class, class>
		friend class unique_ptr;

		// members
		deleter_type _deleter; // 08
	};

	template <class T, class Deleter>
	class unique_ptr<T, Deleter,
		std::enable_if_t<
			std::disjunction_v<
				std::is_empty<
					Deleter>,
				std::is_same<
					default_delete<T>,
					Deleter>>>> : public Deleter
	{
	private:
		using super = Deleter;

	public:
		using pointer = deleter_pointer_type_t<T, Deleter>;
		using deleter_type = Deleter;

		template <class... Args>
		constexpr unique_ptr(pointer a_ptr, Args... a_args) noexcept //
			requires(std::is_nothrow_constructible_v<deleter_type, Args...>)
			: super(std::forward<Args>(a_args)...),
			  _pointer(a_ptr)
		{
		}

		constexpr unique_ptr(unique_ptr&& a_rhs) noexcept //
			requires(std::is_nothrow_move_constructible_v<deleter_type>)
			: super(std::move(a_rhs)),
			  _pointer(std::move(a_rhs._pointer))
		{
			a_rhs._pointer = pointer();
		}

		template <class U, class E>
		constexpr unique_ptr(unique_ptr<U, E>&& a_rhs) noexcept // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			requires(std::is_reference_v<E> &&
						std::is_nothrow_constructible_v<deleter_type, const E&>)
			: super(a_rhs),
			  _pointer(std::move(a_rhs._pointer))
		{
			a_rhs._pointer = typename unique_ptr<U, E>::pointer();
		}

		template <class U, class E>
		constexpr unique_ptr(unique_ptr<U, E>&& a_rhs) noexcept //
			requires(!std::is_reference_v<E> &&
						std::is_nothrow_constructible_v<deleter_type, E &&>)
			: super(std::move(a_rhs)),
			  _pointer(std::move(a_rhs._pointer))
		{
			a_rhs._pointer = typename unique_ptr<U, E>::pointer();
		}

		[[nodiscard]] constexpr deleter_type& get_deleter() noexcept { return *this; }
		[[nodiscard]] constexpr const deleter_type& get_deleter() const noexcept { return *this; }

	protected:
		// members
		pointer _pointer; // 00

	private:
		template <class, class, class>
		friend class unique_ptr;
	};
}

namespace msvc
{
	template <class T>
	struct default_delete
	{
	public:
		constexpr default_delete() noexcept = default;

		template <class U>
		constexpr default_delete([[maybe_unused]] const default_delete<U>& a_deleter) noexcept //
			requires(std::is_convertible_v<U*, T*>)
		{
		}

		constexpr void operator()(T* a_ptr) const { delete a_ptr; }
	};

	template <class T>
	struct default_delete<T[]>
	{
	public:
		constexpr default_delete() noexcept = default;

		template <class U>
		constexpr default_delete([[maybe_unused]] const default_delete<U[]>& a_deleter) noexcept //
			requires(std::is_convertible_v<U (*)[], T (*)[]>)
		{
		}

		template <class U>
		constexpr void operator()(U* a_ptr) const //
			requires(std::is_convertible_v<U (*)[], T (*)[]>)
		{
			delete[] a_ptr;
		}
	};

	template <class T, class Deleter>
	class unique_ptr
		: public detail::unique_ptr<T, Deleter>
	{
	private:
		using super = detail::unique_ptr<T, Deleter>;
		using super::_pointer;

	public:
		using pointer = super::pointer;
		using element_type = T;
		using deleter_type = super::deleter_type;

		constexpr unique_ptr() noexcept //
			requires(std::is_nothrow_default_constructible_v<deleter_type> &&
					 !std::is_pointer_v<deleter_type>)
			: super(pointer())
		{
		}

		constexpr ~unique_ptr() noexcept
		{
			if (_pointer) {
				std::invoke(get_deleter(), _pointer);
			}
		}

		constexpr unique_ptr(std::nullptr_t) noexcept //
			requires(std::is_nothrow_default_constructible_v<deleter_type> &&
					 !std::is_pointer_v<deleter_type>)
			: super(pointer())
		{
		}

		constexpr explicit unique_ptr(pointer a_ptr) noexcept //
			requires(std::is_nothrow_default_constructible_v<deleter_type> &&
					 !std::is_pointer_v<deleter_type>)
			: super(a_ptr)
		{
		}

		constexpr unique_ptr(pointer a_ptr, const deleter_type& a_dtor) noexcept //
			requires(!std::is_reference_v<deleter_type> &&
					 std::is_nothrow_copy_constructible_v<deleter_type>)
			: super(a_ptr, a_dtor)
		{
		}

		constexpr unique_ptr(pointer a_ptr, deleter_type&& a_dtor) noexcept //
			requires(!std::is_reference_v<deleter_type> &&
					 std::is_nothrow_move_constructible_v<deleter_type>)
			: super(a_ptr, std::move(a_dtor))
		{
		}

		constexpr unique_ptr(pointer a_ptr, deleter_type& a_dtor) noexcept //
			requires(std::is_lvalue_reference_v<deleter_type> &&
					 !std::is_const_v<deleter_type>)
			: super(a_ptr, a_dtor)
		{
		}

		constexpr unique_ptr(pointer, deleter_type&&) //
			requires(std::is_lvalue_reference_v<deleter_type> &&
						!std::is_const_v<deleter_type>)
		= delete;

		constexpr unique_ptr(pointer a_ptr, const deleter_type& a_dtor) noexcept //
			requires(std::is_lvalue_reference_v<deleter_type> &&
					 std::is_const_v<deleter_type>)
			: super(a_ptr, a_dtor)
		{
		}

		constexpr unique_ptr(pointer, const deleter_type&&) //
			requires(std::is_lvalue_reference_v<deleter_type> &&
						std::is_const_v<deleter_type>)
		= delete;

		constexpr unique_ptr(unique_ptr&& a_rhs) noexcept //
			requires(std::is_nothrow_move_constructible_v<deleter_type>)
			: super(std::move(a_rhs))
		{
		}

		template <class U, class E>
		constexpr unique_ptr(unique_ptr<U, E>&& a_rhs) noexcept //
			requires(std::is_convertible_v<typename unique_ptr<U, E>::pointer, pointer> &&
					 !std::is_array_v<U> &&
					 std::same_as<E, deleter_type> &&
					 (std::is_reference_v<deleter_type> ?
							 std::is_nothrow_constructible_v<deleter_type, const E&> :
							 std::is_nothrow_constructible_v<deleter_type, E &&>))
			: super(std::move(a_rhs))
		{
		}

		constexpr unique_ptr& operator=(unique_ptr&& a_rhs) noexcept //
			requires((std::is_reference_v<deleter_type> ?
							 std::is_nothrow_copy_assignable_v<std::remove_reference_t<deleter_type>> :
							 std::is_nothrow_move_assignable_v<deleter_type>) &&
					 std::is_move_assignable_v<deleter_type>)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			reset(a_rhs.release());
			get_deleter() = std::forward<deleter_type>(a_rhs.get_deleter());
			return *this;
		}

		template <class U, class E>
		constexpr unique_ptr& operator=(unique_ptr<U, E>&& a_rhs) noexcept // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			requires((std::is_reference_v<deleter_type> ?
							 std::is_nothrow_copy_assignable_v<std::remove_reference_t<deleter_type>> :
							 std::is_nothrow_move_assignable_v<deleter_type>) &&
					 !std::is_array_v<U> &&
					 std::is_convertible_v<typename unique_ptr<U, E>::pointer, pointer> &&
					 std::is_assignable_v<deleter_type, E &&>)
		{
			reset(a_rhs.release());
			get_deleter() = std::forward<E>(a_rhs.get_deleter());
			return *this;
		}

		constexpr unique_ptr& operator=(std::nullptr_t) noexcept
		{
			reset();
			return *this;
		}

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return good(); }

		[[nodiscard]] constexpr auto operator*() const
			-> std::add_lvalue_reference_t<T>
		{
			REX::Assert(good());
			return *get();
		}

		[[nodiscard]] constexpr pointer operator->() const noexcept
		{
			REX::Assert(good());
			return get();
		}

		[[nodiscard]] constexpr pointer get() const noexcept
		{
			return _pointer;
		}

		constexpr pointer release() noexcept
		{
			auto old = _pointer;
			_pointer = pointer();
			return old;
		}

		constexpr void reset(pointer a_ptr = pointer()) noexcept
		{
			auto old = _pointer;
			_pointer = a_ptr;

			if (old) {
				std::invoke(get_deleter(), old);
			}
		}

		constexpr void swap(unique_ptr& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_pointer, a_other._pointer);
			std::swap(get_deleter(), a_other.get_deleter());
		}

		using super::get_deleter;

	private:
		[[nodiscard]] constexpr bool good() const noexcept { return get() != pointer(); }
	};
}

namespace msvc::detail
{
	template <class T, class Ptr>
	concept unique_ptr_array_convertible =
		std::same_as<T, typename Ptr::pointer> ||
		std::same_as<T, std::nullptr_t> ||
		(std::same_as<typename Ptr::pointer, typename Ptr::element_type*> &&
			std::is_pointer_v<T> &&
			std::same_as<std::remove_pointer_t<T> (*)[], typename Ptr::element_type (*)[]>);
}

namespace msvc
{
	template <class T, class Deleter>
	class unique_ptr<T[], Deleter>
		: public detail::unique_ptr<T[], Deleter>
	{
	private:
		using super = detail::unique_ptr<T[], Deleter>;
		using super::_pointer;

	public:
		using pointer = super::pointer;
		using element_type = T;
		using deleter_type = super::deleter_type;

		constexpr unique_ptr() noexcept //
			requires(std::is_nothrow_default_constructible_v<deleter_type> &&
					 !std::is_pointer_v<deleter_type>)
			: super(pointer())
		{
		}

		constexpr ~unique_ptr() noexcept
		{
			if (_pointer) {
				std::invoke(get_deleter(), _pointer);
			}
		}

		constexpr unique_ptr(std::nullptr_t) noexcept //
			requires(std::is_nothrow_default_constructible_v<deleter_type> &&
					 !std::is_pointer_v<deleter_type>)
			: super(pointer())
		{
		}

		template <class U>
		explicit unique_ptr(U a_ptr) noexcept //
			requires(std::is_nothrow_default_constructible_v<deleter_type> &&
					 !std::is_pointer_v<deleter_type> &&
					 detail::unique_ptr_array_convertible<U, unique_ptr>)
			: super(a_ptr)
		{
		}

		template <class U>
		constexpr unique_ptr(U a_ptr, const deleter_type& a_dtor) noexcept //
			requires(!std::is_reference_v<deleter_type> &&
					 std::is_nothrow_copy_constructible_v<deleter_type> &&
					 detail::unique_ptr_array_convertible<U, unique_ptr>)
			: super(a_ptr, a_dtor)
		{
		}

		template <class U>
		constexpr unique_ptr(U a_ptr, deleter_type&& a_dtor) noexcept //
			requires(!std::is_reference_v<deleter_type> &&
					 std::is_nothrow_move_constructible_v<deleter_type> &&
					 detail::unique_ptr_array_convertible<U, unique_ptr>)
			: super(a_ptr, std::move(a_dtor))
		{
		}

		template <class U>
		constexpr unique_ptr(U a_ptr, deleter_type& a_dtor) noexcept //
			requires(std::is_lvalue_reference_v<deleter_type> &&
					 !std::is_const_v<deleter_type> &&
					 detail::unique_ptr_array_convertible<U, unique_ptr>)
			: super(a_ptr, a_dtor)
		{
		}

		template <class U>
		constexpr unique_ptr(U, deleter_type&&) noexcept //
			requires(std::is_lvalue_reference_v<deleter_type> &&
						!std::is_const_v<deleter_type> &&
						detail::unique_ptr_array_convertible<U, unique_ptr>)
		= delete;

		template <class U>
		constexpr unique_ptr(U a_ptr, const deleter_type& a_dtor) noexcept //
			requires(std::is_lvalue_reference_v<deleter_type> &&
					 std::is_const_v<deleter_type> &&
					 detail::unique_ptr_array_convertible<U, unique_ptr>)
			: super(a_ptr, a_dtor)
		{
		}

		template <class U>
		constexpr unique_ptr(U, const deleter_type&&) noexcept //
			requires(std::is_lvalue_reference_v<deleter_type> &&
						std::is_const_v<deleter_type> &&
						detail::unique_ptr_array_convertible<U, unique_ptr>)
		= delete;

		constexpr unique_ptr(unique_ptr&& a_rhs) noexcept //
			requires(std::is_nothrow_move_constructible_v<deleter_type>)
			: super(std::move(a_rhs))
		{
		}

		template <class U, class E>
		constexpr unique_ptr(unique_ptr<U, E>&& a_rhs) noexcept //
			requires(std::is_array_v<U> &&
					 std::same_as<pointer, element_type*> &&
					 std::same_as<typename unique_ptr<U, E>::pointer, typename unique_ptr<U, E>::element_type*> &&
					 std::is_convertible_v<typename unique_ptr<U, E>::element_type (*)[], element_type (*)[]> &&
					 (std::is_reference_v<deleter_type> ?
							 std::same_as<E, deleter_type> && std::is_nothrow_constructible_v<deleter_type, const E&> :
							 std::is_convertible_v<E, deleter_type> && std::is_nothrow_constructible_v<deleter_type, E &&>))
			: super(std::move(a_rhs))
		{
		}

		constexpr unique_ptr& operator=(unique_ptr&& a_rhs) noexcept //
			requires((std::is_reference_v<deleter_type> ?
							 std::is_nothrow_copy_assignable_v<std::remove_reference_t<deleter_type>> :
							 std::is_nothrow_move_assignable_v<deleter_type>) &&
					 std::is_move_assignable_v<deleter_type>)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			reset(a_rhs.release());
			get_deleter() = std::forward<deleter_type>(a_rhs.get_deleter());
			return *this;
		}

		template <class U, class E>
		constexpr unique_ptr& operator=(unique_ptr<U, E>&& a_rhs) noexcept // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			requires(std::is_array_v<U> &&
					 std::same_as<pointer, element_type*> &&
					 std::same_as<typename unique_ptr<U, E>::pointer, typename unique_ptr<U, E>::element_type*> &&
					 std::is_convertible_v<typename unique_ptr<U, E>::element_type (*)[], element_type (*)[]> &&
					 std::is_assignable_v<deleter_type&, E &&>)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			reset(a_rhs.release());
			get_deleter() = std::forward<E>(a_rhs.get_deleter());
			return *this;
		}

		constexpr unique_ptr& operator=(std::nullptr_t) noexcept
		{
			reset();
			return *this;
		}

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return good(); }

		[[nodiscard]] constexpr element_type& operator[](std::size_t a_pos) const
		{
			REX::Assert(good());
			return get()[a_pos];
		}

		[[nodiscard]] constexpr pointer get() const noexcept
		{
			return _pointer;
		}

		constexpr void reset(std::nullptr_t = nullptr) noexcept
		{
			reset(pointer());
		}

		constexpr pointer release() noexcept
		{
			auto old = _pointer;
			_pointer = pointer();
			return old;
		}

		template <class U>
		constexpr void reset(U a_ptr) noexcept //
			requires(detail::unique_ptr_array_convertible<U, unique_ptr>)
		{
			auto old = _pointer;
			_pointer = a_ptr;

			if (old) {
				std::invoke(get_deleter(), old);
			}
		}

		constexpr void swap(unique_ptr& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_pointer, a_other._pointer);
			std::swap(get_deleter(), a_other.get_deleter());
		}

		using super::get_deleter;

	private:
		[[nodiscard]] constexpr bool good() const noexcept { return get() != pointer(); }
	};
	static_assert(sizeof(msvc::unique_ptr<std::any>) == 0x08);

	template <class T, class... Args>
	[[nodiscard]] constexpr unique_ptr<T> make_unique(Args&&... a_args) //
		requires(!std::is_array_v<T>)
	{
		return unique_ptr<T>{ new T(std::forward<Args>(a_args)...) };
	}

	template <class T>
	[[nodiscard]] constexpr unique_ptr<T> make_unique(std::size_t a_size) //
		requires(std::is_unbounded_array_v<T>)
	{
		return unique_ptr<T>{ new std::remove_extent_t<T>[a_size]() };
	}

	template <class T, class... Args>
	constexpr void make_unique(Args&&...) //
		requires(std::is_bounded_array_v<T>)
	= delete;

	template <class T, class... Args>
	[[nodiscard]] constexpr unique_ptr<T> make_unique_for_overwrite() //
		requires(!std::is_array_v<T>)
	{
		return unique_ptr<T>{ new T };
	}

	template <class T>
	[[nodiscard]] constexpr unique_ptr<T> make_unique_for_overwrite(std::size_t a_size) //
		requires(std::is_unbounded_array_v<T>)
	{
		return unique_ptr<T>{ new std::remove_extent_t<T>[a_size] };
	}

	template <class T, class... Args>
	constexpr void make_unique_for_overwrite(Args&&...) //
		requires(std::is_bounded_array_v<T>)
	= delete;

	template <class T1, class D1, class T2, class D2>
	[[nodiscard]] constexpr bool operator==(const unique_ptr<T1, D1>& a_lhs, const unique_ptr<T2, D2>& a_rhs)
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T1, class D1, class T2, class D2>
	[[nodiscard]] constexpr auto operator<=>(const unique_ptr<T1, D1>& a_lhs, const unique_ptr<T2, D2>& a_rhs)
		-> std::compare_three_way_result_t<
			typename unique_ptr<T1, D1>::pointer,
			typename unique_ptr<T2, D2>::pointer>
		requires(std::three_way_comparable_with<
			typename unique_ptr<T1, D1>::pointer,
			typename unique_ptr<T2, D2>::pointer>)
	{
		return a_lhs.get() <=> a_rhs.get();
	}

	template <class T, class D>
	[[nodiscard]] constexpr bool operator==(const unique_ptr<T, D>& a_lhs, std::nullptr_t) noexcept
	{
		return !a_lhs;
	}

	template <class T, class D>
	[[nodiscard]] constexpr auto operator<=>(const unique_ptr<T, D>& a_lhs, std::nullptr_t)
		-> std::compare_three_way_result_t<typename unique_ptr<T, D>::pointer>
		requires(std::three_way_comparable<typename unique_ptr<T, D>::pointer>)
	{
		return a_lhs.get() <=> nullptr;
	}

	template <class T, class Deleter>
	constexpr void swap(unique_ptr<T, Deleter>& a_lhs, unique_ptr<T, Deleter>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	// NOLINTEND(modernize-avoid-c-arrays)
}
