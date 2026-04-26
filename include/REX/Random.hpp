#pragma once

#include "REX/Concepts.hpp"
#include "REX/NotNull.hpp"

namespace REX::Impl
{
	// Source: https://prng.di.unimi.it/xoroshiro128starstar.c, https://prng.di.unimi.it/xoshiro256starstar.c

	template <REX::integer T>
	class XoshiroStarStar_State final
	{
	public:
		std::array<T, 4> data;
	};

	template <REX::integer T>
	[[nodiscard]] constexpr T XoshiroStarStar_Generate(XoshiroStarStar_State<T>& a_state) noexcept;

	template <>
	constexpr std::uint32_t XoshiroStarStar_Generate(XoshiroStarStar_State<std::uint32_t>& a_state) noexcept
	{
		auto& state = a_state.data;

		const auto result = std::rotl(state[1] * 5, 7) * 9;
		const auto temp = state[1] << 9;

		state[2] ^= state[0];
		state[3] ^= state[1];
		state[1] ^= state[2];
		state[0] ^= state[3];

		state[2] ^= temp;
		state[3] = std::rotl(state[3], 11);

		return result;
	}

	template <>
	constexpr std::uint64_t XoshiroStarStar_Generate(XoshiroStarStar_State<std::uint64_t>& a_state) noexcept
	{
		auto& state = a_state.data;

		const auto result = std::rotl(state[1] * 5, 7) * 9;
		const auto temp = state[1] << 17;

		state[2] ^= state[0];
		state[3] ^= state[1];
		state[1] ^= state[2];
		state[0] ^= state[3];

		state[2] ^= temp;
		state[3] = std::rotl(state[3], 45);

		return result;
	}

	template <REX::integer T>
	class SplitMix_State final
	{
	public:
		T data;
	};

	// Source: https://en.wikipedia.org/wiki/Xorshift#Initialization

	constexpr std::uint64_t SplitMix64(SplitMix_State<std::uint64_t>& a_state) noexcept
	{
		auto result = (a_state.data += 0x9E3779B97F4A7C15);
		result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9;
		result = (result ^ (result >> 27)) * 0x94D049BB133111EB;
		return result ^ (result >> 31);
	}

	template <REX::integer T>
	constexpr void XorShift_Init(XoshiroStarStar_State<T>& a_state, T a_seed) noexcept;

	template <>
	constexpr void XorShift_Init(XoshiroStarStar_State<std::uint32_t>& a_state, std::uint32_t a_seed) noexcept
	{
		auto splitMixState = SplitMix_State<std::uint64_t>{ .data = static_cast<std::uint64_t>(a_seed) };

		const auto splitMixValue01 = SplitMix64(splitMixState);
		a_state.data[0] = static_cast<std::uint32_t>(splitMixValue01 & 0xFFFFFFFFui64);
		a_state.data[1] = static_cast<std::uint32_t>(splitMixValue01 >> 32);

		const auto splitMixValue02 = SplitMix64(splitMixState);
		a_state.data[2] = static_cast<std::uint32_t>(splitMixValue02 & 0xFFFFFFFFui64);
		a_state.data[3] = static_cast<std::uint32_t>(splitMixValue02 >> 32);
	}

	template <>
	constexpr void XorShift_Init(XoshiroStarStar_State<std::uint64_t>& a_state, std::uint64_t a_seed) noexcept
	{
		auto splitMixState = SplitMix_State<std::uint64_t>{ .data = a_seed };

		a_state.data[0] = SplitMix64(splitMixState);
		a_state.data[1] = SplitMix64(splitMixState);
		a_state.data[2] = SplitMix64(splitMixState);
		a_state.data[3] = SplitMix64(splitMixState);
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
			Impl::XorShift_Init(_state, DEFAULT_SEED);
		}

		constexpr explicit XoshiroStarStarEngine(result_type a_seed) noexcept
		{
			Impl::XorShift_Init(_state, a_seed);
		}

		constexpr ~XoshiroStarStarEngine() noexcept = default;

		constexpr XoshiroStarStarEngine(const XoshiroStarStarEngine&) noexcept = default;
		constexpr XoshiroStarStarEngine(XoshiroStarStarEngine&&) noexcept = default;

		constexpr XoshiroStarStarEngine& operator=(const XoshiroStarStarEngine&) noexcept = default;
		constexpr XoshiroStarStarEngine& operator=(XoshiroStarStarEngine&&) noexcept = default;

		[[nodiscard]] static constexpr result_type min() noexcept
		{
			return std::numeric_limits<result_type>::min();
		}

		[[nodiscard]] static constexpr result_type max() noexcept
		{
			return std::numeric_limits<result_type>::max();
		}

		[[nodiscard]] constexpr result_type operator()() noexcept
		{
			return Impl::XoshiroStarStar_Generate(_state);
		}

		[[nodiscard]] constexpr const auto& state() const noexcept
		{
			return _state;
		}

		[[nodiscard]] constexpr auto& state() noexcept
		{
			return _state;
		}

		constexpr void seed() noexcept
		{
			Impl::XorShift_Init(_state, DEFAULT_SEED);
		}

		constexpr void seed(result_type a_seed) noexcept
		{
			Impl::XorShift_Init(_state, a_seed);
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

	extern template class XoshiroStarStarEngine<std::uint32_t>;
	extern template class XoshiroStarStarEngine<std::uint64_t>;

	using XoshiroStarStarEngine32 = XoshiroStarStarEngine<std::uint32_t>;
	using XoshiroStarStarEngine64 = XoshiroStarStarEngine<std::uint64_t>;
}

namespace REX::Impl
{
	template <class T, class CharT>
	concept input_stream_readable = requires(T& a_value, std::basic_istream<CharT>& a_stream) {
		{ a_stream >> a_value } -> std::same_as<std::basic_istream<CharT>&>;
	};

	template <class T, class CharT>
	concept output_stream_writable = requires(const T& a_value, std::basic_ostream<CharT>& a_stream) {
		{ a_stream << a_value } -> std::same_as<std::basic_ostream<CharT>&>;
	};

	template <class T>
	concept seedable = requires(T& a_value, T::result_type a_seed) {
		{ a_value.seed() } noexcept;
		{ a_value.seed(a_seed) } noexcept;
	};

	template <class T>
	concept discardable = requires(T& a_value, std::size_t a_count) {
		{ a_value.discard(a_count) } noexcept;
	};

	using default_seed_generator = std::random_device;

	using default_random_engine_32 = XoshiroStarStarEngine32;
	using default_random_engine_64 = XoshiroStarStarEngine64;

	using default_bool_distribution = std::bernoulli_distribution;

	template <REX::integer T>
	using default_int_distribution = std::uniform_int_distribution<T>;

	template <REX::floating_point T>
	using default_float_distribution = std::uniform_real_distribution<T>;

	template <REX::win32_character T>
	inline constexpr auto ALPHANUMERIC_CHARACTERS =
		std::basic_string_view<T>();

	template <>
	inline constexpr auto ALPHANUMERIC_CHARACTERS<char> =
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"0123456789"sv;

	template <>
	inline constexpr auto ALPHANUMERIC_CHARACTERS<wchar_t> =
		L"abcdefghijklmnopqrstuvwxyz"
		L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		L"0123456789"sv;

	template <std::uniform_random_bit_generator T>
	[[nodiscard]] __forceinline bool NextBool(T& a_engine) noexcept
	{
		auto distributor = default_bool_distribution();
		return std::invoke(distributor, a_engine);
	}

	template <REX::integer U, std::uniform_random_bit_generator T>
	[[nodiscard]] __forceinline U NextInt(T& a_engine, U a_min, U a_max) noexcept
	{
		auto distributor = default_int_distribution<U>(a_min, a_max);
		return std::invoke(distributor, a_engine);
	}

	template <REX::floating_point U, std::uniform_random_bit_generator T>
	[[nodiscard]] __forceinline U NextFloat(T& a_engine, U a_min, U a_max) noexcept
	{
		auto distributor = default_float_distribution<U>(a_min, a_max);
		return std::invoke(distributor, a_engine);
	}

	template <REX::win32_character U, std::uniform_random_bit_generator T>
	[[nodiscard]] __forceinline U NextChar(T& a_engine) noexcept
	{
		constexpr const auto& ALPHANUMERIC_CHARACTERS = Impl::ALPHANUMERIC_CHARACTERS<U>;

		auto distributor = default_int_distribution<std::size_t>(0, ALPHANUMERIC_CHARACTERS.size() - 1);
		const auto index = std::invoke(distributor, a_engine);
		return ALPHANUMERIC_CHARACTERS[index];
	}

	template <REX::win32_character U, std::uniform_random_bit_generator T>
	[[nodiscard]] __forceinline U NextChar(T& a_engine, std::span<const U> a_characters) noexcept
	{
		auto distributor = default_int_distribution<std::size_t>(0, a_characters.size() - 1);
		const auto index = std::invoke(distributor, a_engine);
		return a_characters[index];
	}

	template <REX::win32_character U, std::uniform_random_bit_generator T>
	[[nodiscard]] __forceinline U NextAlphanumericChar(T& a_engine) noexcept
	{
		constexpr const auto& ALPHANUMERIC_CHARACTERS = Impl::ALPHANUMERIC_CHARACTERS<U>;

		auto distributor = default_int_distribution<std::size_t>(0, ALPHANUMERIC_CHARACTERS.size() - 1);
		const auto index = std::invoke(distributor, a_engine);
		return ALPHANUMERIC_CHARACTERS[index];
	}

	template <REX::win32_character U, std::uniform_random_bit_generator T>
	[[nodiscard]] __forceinline std::basic_string<U> NextString(T& a_engine, std::size_t a_size, std::basic_string_view<U> a_characters)
	{
		auto distributor = default_int_distribution<std::size_t>(0, a_characters.size() - 1);

		auto result = std::basic_string<U>();
		result.reserve(a_size);

		for (auto i = static_cast<std::size_t>(0); i < a_size; i++) {
			const auto index = std::invoke(distributor, a_engine);
			result.push_back(a_characters[index]);
		}

		return result;
	}

	template <REX::win32_character U, std::uniform_random_bit_generator T>
	[[nodiscard]] __forceinline std::basic_string<U> NextAlphanumericString(T& a_engine, std::size_t a_size)
	{
		constexpr const auto& ALPHANUMERIC_CHARACTERS = Impl::ALPHANUMERIC_CHARACTERS<U>;

		auto distributor = default_int_distribution<std::size_t>(0, ALPHANUMERIC_CHARACTERS.size() - 1);

		auto result = std::basic_string<U>();
		result.reserve(a_size);

		for (auto i = static_cast<std::size_t>(0); i < a_size; i++) {
			const auto index = std::invoke(distributor, a_engine);
			result.push_back(ALPHANUMERIC_CHARACTERS[index]);
		}

		return result;
	}
}

namespace REX
{
	template <REX::integer T>
	[[nodiscard]] T RandomSeed() noexcept
	{
		auto seeder = Impl::default_seed_generator();
		auto engine = Impl::default_random_engine_32(seeder());
		auto distributor = Impl::default_int_distribution<T>();
		return std::invoke(distributor, engine);
	}

	extern template std::uint32_t RandomSeed<std::uint32_t>() noexcept;
	extern template std::uint64_t RandomSeed<std::uint64_t>() noexcept;

	template <std::uniform_random_bit_generator T>
	class BasicRandom final
	{
	public:
		using value_type = T;

		BasicRandom()
			: _engine(RandomSeed<typename value_type::result_type>())
		{
		}

		explicit BasicRandom(value_type::result_type a_seed) noexcept
			: _engine(a_seed)
		{
		}

		~BasicRandom() noexcept = default;

		BasicRandom(const BasicRandom&) = default;
		BasicRandom(BasicRandom&&) noexcept = default;

		BasicRandom& operator=(const BasicRandom&) = default;
		BasicRandom& operator=(BasicRandom&&) noexcept = default;

		[[nodiscard]] bool operator==(const BasicRandom& a_rhs) const noexcept
			requires(REX::equality_comparable<T>)
		{
			return _engine == a_rhs._engine;
		}

		[[nodiscard]] bool operator!=(const BasicRandom& a_rhs) const noexcept
			requires(REX::equality_comparable<T>)
		{
			return !(*this == a_rhs);
		}

		[[nodiscard]] auto& GetEngine() noexcept
		{
			return _engine;
		}

		[[nodiscard]] const auto& GetEngine() const noexcept
		{
			return _engine;
		}

		void Reseed() noexcept
			requires(Impl::seedable<T>)
		{
			_engine.seed(RandomSeed<typename value_type::result_type>());
		}

		void Reseed(value_type::result_type a_seed) noexcept
			requires(Impl::seedable<T>)
		{
			_engine.seed(a_seed);
		}

		template <REX::win32_character U>
		[[nodiscard]] std::basic_string<U> LoadState() const
			requires(Impl::output_stream_writable<T, U>)
		{
			auto stringStream = std::basic_ostringstream<U>();
			stringStream << _engine;
			return stringStream.str();
		}

		template <REX::win32_character U>
		void SaveState(std::basic_string_view<U> a_state)
			requires(Impl::input_stream_readable<T, U>)
		{
			auto stringStream = std::basic_istringstream<U>(std::basic_string<U>(a_state));
			stringStream >> _engine;
		}

		template <REX::win32_character U>
		void SaveState(std::basic_string<U>&& a_state)
			requires(Impl::input_stream_readable<T, U>)
		{
			auto stringStream = std::basic_istringstream<U>(std::move(a_state));
			stringStream >> _engine;
		}

		template <REX::win32_character U>
		void Deserialize(std::basic_istream<U>& a_stream)
			requires(Impl::input_stream_readable<T, U>)
		{
			a_stream >> _engine;
		}

		template <REX::win32_character U>
		void Serialize(std::basic_ostream<U>& a_stream) const
			requires(Impl::output_stream_writable<T, U>)
		{
			a_stream << _engine;
		}

		void Discard(std::size_t a_count) noexcept
			requires(Impl::discardable<T>)
		{
			_engine.discard(a_count);
		}

		[[nodiscard]] bool NextBool() noexcept
		{
			return Impl::NextBool(_engine);
		}

		template <REX::integer U>
		[[nodiscard]] U NextInt() noexcept
		{
			return NextInt<U>(static_cast<U>(0), std::numeric_limits<U>::max());
		}

		template <REX::integer U>
		[[nodiscard]] U NextInt(U a_max) noexcept
		{
			return NextInt<U>(static_cast<U>(0), a_max);
		}

		template <REX::integer U>
		[[nodiscard]] U NextInt(U a_min, U a_max) noexcept
		{
			return Impl::NextInt<U>(_engine, a_min, a_max);
		}

		template <REX::floating_point U>
		[[nodiscard]] U NextFloat() noexcept
		{
			return NextFloat<U>(static_cast<U>(0), static_cast<U>(1));
		}

		template <REX::floating_point U>
		[[nodiscard]] U NextFloat(U a_max) noexcept
		{
			return NextFloat<U>(static_cast<U>(0), a_max);
		}

		template <REX::floating_point U>
		[[nodiscard]] U NextFloat(U a_min, U a_max) noexcept
		{
			return Impl::NextFloat<U>(_engine, a_min, a_max);
		}

		template <REX::win32_character U>
		[[nodiscard]] U NextChar() noexcept
		{
			return Impl::NextChar<U>(_engine);
		}

		template <REX::win32_character U>
		[[nodiscard]] U NextChar(std::span<const U> a_characters) noexcept
		{
			if (a_characters.empty()) {
				return static_cast<U>(0);
			}

			return Impl::NextChar<U>(_engine, a_characters);
		}

		template <REX::win32_character U>
		[[nodiscard]] U NextAlphanumericChar() noexcept
		{
			return Impl::NextAlphanumericChar<U>(_engine);
		}

		template <REX::win32_character U>
		[[nodiscard]] std::basic_string<U> NextString(std::size_t a_size, std::basic_string_view<U> a_characters)
		{
			if (a_size == 0 || a_characters.empty()) {
				return {};
			}

			return Impl::NextString<U>(_engine, a_size, a_characters);
		}

		template <REX::win32_character U>
		[[nodiscard]] std::basic_string<U> NextAlphanumericString(std::size_t a_size)
		{
			if (a_size == 0) {
				return {};
			}

			return Impl::NextAlphanumericString<U>(_engine, a_size);
		}

		template <std::random_access_iterator It>
		[[nodiscard]] It NextElement(It a_begin, It a_end) noexcept
		{
			const auto size = std::distance(a_begin, a_end);
			if (size == 0) {
				return a_end;
			}

			const auto index = Impl::NextInt<std::size_t>(_engine, 0, size - 1);
			return std::next(a_begin, index);
		}

		template <std::ranges::random_access_range Range>
		[[nodiscard]] auto NextElement(Range& a_range) noexcept -> std::ranges::iterator_t<Range>
		{
			auto begin = std::ranges::begin(a_range);
			auto end = std::ranges::end(a_range);

			const auto size = std::ranges::distance(begin, end);
			if (size == 0) {
				return end;
			}

			const auto index = Impl::NextInt<std::size_t>(_engine, 0, size - 1);
			return std::next(begin, index);
		}

		template <std::ranges::random_access_range Range>
		[[nodiscard]] auto NextElement(const Range& a_range) noexcept -> std::ranges::const_iterator_t<Range>
		{
			const auto begin = std::ranges::begin(a_range);
			const auto end = std::ranges::end(a_range);

			const auto size = std::ranges::distance(begin, end);
			if (size == 0) {
				return end;
			}

			const auto index = Impl::NextInt<std::size_t>(_engine, 0, size - 1);
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

		template <REX::character>
		[[nodiscard]] std::basic_string<T> ToString() const
			requires(Impl::output_stream_writable<T, T>)
		{
			auto stringStream = std::basic_ostringstream<T>();
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

	extern template class BasicRandom<Impl::default_random_engine_32>;
	extern template class BasicRandom<Impl::default_random_engine_64>;

	using Random32 = BasicRandom<Impl::default_random_engine_32>;
	using Random64 = BasicRandom<Impl::default_random_engine_64>;

	template <std::uniform_random_bit_generator T>
	void swap(BasicRandom<T>& a_lhs, BasicRandom<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	[[nodiscard]] auto GetSharedRandom32() noexcept -> const REX::NotNull<std::unique_ptr<Random32>>&;
	[[nodiscard]] auto GetSharedRandom64() noexcept -> const REX::NotNull<std::unique_ptr<Random64>>&;
}

#if __cpp_lib_format > 0l
namespace std
{
	template <std::uniform_random_bit_generator T>
		requires(REX::Impl::output_stream_writable<T, char>)
	struct formatter<REX::BasicRandom<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const REX::BasicRandom<T>& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "{}"sv, a_value.template LoadState<char>());
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <std::uniform_random_bit_generator T>
		requires(REX::Impl::output_stream_writable<T, char>)
	struct formatter<REX::BasicRandom<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const REX::BasicRandom<T>& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "{}"sv, a_value.template LoadState<char>());
		}
	};
}
#endif
