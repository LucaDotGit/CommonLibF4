#pragma once

#include "REX/ThreadPool.hpp"

namespace REX
{
	template <class F, class... Args>
	[[nodiscard]] auto ThreadPool::SubmitTask(F&& a_func, Args&&... a_args)
		-> std::future<std::invoke_result_t<F, Args...>>
		requires(std::is_invocable_v<F, Args...> &&
				 (std::is_copy_constructible_v<std::decay_t<F>> &&
					 std::is_move_constructible_v<std::decay_t<F>>) &&
				 ((std::is_copy_constructible_v<std::decay_t<Args>> &&
					  std::is_move_constructible_v<std::decay_t<Args>>) &&
					 ...))
	{
		using result_t = std::invoke_result_t<F, Args...>;

		auto task = std::packaged_task<result_t()>(
			std::bind_front(std::forward<F>(a_func), std::forward<Args>(a_args)...));

		auto future = task.get_future();

		EnqueueImpl([task = std::move(task)]() mutable {
			std::invoke(task);
		});

		return future;
	}

	template <class It, class F, class... Args>
	[[nodiscard]] auto ThreadPool::SubmitTaskRange(It a_begin, It a_end, F&& a_func, Args&&... a_args) // NOLINT(cppcoreguidelines-missing-std-forward)
		-> std::vector<std::future<std::invoke_result_t<F&, std::iter_reference_t<It>, Args&...>>>
		requires(std::forward_iterator<It> &&
				 std::is_invocable_v<F&, std::iter_reference_t<It>, Args&...> &&
				 (std::is_copy_constructible_v<std::decay_t<F>> &&
					 std::is_move_constructible_v<std::decay_t<F>>) &&
				 (std::is_copy_constructible_v<std::iter_value_t<It>> &&
					 std::is_move_constructible_v<std::iter_value_t<It>>) &&
				 ((std::is_copy_constructible_v<std::decay_t<Args>> &&
					  std::is_move_constructible_v<std::decay_t<Args>>) &&
					 ...))
	{
		using result_t = std::invoke_result_t<F&, std::iter_reference_t<It>, Args&...>;

		const auto taskCount = std::distance(a_begin, a_end);

		auto futures = std::vector<std::future<result_t>>();
		futures.reserve(taskCount);

		auto tasks = std::vector<REX::NotNull<std::move_only_function<void()>>>();
		tasks.reserve(taskCount);

		for (auto it = a_begin; it != a_end; it++) {
			auto task = std::packaged_task<result_t()>(
				std::bind_front(a_func, *it, a_args...));

			auto future = task.get_future();
			futures.push_back(std::move(future));

			tasks.emplace_back([task = std::move(task)]() mutable {
				std::invoke(task);
			});
		}

		EnqueueRangeImpl(tasks);
		return futures;
	}

	template <std::ranges::forward_range Range, class F, class... Args>
	[[nodiscard]] auto ThreadPool::SubmitTaskRange(Range& a_range, F&& a_func, Args&&... a_args)
		-> std::vector<std::future<std::invoke_result_t<F&, std::ranges::range_reference_t<Range>, Args&...>>>
		requires(std::is_invocable_v<F&, std::ranges::range_reference_t<Range>, Args&...> &&
				 (std::is_copy_constructible_v<std::decay_t<F>> &&
					 std::is_move_constructible_v<std::decay_t<F>>) &&
				 (std::is_copy_constructible_v<std::ranges::range_value_t<Range>> &&
					 std::is_move_constructible_v<std::ranges::range_value_t<Range>>) &&
				 ((std::is_copy_constructible_v<std::decay_t<Args>> &&
					  std::is_move_constructible_v<std::decay_t<Args>>) &&
					 ...))
	{
		auto begin = std::ranges::begin(a_range);
		auto end = std::ranges::end(a_range);
		return SubmitTaskRange(begin, end, std::forward<F>(a_func), std::forward<Args>(a_args)...);
	}

	template <std::ranges::forward_range Range, class F, class... Args>
	[[nodiscard]] auto ThreadPool::SubmitTaskRange(const Range& a_range, F&& a_func, Args&&... a_args)
		-> std::vector<std::future<std::invoke_result_t<F&, std::ranges::range_reference_t<const Range>, Args&...>>>
		requires(std::is_invocable_v<F&, std::ranges::range_reference_t<const Range>, Args&...> &&
				 (std::is_copy_constructible_v<std::decay_t<F>> &&
					 std::is_move_constructible_v<std::decay_t<F>>) &&
				 (std::is_copy_constructible_v<std::ranges::range_value_t<const Range>> &&
					 std::is_move_constructible_v<std::ranges::range_value_t<const Range>>) &&
				 ((std::is_copy_constructible_v<std::decay_t<Args>> &&
					  std::is_move_constructible_v<std::decay_t<Args>>) &&
					 ...))
	{
		const auto begin = std::ranges::begin(a_range);
		const auto end = std::ranges::end(a_range);
		return SubmitTaskRange(begin, end, std::forward<F>(a_func), std::forward<Args>(a_args)...);
	}

	template <std::ranges::forward_range Range, class F, class... Args>
	[[nodiscard]] auto ThreadPool::SubmitTaskRange(Range&& a_range, F&& a_func, Args&&... a_args) // NOLINT(cppcoreguidelines-missing-std-forward)
		-> std::vector<std::future<std::invoke_result_t<F&, std::ranges::range_rvalue_reference_t<Range>, Args&...>>>
		requires(!std::is_lvalue_reference_v<Range> &&
				 std::is_invocable_v<F&, std::ranges::range_rvalue_reference_t<Range>, Args&...> &&
				 (std::is_copy_constructible_v<std::decay_t<F>> &&
					 std::is_move_constructible_v<std::decay_t<F>>) &&
				 (std::is_copy_constructible_v<std::ranges::range_value_t<Range>> &&
					 std::is_move_constructible_v<std::ranges::range_value_t<Range>>) &&
				 ((std::is_copy_constructible_v<std::decay_t<Args>> &&
					  std::is_move_constructible_v<std::decay_t<Args>>) &&
					 ...))
	{
		auto begin = std::make_move_iterator(std::ranges::begin(a_range));
		auto end = std::make_move_iterator(std::ranges::end(a_range));
		return SubmitTaskRange(begin, end, std::forward<F>(a_func), std::forward<Args>(a_args)...);
	}
}
