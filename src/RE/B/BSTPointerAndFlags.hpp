#pragma once

namespace RE
{
	template <class T, std::uintptr_t MASK = 1>
	class BSTPointerAndFlags
	{
	public:
		inline static constexpr auto FLAG_MASK = MASK;

		using value_type = T;
		using element_type = T::element_type;

		constexpr BSTPointerAndFlags() noexcept = default;

		constexpr ~BSTPointerAndFlags() noexcept
		{
			reset();
		}

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr BSTPointerAndFlags(std::nullptr_t) noexcept :
			_storage(0)
		{
		}

		constexpr BSTPointerAndFlags(const BSTPointerAndFlags& a_rhs) noexcept :
			_storage(a_rhs._storage)
		{
		}

		constexpr BSTPointerAndFlags(BSTPointerAndFlags&& a_rhs) noexcept :
			_storage(std::move(a_rhs._storage))
		{
		}

		constexpr auto operator=(const BSTPointerAndFlags& a_rhs) noexcept -> BSTPointerAndFlags&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			clear_flags();

			_storage.ptr = a_rhs._storage.ptr;

			return *this;
		}

		constexpr auto operator=(BSTPointerAndFlags&& a_rhs) noexcept -> BSTPointerAndFlags&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			clear_flags();
			a_rhs.clear_flags();

			_storage.ptr = std::move(a_rhs._storage.ptr);

			return *this;
		}

		[[nodiscard]]
		constexpr explicit operator bool() const noexcept
		{
			return get() != nullptr;
		}

		[[nodiscard]]
		constexpr auto operator*() const noexcept -> element_type&
		{
			REX::Assert(static_cast<bool>(*this));
			return *get();
		}

		[[nodiscard]]
		constexpr auto operator->() const noexcept -> element_type*
		{
			return get();
		}

		[[nodiscard]]
		constexpr auto get() const noexcept -> element_type*
		{
			return std::bit_cast<element_type*>(_storage.address & ~FLAG_MASK);
		}

		constexpr void reset() noexcept
		{
			clear_flags();

			_storage.ptr.reset();
			_storage.address = 0;
		}

	private:
		constexpr void clear_flags() noexcept
		{
			_storage.address &= ~FLAG_MASK;
		}

		union Storage
		{
		public:
			// members
			value_type ptr;
			std::uintptr_t address{0};
		};

		// members
		Storage _storage; // 0x00
	};
}
