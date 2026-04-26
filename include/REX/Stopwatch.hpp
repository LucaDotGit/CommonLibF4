#pragma once

namespace REX
{
	template <class Clock>
	class BasicStopwatch final
	{
	public:
		using clock = Clock;

	private:
		using duration = clock::duration;
		using time_point = clock::time_point;

	public:
		inline static constexpr auto IS_STEADY = clock::is_steady;
		inline static constexpr auto IS_HIGH_RESOLUTION = std::same_as<typename clock::period, std::nano>;

		static_assert(std::chrono::is_clock_v<clock>,
			"`REX::BasicStopwatch` requires a valid clock type.");
		static_assert(std::is_nothrow_invocable_r_v<time_point, decltype(&clock::now)>,
			"`REX::BasicStopwatch` requires a `noexcept`-invocable `clock::now()` function.");

		BasicStopwatch() noexcept = default;
		~BasicStopwatch() noexcept = default;

		BasicStopwatch(const BasicStopwatch&) noexcept = default;
		BasicStopwatch(BasicStopwatch&&) noexcept = default;

		BasicStopwatch& operator=(const BasicStopwatch&) noexcept = default;
		BasicStopwatch& operator=(BasicStopwatch&&) noexcept = default;

		[[nodiscard]] static BasicStopwatch StartNew() noexcept
		{
			auto stopwatch = BasicStopwatch();
			stopwatch.Start();
			return stopwatch;
		}

		[[nodiscard]] bool IsRunning() const noexcept
		{
			return _isRunning;
		}

		[[nodiscard]] time_point GetStartTime() const noexcept
		{
			return _startTime;
		}

		[[nodiscard]] duration GetElapsedTime() const noexcept
		{
			auto timeElapsed = _elapsedTime;

			if (_isRunning) {
				const auto currentTime = clock::now();
				timeElapsed += currentTime - _startTime;
			}

			return timeElapsed;
		}

		bool Start() noexcept
		{
			if (_isRunning) {
				return false;
			}

			_startTime = clock::now();
			_isRunning = true;
			return true;
		}

		bool Stop() noexcept
		{
			if (!_isRunning) {
				return false;
			}

			const auto currentTime = clock::now();
			_elapsedTime += currentTime - _startTime;
			_isRunning = false;
			return true;
		}

		void Reset() noexcept
		{
			_startTime = {};
			_elapsedTime = {};
			_isRunning = false;
		}

		void Restart() noexcept
		{
			_startTime = clock::now();
			_elapsedTime = {};
			_isRunning = true;
		}

	private:
		time_point _startTime{};
		duration _elapsedTime{};
		bool _isRunning{ false };
	};

	extern template class BasicStopwatch<std::chrono::steady_clock>;

	using Stopwatch = BasicStopwatch<std::chrono::steady_clock>;
}
