#pragma once

#include "REX/NotNull.hpp"

namespace REX
{
	// Source: https://www.geeksforgeeks.org/cpp/thread-pool-in-cpp, https://dev.to/ish4n10/making-a-thread-pool-in-c-from-scratch-bnm

	class ThreadPool final
	{
	public:
		explicit ThreadPool() noexcept;
		explicit ThreadPool(std::size_t a_threadCount) noexcept;

		~ThreadPool() noexcept;

		ThreadPool(const ThreadPool&) = delete;
		ThreadPool(ThreadPool&&) = delete;

		ThreadPool& operator=(const ThreadPool&) = delete;
		ThreadPool& operator=(ThreadPool&&) = delete;

		[[nodiscard]] std::size_t GetThreadCount() const noexcept;
		[[nodiscard]] std::size_t GetTaskCount() const noexcept;

		template <class F, class... Args>
		[[nodiscard]] auto SubmitTask(F&& a_func, Args&&... a_args)
			-> std::future<std::invoke_result_t<F, Args...>>
			requires(std::is_invocable_v<F, Args...> &&
					 (std::is_copy_constructible_v<std::decay_t<F>> &&
						 std::is_move_constructible_v<std::decay_t<F>>) &&
					 ((std::is_copy_constructible_v<std::decay_t<Args>> &&
						  std::is_move_constructible_v<std::decay_t<Args>>) &&
						 ...));

		template <class It, class F, class... Args>
		[[nodiscard]] auto SubmitTaskRange(It a_begin, It a_end, const F& a_func, const Args&... a_args)
			-> std::vector<std::future<std::invoke_result_t<F, std::iter_reference_t<It>, Args&...>>>
			requires(std::forward_iterator<It> &&
					 std::is_invocable_v<F, std::iter_reference_t<It>, Args&...> &&
					 (std::is_copy_constructible_v<std::decay_t<F>> &&
						 std::is_move_constructible_v<std::decay_t<F>>) &&
					 (std::is_copy_constructible_v<std::iter_reference_t<It>> &&
						 std::is_move_constructible_v<std::iter_reference_t<It>>) &&
					 ((std::is_copy_constructible_v<std::decay_t<Args>> &&
						  std::is_move_constructible_v<std::decay_t<Args>>) &&
						 ...));

		template <std::ranges::forward_range Range, class F, class... Args>
		[[nodiscard]] auto SubmitTaskRange(Range& a_range, const F& a_func, const Args&... a_args)
			-> std::vector<std::future<std::invoke_result_t<F, std::ranges::range_reference_t<Range>, Args&...>>>
			requires(std::is_invocable_v<F, std::ranges::range_reference_t<Range>, Args&...> &&
					 (std::is_copy_constructible_v<std::decay_t<F>> &&
						 std::is_move_constructible_v<std::decay_t<F>>) &&
					 (std::is_copy_constructible_v<std::ranges::range_reference_t<Range>> &&
						 std::is_move_constructible_v<std::ranges::range_reference_t<Range>>) &&
					 ((std::is_copy_constructible_v<std::decay_t<Args>> &&
						  std::is_move_constructible_v<std::decay_t<Args>>) &&
						 ...));

		template <std::ranges::forward_range Range, class F, class... Args>
		[[nodiscard]] auto SubmitTaskRange(const Range& a_range, const F& a_func, const Args&... a_args)
			-> std::vector<std::future<std::invoke_result_t<F, std::ranges::range_reference_t<const Range>, Args&...>>>
			requires(std::is_invocable_v<F, std::ranges::range_reference_t<const Range>, Args&...> &&
					 (std::is_copy_constructible_v<std::decay_t<F>> &&
						 std::is_move_constructible_v<std::decay_t<F>>) &&
					 (std::is_copy_constructible_v<std::ranges::range_reference_t<const Range>> &&
						 std::is_move_constructible_v<std::ranges::range_reference_t<const Range>>) &&
					 ((std::is_copy_constructible_v<std::decay_t<Args>> &&
						  std::is_move_constructible_v<std::decay_t<Args>>) &&
						 ...));

		template <std::ranges::forward_range Range, class F, class... Args>
		[[nodiscard]] auto SubmitTaskRange(Range&& a_range, const F& a_func, const Args&... a_args)
			-> std::vector<std::future<std::invoke_result_t<F, std::ranges::range_rvalue_reference_t<Range>, Args&...>>>
			requires(!std::is_lvalue_reference_v<Range> &&
					 std::is_invocable_v<F, std::ranges::range_rvalue_reference_t<Range>, Args&...> &&
					 (std::is_copy_constructible_v<std::decay_t<F>> &&
						 std::is_move_constructible_v<std::decay_t<F>>) &&
					 (std::is_copy_constructible_v<std::ranges::range_rvalue_reference_t<Range>> &&
						 std::is_move_constructible_v<std::ranges::range_rvalue_reference_t<Range>>) &&
					 ((std::is_copy_constructible_v<std::decay_t<Args>> &&
						  std::is_move_constructible_v<std::decay_t<Args>>) &&
						 ...));

		void AttachThisUntilDrained() noexcept;
		void AttachThisUntilStopped() noexcept;

	private:
		void StartImpl(std::size_t a_threadCount);
		void EnqueueImpl(REX::NotNull<std::move_only_function<void()>>&& a_task);
		void EnqueueRangeImpl(std::span<REX::NotNull<std::move_only_function<void()>>> a_tasks);
		void StopImpl() noexcept;

		std::vector<std::thread> _threads;
		mutable std::mutex _queueMutex;
		std::queue<REX::NotNull<std::move_only_function<void()>>> _taskQueue;
		std::condition_variable _queueCondition;
		bool _doStop{ false };
	};
}

#include "REX/ThreadPool.inl"
