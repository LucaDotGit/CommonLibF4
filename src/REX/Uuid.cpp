#include "REX/Uuid.hpp"

#include "REX/Random.hpp"

namespace REX::Impl
{
	namespace
	{
		[[nodiscard]]
		auto FromSeed(REX::Random64::value_type::result_type a_seed) noexcept -> Uuid::container_type
		{
			// Source: https://ietf.org/rfc/rfc4122.txt

			auto random = REX::Random64(a_seed);
			auto bytes = Uuid::container_type();

			auto buffer = Uuid::container_type();
			random.NextRange(buffer);

			constexpr auto TIME_HIGH_AND_VERSION_INDEX = static_cast<std::size_t>(6);
			constexpr auto CLOCK_SEQ_HIGH_AND_RESERVED_INDEX = static_cast<std::size_t>(8);

			constexpr auto VERSION_MASK = static_cast<std::uint32_t>(0xF0);
			constexpr auto RANDOM_VERSION = static_cast<std::uint32_t>(0x40);

			constexpr auto VARIANT_MASK = static_cast<std::uint32_t>(0xC0);
			constexpr auto RANDOM_VARIANT = static_cast<std::uint32_t>(0x80);

			bytes[TIME_HIGH_AND_VERSION_INDEX] = (bytes[TIME_HIGH_AND_VERSION_INDEX] & ~VERSION_MASK) | RANDOM_VERSION;
			bytes[CLOCK_SEQ_HIGH_AND_RESERVED_INDEX] =
				(bytes[CLOCK_SEQ_HIGH_AND_RESERVED_INDEX] & ~VARIANT_MASK) | RANDOM_VARIANT;

			return bytes;
		}
	}
}

namespace REX
{
	auto Uuid::Generate() noexcept -> Uuid
	{
		const auto seed = REX::RandomSeed<REX::Random64::value_type::result_type>();
		const auto bytes = Impl::FromSeed(seed);
		return Uuid(bytes);
	}
}
