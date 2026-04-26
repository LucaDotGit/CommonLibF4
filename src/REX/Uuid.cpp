#include "REX/Uuid.hpp"

#include "REX/Random.hpp"

namespace REX::Impl
{
	// Source: https://www.ietf.org/rfc/rfc4122.txt
	[[nodiscard]] static Uuid::container_type FromSeed(REX::Random64::value_type::result_type a_seed) noexcept
	{
		static_assert(sizeof(std::uint64_t) * 2 == Uuid::BYTE_COUNT);

		auto random = REX::Random64(a_seed);
		auto bytes = Uuid::container_type();

		const auto lowPart = random.NextInt<std::uint64_t>();
		const auto highPart = random.NextInt<std::uint64_t>();

		reinterpret_cast<std::uint64_t*>(bytes.data())[0] = lowPart;
		reinterpret_cast<std::uint64_t*>(bytes.data())[1] = highPart;

		constexpr auto TIME_HIGH_AND_VERSION_INDEX = static_cast<std::size_t>(6);
		constexpr auto CLOCK_SEQ_HIGH_AND_RESERVED_INDEX = static_cast<std::size_t>(8);

		constexpr auto VERSION_MASK = 0xF0ui32;
		constexpr auto RANDOM_VERSION = 0x40ui32;

		constexpr auto VARIANT_MASK = 0xC0ui32;
		constexpr auto RANDOM_VARIANT = 0x80ui32;

		bytes[TIME_HIGH_AND_VERSION_INDEX] = (bytes[TIME_HIGH_AND_VERSION_INDEX] & ~VERSION_MASK) | RANDOM_VERSION;
		bytes[CLOCK_SEQ_HIGH_AND_RESERVED_INDEX] = (bytes[CLOCK_SEQ_HIGH_AND_RESERVED_INDEX] & ~VARIANT_MASK) | RANDOM_VARIANT;

		return bytes;
	}
}

namespace REX
{
	Uuid Uuid::Generate() noexcept
	{
		const auto seed = REX::RandomSeed<REX::Random64::value_type::result_type>();
		const auto bytes = Impl::FromSeed(seed);
		return { bytes };
	}

	static_assert([]() consteval noexcept {
		constexpr auto UUID_01 = "62470f2d-f92b-4189-8af6-157310dadc8b"sv;
		constexpr auto UUID_02 = std::array<const Uuid::value_type, Uuid::BYTE_COUNT>{
			0x62, 0x47, 0x0F, 0x2D, 0xF9, 0x2B, 0x41, 0x89, 0x8A, 0xF6, 0x15, 0x73, 0x10, 0xDA, 0xDC, 0x8B
		};

		return Uuid::FromString(UUID_01) == Uuid::FromArray(UUID_02);
	}());

	static_assert([]() consteval noexcept {
		constexpr auto UUID_01 = "62470f2d-f92b-4189-8af6-157310dadc8b"sv;
		constexpr auto UUID_02 = Uuid::FromString(UUID_01);

		return UUID_02 && UUID_02->ToString() == UUID_01;
	}());
}
