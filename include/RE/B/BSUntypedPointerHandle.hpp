#pragma once

namespace RE
{
	template <std::uint32_t = 21, std::uint32_t = 5>
	class BSUntypedPointerHandle;

	template <std::uint32_t FreeListBits, std::uint32_t AgeShift>
	class BSUntypedPointerHandle
	{
	public:
		inline static constexpr auto FREE_LIST_BITS = FreeListBits;
		inline static constexpr auto AGE_SHIFT = AgeShift;

		using value_type = std::uint32_t;

		constexpr BSUntypedPointerHandle() noexcept = default;
		constexpr ~BSUntypedPointerHandle() noexcept = default;

		constexpr BSUntypedPointerHandle(const BSUntypedPointerHandle&) noexcept = default;
		constexpr BSUntypedPointerHandle(BSUntypedPointerHandle&&) noexcept = default;

		constexpr BSUntypedPointerHandle(value_type a_handle) noexcept
			: _handle(a_handle)
		{
		}

		constexpr BSUntypedPointerHandle& operator=(const BSUntypedPointerHandle&) noexcept = default;
		constexpr BSUntypedPointerHandle& operator=(BSUntypedPointerHandle&&) noexcept = default;

		constexpr BSUntypedPointerHandle& operator=(value_type a_handle) noexcept
		{
			_handle = a_handle;
			return *this;
		}

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return has_value(); }
		[[nodiscard]] constexpr bool has_value() const noexcept { return _handle > static_cast<value_type>(0); }

		[[nodiscard]] constexpr value_type value() const noexcept { return _handle; }

		constexpr void reset() noexcept { _handle = static_cast<value_type>(0); }

		constexpr void swap(BSUntypedPointerHandle& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_handle, a_other._handle);
		}

	private:
		// members
		value_type _handle{ 0 }; // 00
	};
	static_assert(sizeof(BSUntypedPointerHandle<>) == 0x04);

	extern template class BSUntypedPointerHandle<>;

	static_assert(std::is_trivially_destructible_v<BSUntypedPointerHandle<>>);
	static_assert(std::is_trivially_copyable_v<BSUntypedPointerHandle<>>);

	template <std::uint32_t FreeListBits, std::uint32_t AgeShift>
	[[nodiscard]] constexpr bool operator==(const BSUntypedPointerHandle<FreeListBits, AgeShift>& a_lhs, const BSUntypedPointerHandle<FreeListBits, AgeShift>& a_rhs) noexcept
	{
		return a_lhs.value() == a_rhs.value();
	}

	template <std::uint32_t FreeListBits, std::uint32_t AgeShift>
	[[nodiscard]] constexpr auto operator<=>(const BSUntypedPointerHandle<FreeListBits, AgeShift>& a_lhs, const BSUntypedPointerHandle<FreeListBits, AgeShift>& a_rhs) noexcept
	{
		return a_lhs.value() <=> a_rhs.value();
	}

	extern template bool operator==(const BSUntypedPointerHandle<>&, const BSUntypedPointerHandle<>&) noexcept;
	extern template auto operator<=>(const BSUntypedPointerHandle<>&, const BSUntypedPointerHandle<>&) noexcept;

	template <std::uint32_t FreeListBits, std::uint32_t AgeShift>
	constexpr void swap(BSUntypedPointerHandle<FreeListBits, AgeShift>& a_lhs, BSUntypedPointerHandle<FreeListBits, AgeShift>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	extern template void swap(BSUntypedPointerHandle<>&, BSUntypedPointerHandle<>&) noexcept;
}

namespace std
{
	template <std::uint32_t FreeListBits, std::uint32_t AgeShift>
	struct hash<RE::BSUntypedPointerHandle<FreeListBits, AgeShift>>
	{
	public:
		[[nodiscard]] std::size_t operator()(const RE::BSUntypedPointerHandle<FreeListBits, AgeShift>& a_key) const noexcept
		{
			return REX::Hash(a_key.value());
		}
	};

	extern template struct hash<RE::BSUntypedPointerHandle<>>;
}
