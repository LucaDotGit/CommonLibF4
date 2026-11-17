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

		constexpr explicit BSUntypedPointerHandle(value_type a_handle) noexcept :
			_handle(a_handle)
		{
		}

		constexpr BSUntypedPointerHandle(const BSUntypedPointerHandle&) noexcept = default;
		constexpr BSUntypedPointerHandle(BSUntypedPointerHandle&&) noexcept = default;

		constexpr auto operator=(const BSUntypedPointerHandle&) noexcept -> BSUntypedPointerHandle& = default;
		constexpr auto operator=(BSUntypedPointerHandle&&) noexcept -> BSUntypedPointerHandle& = default;

		constexpr auto operator=(value_type a_handle) noexcept -> BSUntypedPointerHandle&
		{
			_handle = a_handle;
			return *this;
		}

		[[nodiscard]]
		constexpr explicit operator bool() const noexcept
		{
			return has_value();
		}

		[[nodiscard]]
		constexpr auto has_value() const noexcept -> bool
		{
			return _handle > static_cast<value_type>(0);
		}

		[[nodiscard]]
		constexpr auto value() const noexcept -> value_type
		{
			return _handle;
		}

		constexpr void reset() noexcept
		{
			_handle = static_cast<value_type>(0);
		}

		constexpr void swap(BSUntypedPointerHandle& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_handle, a_other._handle);
		}

	private:
		// members
		value_type _handle{0}; // 0x00
	};

	static_assert(sizeof(BSUntypedPointerHandle<>) == 0x04);

	static_assert(std::is_trivially_destructible_v<BSUntypedPointerHandle<>>);
	static_assert(std::is_trivially_copyable_v<BSUntypedPointerHandle<>>);
	static_assert(std::is_trivially_move_constructible_v<BSUntypedPointerHandle<>>);

	template <std::uint32_t FreeListBits, std::uint32_t AgeShift>
	[[nodiscard]]
	constexpr auto operator==(
		const BSUntypedPointerHandle<FreeListBits, AgeShift>& a_lhs,
		const BSUntypedPointerHandle<FreeListBits, AgeShift>& a_rhs) noexcept -> bool
	{
		return a_lhs.value() == a_rhs.value();
	}

	template <std::uint32_t FreeListBits, std::uint32_t AgeShift>
	[[nodiscard]]
	constexpr auto operator<=>(
		const BSUntypedPointerHandle<FreeListBits, AgeShift>& a_lhs,
		const BSUntypedPointerHandle<FreeListBits, AgeShift>& a_rhs) noexcept
	{
		return a_lhs.value() <=> a_rhs.value();
	}
}

namespace std
{
	template <std::uint32_t FreeListBits, std::uint32_t AgeShift>
	struct hash<RE::BSUntypedPointerHandle<FreeListBits, AgeShift>>
	{
	public:
		[[nodiscard]]
		auto operator()(const RE::BSUntypedPointerHandle<FreeListBits, AgeShift>& a_key) const noexcept -> std::size_t
		{
			return REX::Hash(a_key.value());
		}
	};
}
