#include "REX/Random.hpp"

namespace REX::Impl
{
	static_assert([]() consteval noexcept {
		auto state = XoshiroStarStarEngine32(123456789);

		auto values = std::array<std::uint32_t, 6>();
		for (auto& value : values) {
			value = std::invoke(state);
		}

		return values == std::array{
			0x5045157Dui32,
			0xABCA7E60ui32,
			0x6DBB078Eui32,
			0xF0357E1Eui32,
			0xD935A07Fui32,
			0x241C386Eui32
		};
	}());

	static_assert([]() consteval noexcept {
		auto state = XoshiroStarStarEngine64(123456789);

		auto values = std::array<std::uint64_t, 6>();
		for (auto& value : values) {
			value = std::invoke(state);
		}

		return values == std::array{
			0xD1EEA10C836F0CC2ui64,
			0xE1BB9DFA08F02548ui64,
			0x1503F3B726A1B888ui64,
			0x88BF5A022CF9D5C2ui64,
			0xDE0F231C26906FE1ui64,
			0x7BF14DF7468F6BD5ui64
		};
	}());
}

namespace REX
{
	template class XoshiroStarStarEngine<std::uint32_t>;
	template class XoshiroStarStarEngine<std::uint64_t>;

	static_assert(std::uniform_random_bit_generator<XoshiroStarStarEngine32>);
	static_assert(std::uniform_random_bit_generator<XoshiroStarStarEngine64>);

	template std::uint32_t RandomSeed<std::uint32_t>() noexcept;
	template std::uint64_t RandomSeed<std::uint64_t>() noexcept;

	template class BasicRandom<Impl::default_random_engine_32>;
	template class BasicRandom<Impl::default_random_engine_64>;

	auto GetSharedRandom32() noexcept
		-> const REX::NotNull<std::unique_ptr<Random32>>&
	{
		thread_local static const auto Instance = REX::NotNull(std::make_unique<Random32>());
		return Instance;
	}

	auto GetSharedRandom64() noexcept
		-> const REX::NotNull<std::unique_ptr<Random64>>&
	{
		thread_local static const auto Instance = REX::NotNull(std::make_unique<Random64>());
		return Instance;
	}
}
