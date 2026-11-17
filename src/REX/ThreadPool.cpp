#include "REX/ThreadPool.hpp"

#include "REX/Concurrency.hpp"
#include "REX/Container.hpp"
#include "REX/Contract.hpp"
#include "REX/NotNull.hpp"

namespace REX
{
	ThreadPool::ThreadPool()
	{
		StartImpl(REX::GetMaxThreadCount());
	}

	ThreadPool::ThreadPool(std::size_t a_threadCount)
	{
		StartImpl(a_threadCount);
	}

	ThreadPool::~ThreadPool() noexcept
	{
		StopImpl();
	}

	auto ThreadPool::GetThreadCount() const noexcept -> std::size_t
	{
		return _threads.size();
	}

	auto ThreadPool::GetTaskCount() const noexcept -> std::size_t
	{
		const auto queueLock = std::scoped_lock(_queueMutex);
		return _queuedTasks.size();
	}

	void ThreadPool::AttachThisUntilDrained() noexcept
	{
		AttachThisUntilDrained(std::stop_token());
	}

	void ThreadPool::AttachThisUntilDrained(std::stop_token a_stopToken) noexcept
	{
		AttachThisImpl(true, std::move(a_stopToken));
	}

	void ThreadPool::AttachThisUntilStopped(std::stop_token a_stopToken) noexcept
	{
		AttachThisImpl(false, std::move(a_stopToken));
	}

	void ThreadPool::StartImpl(std::size_t a_threadCount)
	{
		_threads.reserve(a_threadCount);

		for (auto i = static_cast<std::size_t>(0); i < a_threadCount; i++) {
			_threads.emplace_back(std::bind_front(&ThreadPool::AttachThisUntilStopped, this));
		}
	}

	void ThreadPool::EnqueueTaskImpl(REX::NotNull<std::move_only_function<void()>> a_task)
	{
		{
			const auto queueLock = std::scoped_lock(_queueMutex);
			_queuedTasks.emplace(std::move(a_task));
		}

		_queueCondition.notify_one();
	}

	void ThreadPool::EnqueueTaskImpl(
		REX::NotNull<std::move_only_function<void()>> a_task,
		clock::time_point a_startTime,
		clock::duration a_duration)
	{
		{
			const auto queueLock = std::scoped_lock(_queueMutex);
			_queuedTasks.emplace(std::move(a_task), a_startTime, a_duration);
		}

		_queueCondition.notify_one();
	}

	void ThreadPool::EnqueueTaskImpl(
		REX::NotNull<std::move_only_function<void()>> a_task,
		clock::time_point a_startTime,
		clock::duration a_duration,
		bool a_isPersistent)
	{
		{
			const auto queueLock = std::scoped_lock(_queueMutex);
			_queuedTasks.emplace(std::move(a_task), a_startTime, a_duration, a_isPersistent);
		}

		_queueCondition.notify_one();
	}

	void ThreadPool::EnqueueTaskRangeImpl(std::span<REX::NotNull<std::move_only_function<void()>>> a_tasks)
	{
		{
			const auto queueLock = std::scoped_lock(_queueMutex);

			for (auto& task : a_tasks) {
				_queuedTasks.emplace(std::move(task));
			}
		}

		_queueCondition.notify_all();
	}

	// NOLINTNEXTLINE(performance-unnecessary-value-param)
	void ThreadPool::AttachThisImpl(bool a_exitOnEmptyQueue, std::stop_token a_stopToken) noexcept
	{
		const auto stopCallback = std::stop_callback(a_stopToken, [this] -> void {
			_queueCondition.notify_all();
		});

		while (true) {
			auto queueLock = std::unique_lock(_queueMutex);

			while (true) {
				if (a_stopToken.stop_requested()) {
					return;
				}

				if (_queuedTasks.empty()) {
					if (a_exitOnEmptyQueue) {
						return;
					}

					_queueCondition.wait(queueLock);
					continue;
				}

				const auto targetTime = _queuedTasks.top().GetTargetTime();
				if (!targetTime.has_value()) {
					break;
				}

				const auto waitResult = _queueCondition.wait_until(queueLock, targetTime.value());
				if (waitResult == std::cv_status::timeout) {
					break;
				}
			}

			if (_queuedTasks.empty()) {
				continue;
			}

			auto task = REX::Pop(_queuedTasks);

			queueLock.unlock();

			try {
				std::invoke(*(task.GetTask()));
			}
			catch (const std::future_error& error) {
				std::ignore = error;
				REX::Assert(false);
				continue;
			}

			const auto isPersistent = task.GetIsPersistent();
			if (!isPersistent) {
				continue;
			}

			const auto duration = task.GetDuration();
			if (!duration.has_value()) {
				continue;
			}

			const auto startTime = clock::now();
			EnqueueTaskImpl(std::move(task.GetTask()), startTime, duration.value(), true);
		}
	}

	void ThreadPool::StopImpl() noexcept
	{
		for (auto& thread : _threads) {
			thread.request_stop();
		}

		_threads.clear();
	}
}
