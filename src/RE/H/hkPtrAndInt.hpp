#pragma once

namespace RE
{
	template <class, class, std::size_t>
	class hkPtrAndInt
	{
	public:
		constexpr hkPtrAndInt() noexcept = default;
		constexpr ~hkPtrAndInt() noexcept = default;

		constexpr hkPtrAndInt(const hkPtrAndInt&) noexcept = default;
		constexpr hkPtrAndInt(hkPtrAndInt&&) noexcept = default;

		constexpr auto operator=(const hkPtrAndInt&) noexcept -> hkPtrAndInt& = default;
		constexpr auto operator=(hkPtrAndInt&&) noexcept -> hkPtrAndInt& = default;

		// members
		std::uint64_t ptrAndInt; // 0x00
	};

	static_assert(sizeof(hkPtrAndInt<void, void, 0>) == 0x08);
}
