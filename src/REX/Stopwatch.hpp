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
		static_assert(std::chrono::is_clock_v<clock>, "`REX::BasicStopwatch` requires a valid clock type.");

		BasicStopwatch() noexcept = default;
		~BasicStopwatch() noexcept = default;

		BasicStopwatch(const BasicStopwatch&) noexcept = default;
		BasicStopwatch(BasicStopwatch&&) noexcept = default;

		auto operator=(const BasicStopwatch&) noexcept -> BasicStopwatch& = default;
		auto operator=(BasicStopwatch&&) noexcept -> BasicStopwatch& = default;

		[[nodiscard]]
		static auto StartNew() noexcept -> BasicStopwatch
		{
			auto stopwatch = BasicStopwatch();
			stopwatch.Start();
			return stopwatch;
		}

		[[nodiscard]]
		auto IsRunning() const noexcept -> bool
		{
			return _isRunning;
		}

		[[nodiscard]]
		auto GetStartTime() const noexcept -> time_point
		{
			return _startTime;
		}

		[[nodiscard]]
		auto GetElapsedTime() const noexcept -> duration
		{
			auto timeElapsed = _elapsedTime;

			if (_isRunning) {
				const auto currentTime = GetCurrentTime();
				timeElapsed += currentTime - _startTime;
			}

			return timeElapsed;
		}

		auto Start() noexcept -> bool
		{
			if (_isRunning) {
				return false;
			}

			_startTime = GetCurrentTime();
			_isRunning = true;
			return true;
		}

		auto Stop() noexcept -> bool
		{
			if (!_isRunning) {
				return false;
			}

			const auto currentTime = GetCurrentTime();
			_elapsedTime += currentTime - _startTime;
			_isRunning = false;
			return true;
		}

		void Reset() noexcept
		{
			_startTime = {};
			_elapsedTime = duration::zero();
			_isRunning = false;
		}

		void Restart() noexcept
		{
			_startTime = GetCurrentTime();
			_elapsedTime = duration::zero();
			_isRunning = true;
		}

	private:
		[[nodiscard]]
		static auto GetCurrentTime() noexcept -> time_point
		{
			return clock::now();
		}

		time_point _startTime;
		duration _elapsedTime{duration::zero()};
		bool _isRunning{false};
	};

	using Stopwatch = BasicStopwatch<std::chrono::steady_clock>;
	static_assert(Stopwatch::clock::is_steady);
}
