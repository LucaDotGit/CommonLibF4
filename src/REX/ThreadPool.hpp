#pragma once

#include "REX/NotNull.hpp"

namespace REX
{
	// Source: https://geeksforgeeks.org/cpp/thread-pool-in-cpp,
	// https://dev.to/ish4n10/making-a-thread-pool-in-c-from-scratch-bnm

	class ThreadPool final
	{
	public:
		using clock = std::chrono::steady_clock;

		ThreadPool();
		explicit ThreadPool(std::size_t a_threadCount);

		~ThreadPool() noexcept;

		ThreadPool(const ThreadPool&) = delete;
		ThreadPool(ThreadPool&&) = delete;

		auto operator=(const ThreadPool&) -> ThreadPool& = delete;
		auto operator=(ThreadPool&&) -> ThreadPool& = delete;

		[[nodiscard]]
		auto GetThreadCount() const noexcept -> std::size_t;
		[[nodiscard]]
		auto GetTaskCount() const noexcept -> std::size_t;

		template <class Rep, class Period, class F, class... Args>
		auto SubmitTaskFor(std::chrono::duration<Rep, Period> a_delay, F&& a_func, Args&&... a_args)
			-> std::future<std::invoke_result_t<F, Args...>>
			requires(
				std::is_invocable_v<F, Args...> &&
				(std::is_constructible_v<std::decay_t<F>, F> && std::is_move_constructible_v<std::decay_t<F>>) &&
				((std::is_constructible_v<std::decay_t<Args>, Args> &&
				  std::is_move_constructible_v<std::decay_t<Args>>) &&
				 ...))
		{
			using result_t = std::invoke_result_t<F, Args...>;

			auto task =
				std::packaged_task<result_t()>(std::bind_front(std::forward<F>(a_func), std::forward<Args>(a_args)...));
			auto future = task.get_future();

			const auto startTime = clock::now();
			const auto duration = std::chrono::duration_cast<clock::duration>(a_delay);

			EnqueueTaskImpl(std::bind_front(&decltype(task)::operator(), std::move(task)), startTime, duration);
			return future;
		}

		template <class Clock, class Duration, class F, class... Args>
		auto SubmitTaskUntil(std::chrono::time_point<Clock, Duration> a_timePoint, F&& a_func, Args&&... a_args)
			-> std::future<std::invoke_result_t<F, Args...>>
			requires(
				std::is_invocable_v<F, Args...> &&
				(std::is_constructible_v<std::decay_t<F>, F> && std::is_move_constructible_v<std::decay_t<F>>) &&
				((std::is_constructible_v<std::decay_t<Args>, Args> &&
				  std::is_move_constructible_v<std::decay_t<Args>>) &&
				 ...))
		{
			using result_t = std::invoke_result_t<F, Args...>;

			auto task =
				std::packaged_task<result_t()>(std::bind_front(std::forward<F>(a_func), std::forward<Args>(a_args)...));
			auto future = task.get_future();

			const auto startTime = clock::now();
			const auto duration = std::chrono::duration_cast<clock::duration>(a_timePoint - startTime);

			EnqueueTaskImpl(std::bind_front(&decltype(task)::operator(), std::move(task)), startTime, duration);
			return future;
		}

		template <class Rep, class Period, class F, class... Args>
		auto SubmitTaskEvery(std::chrono::duration<Rep, Period> a_interval, F&& a_func, Args&&... a_args)
			-> std::future<std::invoke_result_t<F, Args...>>
			requires(
				std::is_invocable_v<F, Args...> &&
				(std::is_constructible_v<std::decay_t<F>, F> && std::is_move_constructible_v<std::decay_t<F>>) &&
				((std::is_constructible_v<std::decay_t<Args>, Args> &&
				  std::is_move_constructible_v<std::decay_t<Args>>) &&
				 ...))
		{
			using result_t = std::invoke_result_t<F, Args...>;

			auto task =
				std::packaged_task<result_t()>(std::bind_front(std::forward<F>(a_func), std::forward<Args>(a_args)...));
			auto future = task.get_future();

			const auto startTime = clock::now();
			const auto duration = std::chrono::duration_cast<clock::duration>(a_interval);

			EnqueueTaskImpl(std::bind_front(&decltype(task)::operator(), std::move(task)), startTime, duration, true);
			return future;
		}

		template <class F, class... Args>
		auto SubmitTask(F&& a_func, Args&&... a_args) -> std::future<std::invoke_result_t<F, Args...>>
			requires(
				std::is_invocable_v<F, Args...> &&
				(std::is_constructible_v<std::decay_t<F>, F> && std::is_move_constructible_v<std::decay_t<F>>) &&
				((std::is_constructible_v<std::decay_t<Args>, Args> &&
				  std::is_move_constructible_v<std::decay_t<Args>>) &&
				 ...))
		{
			using result_t = std::invoke_result_t<F, Args...>;

			auto task =
				std::packaged_task<result_t()>(std::bind_front(std::forward<F>(a_func), std::forward<Args>(a_args)...));
			auto future = task.get_future();

			EnqueueTaskImpl(std::bind_front(&decltype(task)::operator(), std::move(task)));
			return future;
		}

		template <std::input_iterator It, class F, class... Args>
		auto SubmitTaskRange(It a_begin, It a_end, const F& a_func, const Args&... a_args)
			-> std::vector<std::future<std::invoke_result_t<F, std::iter_reference_t<It>, Args&...>>>
			requires(
				std::is_invocable_v<F, std::iter_reference_t<It>, Args&...> &&
				(std::is_constructible_v<std::decay_t<F>, F> && std::is_move_constructible_v<std::decay_t<F>>) &&
				(std::is_constructible_v<std::decay_t<std::iter_reference_t<It>>, std::iter_reference_t<It>> &&
				 std::is_move_constructible_v<std::decay_t<std::iter_reference_t<It>>>) &&
				((std::is_constructible_v<std::decay_t<Args>, Args> &&
				  std::is_move_constructible_v<std::decay_t<Args>>) &&
				 ...))
		{
			using result_t = std::invoke_result_t<F, std::iter_reference_t<It>, Args&...>;

			const auto taskCount = std::distance(a_begin, a_end);

			auto tasks = std::vector<REX::NotNull<std::move_only_function<void()>>>();
			tasks.reserve(taskCount);

			auto futures = std::vector<std::future<result_t>>();
			futures.reserve(taskCount);

			for (auto it = a_begin; it != a_end; it++) {
				auto task = std::packaged_task<result_t()>(std::bind_front(a_func, *it, a_args...));
				auto future = task.get_future();

				tasks.push_back(std::bind_front(&decltype(task)::operator(), std::move(task)));
				futures.push_back(std::move(future));
			}

			EnqueueTaskRangeImpl(tasks);
			return futures;
		}

		template <std::ranges::input_range Range, class F, class... Args>
		auto SubmitTaskRange(Range& a_range, const F& a_func, const Args&... a_args)
			-> std::vector<std::future<std::invoke_result_t<F, std::ranges::range_reference_t<Range>, Args&...>>>
			requires(
				std::is_invocable_v<F, std::ranges::range_reference_t<Range>, Args&...> &&
				(std::is_constructible_v<std::decay_t<F>, F> && std::is_move_constructible_v<std::decay_t<F>>) &&
				(std::is_constructible_v<
					 std::decay_t<std::ranges::range_reference_t<Range>>,
					 std::ranges::range_reference_t<Range>> &&
				 std::is_move_constructible_v<std::decay_t<std::ranges::range_reference_t<Range>>>) &&
				((std::is_constructible_v<std::decay_t<Args>, Args> &&
				  std::is_move_constructible_v<std::decay_t<Args>>) &&
				 ...))
		{
			auto begin = std::ranges::begin(a_range);
			auto end = std::ranges::end(a_range);
			return SubmitTaskRange(begin, end, a_func, a_args...);
		}

		template <std::ranges::input_range Range, class F, class... Args>
		auto SubmitTaskRange(const Range& a_range, const F& a_func, const Args&... a_args)
			-> std::vector<std::future<std::invoke_result_t<F, std::ranges::range_reference_t<const Range>, Args&...>>>
			requires(
				std::is_invocable_v<F, std::ranges::range_reference_t<const Range>, Args&...> &&
				(std::is_constructible_v<std::decay_t<F>, F> && std::is_move_constructible_v<std::decay_t<F>>) &&
				(std::is_constructible_v<
					 std::decay_t<std::ranges::range_reference_t<const Range>>,
					 std::ranges::range_reference_t<const Range>> &&
				 std::is_move_constructible_v<std::decay_t<std::ranges::range_reference_t<const Range>>>) &&
				((std::is_constructible_v<std::decay_t<Args>, Args> &&
				  std::is_move_constructible_v<std::decay_t<Args>>) &&
				 ...))
		{
			const auto begin = std::ranges::begin(a_range);
			const auto end = std::ranges::end(a_range);
			return SubmitTaskRange(begin, end, a_func, a_args...);
		}

		template <std::ranges::input_range Range, class F, class... Args>
		// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
		auto SubmitTaskRange(Range&& a_range, const F& a_func, const Args&... a_args)
			-> std::vector<std::future<std::invoke_result_t<F, std::ranges::range_rvalue_reference_t<Range>, Args&...>>>
			requires(
				!std::is_lvalue_reference_v<Range> &&
				std::is_invocable_v<F, std::ranges::range_rvalue_reference_t<Range>, Args&...> &&
				(std::is_constructible_v<std::decay_t<F>, F> && std::is_move_constructible_v<std::decay_t<F>>) &&
				(std::is_constructible_v<
					 std::decay_t<std::ranges::range_rvalue_reference_t<Range>>,
					 std::ranges::range_rvalue_reference_t<Range>> &&
				 std::is_move_constructible_v<std::decay_t<std::ranges::range_rvalue_reference_t<Range>>>) &&
				((std::is_constructible_v<std::decay_t<Args>, Args> &&
				  std::is_move_constructible_v<std::decay_t<Args>>) &&
				 ...))
		{
			auto begin = std::make_move_iterator(std::ranges::begin(a_range));
			auto end = std::make_move_iterator(std::ranges::end(a_range));
			return SubmitTaskRange(begin, end, a_func, a_args...);
		}

		void AttachThisUntilDrained() noexcept;
		void AttachThisUntilDrained(std::stop_token a_stopToken) noexcept;

		void AttachThisUntilStopped(std::stop_token a_stopToken) noexcept;

	private:
		class QueuedTask final
		{
		public:
			explicit QueuedTask(REX::NotNull<std::move_only_function<void()>> a_task) noexcept :
				_task(std::move(a_task))
			{
			}

			explicit QueuedTask(
				REX::NotNull<std::move_only_function<void()>> a_task,
				clock::time_point a_startTime,
				clock::duration a_duration) noexcept :
				_task(std::move(a_task)),
				_startTime(a_startTime),
				_duration(a_duration)
			{
			}

			explicit QueuedTask(
				REX::NotNull<std::move_only_function<void()>> a_task,
				clock::time_point a_startTime,
				clock::duration a_duration,
				bool a_isPersistent) noexcept :
				_task(std::move(a_task)),
				_startTime(a_startTime),
				_duration(a_duration),
				_isPersistent(a_isPersistent)
			{
			}

			~QueuedTask() noexcept = default;

			QueuedTask(const QueuedTask&) = delete;
			QueuedTask(QueuedTask&&) noexcept = default;

			auto operator=(const QueuedTask&) -> QueuedTask& = delete;
			auto operator=(QueuedTask&&) noexcept -> QueuedTask& = default;

			[[nodiscard]]
			auto operator==(const QueuedTask& a_rhs) const noexcept -> bool
			{
				return _startTime == a_rhs._startTime && _duration == a_rhs._duration;
			}

			[[nodiscard]]
			auto operator<=>(const QueuedTask& a_rhs) const noexcept -> auto
			{
				return std::tie(_startTime, _duration) <=> std::tie(a_rhs._startTime, a_rhs._duration);
			}

			[[nodiscard]]
			auto GetTask() & noexcept -> auto&
			{
				return _task;
			}

			[[nodiscard]]
			auto GetTask() const& noexcept -> const auto&
			{
				return _task;
			}

			[[nodiscard]]
			auto GetTask() && noexcept -> auto&&
			{
				return std::move(_task);
			}

			[[nodiscard]]
			auto GetTask() const&& noexcept -> const auto&&
			{
				return std::move(_task);
			}

			[[nodiscard]]
			auto GetStartTime() const noexcept
			{
				return _startTime;
			}

			[[nodiscard]]
			auto GetDuration() const noexcept
			{
				return _duration;
			}

			[[nodiscard]]
			auto GetIsPersistent() const noexcept
			{
				return _isPersistent;
			}

			[[nodiscard]]
			auto GetTargetTime() const noexcept -> std::optional<clock::time_point>
			{
				if (!_startTime.has_value() || !_duration.has_value()) {
					return std::nullopt;
				}

				return _startTime.value() + _duration.value();
			}

		private:
			REX::NotNull<std::move_only_function<void()>> _task;
			std::optional<clock::time_point> _startTime;
			std::optional<clock::duration> _duration;
			bool _isPersistent{false};
		};

		void StartImpl(std::size_t a_threadCount);
		void EnqueueTaskImpl(REX::NotNull<std::move_only_function<void()>> a_task);
		void EnqueueTaskImpl(
			REX::NotNull<std::move_only_function<void()>> a_task,
			clock::time_point a_startTime,
			clock::duration a_duration);
		void EnqueueTaskImpl(
			REX::NotNull<std::move_only_function<void()>> a_task,
			clock::time_point a_startTime,
			clock::duration a_duration,
			bool a_isPersistent);
		void EnqueueTaskRangeImpl(std::span<REX::NotNull<std::move_only_function<void()>>> a_tasks);
		void AttachThisImpl(bool a_exitOnEmptyQueue, std::stop_token a_stopToken) noexcept;
		void StopImpl() noexcept;

		std::vector<std::jthread> _threads;
		mutable std::mutex _queueMutex;
		std::priority_queue<QueuedTask, std::vector<QueuedTask>, std::greater<>> _queuedTasks;
		std::condition_variable _queueCondition;
	};
}
