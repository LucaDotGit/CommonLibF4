#pragma once

#include "REX/Concepts.hpp"
#include "REX/Exception.hpp"
#include "REX/Localization.hpp"

namespace REX::Impl
{
	// Source: https://prng.di.unimi.it/xoroshiro128starstar.c, https://prng.di.unimi.it/xoshiro256starstar.c

	template <REX::integer T>
	using XoshiroStarStar_State = std::array<T, 4>;

	template <REX::integer T>
	[[nodiscard]]
	constexpr auto XoshiroStarStar_Generate(XoshiroStarStar_State<T>& a_state) noexcept -> T;

	template <>
	constexpr auto XoshiroStarStar_Generate(XoshiroStarStar_State<std::uint32_t>& a_state) noexcept -> std::uint32_t
	{
		const auto result = std::rotl(a_state[1] * 5, 7) * 9;
		const auto temp = a_state[1] << 9;

		a_state[2] ^= a_state[0];
		a_state[3] ^= a_state[1];
		a_state[1] ^= a_state[2];
		a_state[0] ^= a_state[3];

		a_state[2] ^= temp;
		a_state[3] = std::rotl(a_state[3], 11);

		return result;
	}

	template <>
	constexpr auto XoshiroStarStar_Generate(XoshiroStarStar_State<std::uint64_t>& a_state) noexcept -> std::uint64_t
	{
		const auto result = std::rotl(a_state[1] * 5, 7) * 9;
		const auto temp = a_state[1] << 17;

		a_state[2] ^= a_state[0];
		a_state[3] ^= a_state[1];
		a_state[1] ^= a_state[2];
		a_state[0] ^= a_state[3];

		a_state[2] ^= temp;
		a_state[3] = std::rotl(a_state[3], 45);

		return result;
	}

	template <REX::integer T>
	using SplitMix_State = T;

	// Source: https://en.wikipedia.org/wiki/Xorshift#Initialization

	constexpr auto SplitMix64(SplitMix_State<std::uint64_t>& a_state) noexcept -> std::uint64_t
	{
		auto result = (a_state += 0x9E37'79B9'7F4A'7C15);
		result = (result ^ (result >> 30)) * 0xBF58'476D'1CE4'E5B9;
		result = (result ^ (result >> 27)) * 0x94D0'49BB'1331'11EB;
		return result ^ (result >> 31);
	}

	template <REX::integer T>
	constexpr void XorShift_Setup(XoshiroStarStar_State<T>& a_state, T a_seed) noexcept;

	template <>
	constexpr void XorShift_Setup(XoshiroStarStar_State<std::uint32_t>& a_state, std::uint32_t a_seed) noexcept
	{
		auto splitMixState = std::bit_cast<SplitMix_State<std::uint64_t>>(static_cast<std::uint64_t>(a_seed));

		const auto splitMixValue01 = SplitMix64(splitMixState);
		a_state[0] = static_cast<std::uint32_t>(splitMixValue01 & std::numeric_limits<std::uint32_t>::max());
		a_state[1] = static_cast<std::uint32_t>(splitMixValue01 >> 32);

		const auto splitMixValue02 = SplitMix64(splitMixState);
		a_state[2] = static_cast<std::uint32_t>(splitMixValue02 & std::numeric_limits<std::uint32_t>::max());
		a_state[3] = static_cast<std::uint32_t>(splitMixValue02 >> 32);
	}

	template <>
	constexpr void XorShift_Setup(XoshiroStarStar_State<std::uint64_t>& a_state, std::uint64_t a_seed) noexcept
	{
		auto splitMixState = std::bit_cast<SplitMix_State<std::uint64_t>>(a_seed);

		a_state[0] = SplitMix64(splitMixState);
		a_state[1] = SplitMix64(splitMixState);
		a_state[2] = SplitMix64(splitMixState);
		a_state[3] = SplitMix64(splitMixState);
	}
}

namespace REX
{
	template <REX::integer T>
	class XoshiroStarStarEngine final
	{
	public:
		using result_type = T;

		inline static constexpr auto DEFAULT_SEED = static_cast<result_type>(0);

		constexpr XoshiroStarStarEngine() noexcept
		{
			Impl::XorShift_Setup(_state, DEFAULT_SEED);
		}

		constexpr explicit XoshiroStarStarEngine(result_type a_seed) noexcept
		{
			Impl::XorShift_Setup(_state, a_seed);
		}

		constexpr ~XoshiroStarStarEngine() noexcept = default;

		constexpr XoshiroStarStarEngine(const XoshiroStarStarEngine&) noexcept = default;
		constexpr XoshiroStarStarEngine(XoshiroStarStarEngine&&) noexcept = default;

		constexpr auto operator=(const XoshiroStarStarEngine&) noexcept -> XoshiroStarStarEngine& = default;
		constexpr auto operator=(XoshiroStarStarEngine&&) noexcept -> XoshiroStarStarEngine& = default;

		[[nodiscard]]
		static constexpr auto min() noexcept -> result_type
		{
			return std::numeric_limits<result_type>::min();
		}

		[[nodiscard]]
		static constexpr auto max() noexcept -> result_type
		{
			return std::numeric_limits<result_type>::max();
		}

		[[nodiscard]]
		constexpr auto operator()() noexcept -> result_type
		{
			return Impl::XoshiroStarStar_Generate(_state);
		}

		[[nodiscard]]
		constexpr auto state() noexcept -> auto&
		{
			return _state;
		}

		[[nodiscard]]
		constexpr auto state() const noexcept -> const auto&
		{
			return _state;
		}

		constexpr void seed() noexcept
		{
			Impl::XorShift_Setup(_state, DEFAULT_SEED);
		}

		constexpr void seed(result_type a_seed) noexcept
		{
			Impl::XorShift_Setup(_state, a_seed);
		}

		constexpr void discard(std::size_t a_count) noexcept
		{
			for (auto i = static_cast<std::size_t>(0); i < a_count; i++) {
				std::ignore = Impl::XoshiroStarStar_Generate(_state);
			}
		}

	private:
		Impl::XoshiroStarStar_State<result_type> _state{};
	};

	using XoshiroStarStarEngine32 = XoshiroStarStarEngine<std::uint32_t>;
	static_assert(std::uniform_random_bit_generator<XoshiroStarStarEngine32>);

	using XoshiroStarStarEngine64 = XoshiroStarStarEngine<std::uint64_t>;
	static_assert(std::uniform_random_bit_generator<XoshiroStarStarEngine64>);

	static_assert([]() consteval noexcept -> bool {
		auto state = XoshiroStarStarEngine32(123'456'789);

		auto values = std::array<std::uint32_t, 6>();
		for (auto& value : values) {
			value = std::invoke(state);
		}

		return values == std::array{
							 static_cast<std::uint32_t>(0x5045'157D),
							 static_cast<std::uint32_t>(0xABCA'7E60),
							 static_cast<std::uint32_t>(0x6DBB'078E),
							 static_cast<std::uint32_t>(0xF035'7E1E),
							 static_cast<std::uint32_t>(0xD935'A07F),
							 static_cast<std::uint32_t>(0x241C'386E)
						 };
	}());

	static_assert([]() consteval noexcept -> bool {
		auto state = XoshiroStarStarEngine64(123'456'789);

		auto values = std::array<std::uint64_t, 6>();
		for (auto& value : values) {
			value = std::invoke(state);
		}

		return values == std::array{
							 static_cast<std::uint64_t>(0xD1EE'A10C'836F'0CC2),
							 static_cast<std::uint64_t>(0xE1BB'9DFA'08F0'2548),
							 static_cast<std::uint64_t>(0x1503'F3B7'26A1'B888),
							 static_cast<std::uint64_t>(0x88BF'5A02'2CF9'D5C2),
							 static_cast<std::uint64_t>(0xDE0F'231C'2690'6FE1),
							 static_cast<std::uint64_t>(0x7BF1'4DF7'468F'6BD5)
						 };
	}());
}

namespace REX
{
	using SeedGenerator = std::random_device;

	using RandomEngine32 = REX::XoshiroStarStarEngine32;
	using RandomEngine64 = REX::XoshiroStarStarEngine64;

	using BoolDistributor = std::bernoulli_distribution;

	template <REX::integer T>
	using IntDistributor = std::uniform_int_distribution<T>;

	template <REX::floating_point T>
	using FloatDistributor = std::uniform_real_distribution<T>;

	template <REX::integer T>
	[[nodiscard]]
	auto RandomSeed() noexcept -> T
	{
		using seeder_result_type = SeedGenerator::result_type;

		const auto seed = REX::TryCatch<std::exception>(
			[]() -> seeder_result_type {
				auto seeder = SeedGenerator();
				return std::invoke(seeder);
			},
			[](const std::exception& a_error) noexcept -> seeder_result_type {
				std::ignore = a_error;
				return static_cast<seeder_result_type>(std::chrono::steady_clock::now().time_since_epoch().count());
			});

		auto engine = RandomEngine32(static_cast<std::uint32_t>(seed));
		auto distributor = IntDistributor<T>();
		return std::invoke(distributor, engine);
	}

	template <std::uniform_random_bit_generator T>
	[[nodiscard]]
	auto NextBool(T& a_engine) noexcept -> bool
	{
		auto distributor = BoolDistributor();
		return std::invoke(distributor, a_engine);
	}

	template <REX::integer U, std::uniform_random_bit_generator T>
	[[nodiscard]]
	auto NextInt(T& a_engine, U a_minInclusive, U a_maxInclusive) noexcept -> U
	{
		auto distributor = IntDistributor<U>(a_minInclusive, a_maxInclusive);
		return std::invoke(distributor, a_engine);
	}

	template <REX::floating_point U, std::uniform_random_bit_generator T>
	[[nodiscard]]
	auto NextFloat(T& a_engine, U a_minInclusive, U a_maxExclusive) noexcept -> U
	{
		auto distributor = FloatDistributor<U>(a_minInclusive, a_maxExclusive);
		return std::invoke(distributor, a_engine);
	}

	template <REX::character CharT, std::uniform_random_bit_generator T>
	[[nodiscard]]
	auto NextChar(T& a_engine) noexcept -> CharT
	{
		constexpr const auto& ALPHANUMERIC_CHARACTERS = REX::ALPHANUMERIC_CHARACTERS<CharT>;

		auto distributor = IntDistributor<std::size_t>(0, ALPHANUMERIC_CHARACTERS.size() - 1);
		const auto index = std::invoke(distributor, a_engine);
		return ALPHANUMERIC_CHARACTERS[index];
	}

	template <REX::character CharT, std::uniform_random_bit_generator T>
	[[nodiscard]]
	auto NextChar(T& a_engine, std::span<const CharT> a_characters) noexcept -> CharT
	{
		auto distributor = IntDistributor<std::size_t>(0, a_characters.size() - 1);
		const auto index = std::invoke(distributor, a_engine);
		return a_characters[index];
	}

	template <REX::character CharT, std::uniform_random_bit_generator T>
	[[nodiscard]]
	auto NextAlphanumericChar(T& a_engine) noexcept -> CharT
	{
		constexpr const auto& ALPHANUMERIC_CHARACTERS = REX::ALPHANUMERIC_CHARACTERS<CharT>;

		auto distributor = IntDistributor<std::size_t>(0, ALPHANUMERIC_CHARACTERS.size() - 1);
		const auto index = std::invoke(distributor, a_engine);
		return ALPHANUMERIC_CHARACTERS[index];
	}

	template <REX::character CharT, std::uniform_random_bit_generator T>
	[[nodiscard]]
	auto NextString(T& a_engine, std::size_t a_size, std::basic_string_view<CharT> a_characters)
		-> std::basic_string<CharT>
	{
		auto distributor = IntDistributor<std::size_t>(0, a_characters.size() - 1);

		auto result = std::basic_string<CharT>();
		result.reserve(a_size);

		for (auto i = static_cast<std::size_t>(0); i < a_size; i++) {
			const auto index = std::invoke(distributor, a_engine);
			result.push_back(a_characters[index]);
		}

		return result;
	}

	template <REX::character CharT, std::uniform_random_bit_generator T>
	[[nodiscard]]
	auto NextAlphanumericString(T& a_engine, std::size_t a_size) -> std::basic_string<CharT>
	{
		constexpr const auto& ALPHANUMERIC_CHARACTERS = REX::ALPHANUMERIC_CHARACTERS<CharT>;

		auto distributor = IntDistributor<std::size_t>(0, ALPHANUMERIC_CHARACTERS.size() - 1);

		auto result = std::basic_string<CharT>();
		result.reserve(a_size);

		for (auto i = static_cast<std::size_t>(0); i < a_size; i++) {
			const auto index = std::invoke(distributor, a_engine);
			result.push_back(ALPHANUMERIC_CHARACTERS[index]);
		}

		return result;
	}
}

namespace REX::Impl
{
	template <class T, class CharT>
	concept input_stream_readable = requires(T& a_value, std::basic_istream<CharT>& a_stream) {
		{
			a_stream >> a_value
		} -> std::same_as<std::basic_istream<CharT>&>;
	};

	template <class T, class CharT>
	concept output_stream_writable = requires(const T& a_value, std::basic_ostream<CharT>& a_stream) {
		{
			a_stream << a_value
		} -> std::same_as<std::basic_ostream<CharT>&>;
	};

	template <class T>
	concept seedable = requires(T& a_value, T::result_type a_seed) {
		{
			a_value.seed()
		} noexcept;
		{
			a_value.seed(a_seed)
		} noexcept;
	};

	template <class T>
	concept discardable = requires(T& a_value, std::size_t a_count) {
		{
			a_value.discard(a_count)
		} noexcept;
	};
}

namespace REX
{
	template <std::uniform_random_bit_generator T>
	class BasicRandom final
	{
	public:
		using value_type = T;

		BasicRandom() noexcept(std::is_nothrow_constructible_v<value_type, typename value_type::result_type>) :
			_engine(RandomSeed<typename value_type::result_type>())
		{
		}

		explicit BasicRandom(value_type::result_type a_seed)
			noexcept(std::is_nothrow_constructible_v<value_type, typename value_type::result_type>) :
			_engine(a_seed)
		{
		}

		~BasicRandom() noexcept = default;

		BasicRandom(const BasicRandom&) = default;
		BasicRandom(BasicRandom&&) noexcept = default;

		auto operator=(const BasicRandom&) -> BasicRandom& = default;
		auto operator=(BasicRandom&&) noexcept -> BasicRandom& = default;

		[[nodiscard]]
		auto operator==(const BasicRandom& a_rhs) const noexcept -> bool
			requires(REX::equality_comparable<value_type>)
		{
			return _engine == a_rhs._engine;
		}

		[[nodiscard]]
		static auto GetShared() noexcept(std::is_nothrow_default_constructible_v<BasicRandom>) -> BasicRandom&
		{
			static thread_local auto Instance = BasicRandom();
			return Instance;
		}

		[[nodiscard]]
		auto GetEngine() noexcept -> auto&
		{
			return _engine;
		}

		[[nodiscard]]
		auto GetEngine() const noexcept -> const auto&
		{
			return _engine;
		}

		void Reseed() noexcept
			requires(Impl::seedable<value_type>)
		{
			_engine.seed(RandomSeed<typename value_type::result_type>());
		}

		void Reseed(value_type::result_type a_seed) noexcept
			requires(Impl::seedable<value_type>)
		{
			_engine.seed(a_seed);
		}

		template <REX::character CharT>
		[[nodiscard]]
		auto LoadState() const -> std::basic_string<CharT>
			requires(Impl::output_stream_writable<value_type, CharT>)
		{
			auto stringStream = std::basic_ostringstream<CharT>();
			stringStream << _engine;
			return stringStream.str();
		}

		template <REX::character CharT>
		void SaveState(std::basic_string_view<CharT> a_state)
			requires(Impl::input_stream_readable<value_type, CharT>)
		{
			auto stringStream = std::basic_istringstream<CharT>(std::basic_string<CharT>(a_state));
			stringStream >> _engine;
		}

		template <REX::character CharT>
		void SaveState(std::basic_string<CharT>&& a_state)
			requires(Impl::input_stream_readable<value_type, CharT>)
		{
			auto stringStream = std::basic_istringstream<CharT>(std::move(a_state));
			stringStream >> _engine;
		}

		template <REX::character CharT>
		void Deserialize(std::basic_istream<CharT>& a_stream)
			requires(Impl::input_stream_readable<value_type, CharT>)
		{
			a_stream >> _engine;
		}

		template <REX::character CharT>
		void Serialize(std::basic_ostream<CharT>& a_stream) const
			requires(Impl::output_stream_writable<value_type, CharT>)
		{
			a_stream << _engine;
		}

		void Discard(std::size_t a_count) noexcept
			requires(Impl::discardable<value_type>)
		{
			_engine.discard(a_count);
		}

		[[nodiscard]]
		auto NextBool() noexcept -> bool
		{
			return REX::NextBool(_engine);
		}

		template <REX::integer U>
		[[nodiscard]]
		auto NextInt() noexcept -> U
		{
			return NextInt<U>(static_cast<U>(0), std::numeric_limits<U>::max());
		}

		template <REX::integer U>
		[[nodiscard]]
		auto NextInt(U a_maxInclusive) noexcept -> U
		{
			return NextInt<U>(static_cast<U>(0), a_maxInclusive);
		}

		template <REX::integer U>
		[[nodiscard]]
		auto NextInt(U a_minInclusive, U a_maxInclusive) noexcept -> U
		{
			return REX::NextInt<U>(_engine, a_minInclusive, a_maxInclusive);
		}

		template <REX::floating_point U>
		[[nodiscard]]
		auto NextFloat() noexcept -> U
		{
			return NextFloat<U>(static_cast<U>(0), static_cast<U>(1));
		}

		template <REX::floating_point U>
		[[nodiscard]]
		auto NextFloat(U a_maxInclusive) noexcept -> U
		{
			return NextFloat<U>(static_cast<U>(0), a_maxInclusive);
		}

		template <REX::floating_point U>
		[[nodiscard]]
		auto NextFloat(U a_minInclusive, U a_maxExclusive) noexcept -> U
		{
			return REX::NextFloat<U>(_engine, a_minInclusive, a_maxExclusive);
		}

		template <REX::character CharT>
		[[nodiscard]]
		auto NextChar() noexcept -> CharT
		{
			return REX::NextChar<CharT>(_engine);
		}

		template <REX::character CharT>
		[[nodiscard]]
		auto NextChar(std::span<const CharT> a_characters) noexcept -> CharT
		{
			if (a_characters.empty()) {
				return static_cast<CharT>(0);
			}

			return REX::NextChar<CharT>(_engine, a_characters);
		}

		template <REX::character CharT>
		[[nodiscard]]
		auto NextAlphanumericChar() noexcept -> CharT
		{
			return REX::NextAlphanumericChar<CharT>(_engine);
		}

		template <REX::character CharT>
		[[nodiscard]]
		auto NextString(std::size_t a_size, std::basic_string_view<CharT> a_characters) -> std::basic_string<CharT>
		{
			if (a_size == 0 || a_characters.empty()) {
				return {};
			}

			return REX::NextString<CharT>(_engine, a_size, a_characters);
		}

		template <REX::character CharT>
		[[nodiscard]]
		auto NextAlphanumericString(std::size_t a_size) -> std::basic_string<CharT>
		{
			if (a_size == 0) {
				return {};
			}

			return REX::NextAlphanumericString<CharT>(_engine, a_size);
		}

		template <std::random_access_iterator It>
		[[nodiscard]]
		auto NextElement(It a_begin, It a_end) noexcept -> It
		{
			const auto size = std::distance(a_begin, a_end);
			if (size == 0) {
				return a_end;
			}

			const auto index = REX::NextInt<std::size_t>(_engine, 0, size - 1);
			return std::next(a_begin, index);
		}

		template <std::ranges::random_access_range Range>
		[[nodiscard]]
		auto NextElement(Range& a_range) noexcept -> std::ranges::iterator_t<Range>
		{
			auto begin = std::ranges::begin(a_range);
			auto end = std::ranges::end(a_range);

			const auto size = std::ranges::distance(begin, end);
			if (size == 0) {
				return end;
			}

			const auto index = REX::NextInt<std::size_t>(_engine, 0, size - 1);
			return std::next(begin, index);
		}

		template <std::ranges::random_access_range Range>
		[[nodiscard]]
		auto NextElement(const Range& a_range) noexcept -> std::ranges::const_iterator_t<Range>
		{
			const auto begin = std::ranges::begin(a_range);
			const auto end = std::ranges::end(a_range);

			const auto size = std::ranges::distance(begin, end);
			if (size == 0) {
				return end;
			}

			const auto index = REX::NextInt<std::size_t>(_engine, 0, size - 1);
			return std::next(begin, index);
		}

		template <std::random_access_iterator It>
		void NextRange(It a_begin, It a_end) noexcept
		{
			if (a_begin == a_end) {
				return;
			}

			std::shuffle(a_begin, a_end, _engine);
		}

		template <std::ranges::random_access_range Range>
		void NextRange(Range& a_range) noexcept
		{
			const auto begin = std::ranges::begin(a_range);
			const auto end = std::ranges::end(a_range);

			if (begin == end) {
				return;
			}

			std::ranges::shuffle(a_range, _engine);
		}

		template <REX::character CharT>
		[[nodiscard]]
		auto ToString() const -> std::basic_string<CharT>
			requires(Impl::output_stream_writable<value_type, CharT>)
		{
			auto stringStream = std::basic_ostringstream<CharT>();
			stringStream << _engine;
			return stringStream.str();
		}

		void swap(BasicRandom& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_engine, a_other._engine);
		}

	private:
		value_type _engine;
	};

	using Random32 = BasicRandom<REX::RandomEngine32>;
	using Random64 = BasicRandom<REX::RandomEngine64>;
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <std::uniform_random_bit_generator T>
		requires(REX::Impl::output_stream_writable<T, char>)
	struct formatter<REX::BasicRandom<T>> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REX::BasicRandom<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.template LoadState<char>());
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <std::uniform_random_bit_generator T>
		requires(REX::Impl::output_stream_writable<T, char>)
	struct formatter<REX::BasicRandom<T>> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REX::BasicRandom<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.template LoadState<char>());
		}
	};
}
#endif
