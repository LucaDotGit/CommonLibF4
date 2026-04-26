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

		constexpr hkPtrAndInt& operator=(const hkPtrAndInt&) noexcept = default;
		constexpr hkPtrAndInt& operator=(hkPtrAndInt&&) noexcept = default;

		// members
		std::uint64_t ptrAndInt; // 00
	};
	static_assert(sizeof(hkPtrAndInt<void, void, 0>) == 0x08);
}
