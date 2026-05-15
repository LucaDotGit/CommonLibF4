#include "REX/ThreadPool.hpp"

#include "REX/Concurrent.hpp"
#include "REX/Contract.hpp"
#include "REX/Message.hpp"

namespace REX
{
	ThreadPool::ThreadPool() noexcept
	{
		StartImpl(REX::GetMaxThreadCount());
	}

	ThreadPool::ThreadPool(std::size_t a_threadCount) noexcept
	{
		StartImpl(a_threadCount);
	}

	ThreadPool::~ThreadPool() noexcept
	{
		StopImpl();
	}

	std::size_t ThreadPool::GetThreadCount() const noexcept
	{
		return _threads.size();
	}

	std::size_t ThreadPool::GetTaskCount() const noexcept
	{
		const auto queueLock = std::scoped_lock(_queueMutex);
		return _taskQueue.size();
	}

	void ThreadPool::AttachThisUntilDrained() noexcept
	{
		while (true) {
			auto queueLock = std::unique_lock(_queueMutex);

			if (_taskQueue.empty()) {
				break;
			}

			auto task = std::move(_taskQueue.front());
			_taskQueue.pop();

			queueLock.unlock();
			queueLock.~unique_lock();

			std::invoke(*task);
		}
	}

	void ThreadPool::AttachThisUntilStopped() noexcept
	{
		while (true) {
			auto queueLock = std::unique_lock(_queueMutex);
			_queueCondition.wait(queueLock, [this]() noexcept -> bool {
				return _doStop || !_taskQueue.empty();
			});

			if (_doStop && _taskQueue.empty()) {
				break;
			}

			auto task = std::move(_taskQueue.front());
			_taskQueue.pop();

			queueLock.unlock();
			queueLock.~unique_lock();

			std::invoke(*task);
		}
	}

	void ThreadPool::StartImpl(std::size_t a_threadCount)
	{
		_threads.reserve(a_threadCount);

		for (auto i = static_cast<std::size_t>(0); i < a_threadCount; i++) {
			_threads.emplace_back(&ThreadPool::AttachThisUntilStopped, this);
		}
	}

	void ThreadPool::EnqueueImpl(REX::NotNull<std::move_only_function<void()>>&& a_task)
	{
		{
			const auto queueLock = std::scoped_lock(_queueMutex);

			if (_doStop) [[unlikely]] {
				REX::Assert(false);
				return;
			}

			_taskQueue.push(std::move(a_task));
		}

		_queueCondition.notify_one();
	}

	void ThreadPool::EnqueueRangeImpl(std::span<REX::NotNull<std::move_only_function<void()>>> a_tasks)
	{
		{
			const auto queueLock = std::scoped_lock(_queueMutex);

			if (_doStop) [[unlikely]] {
				REX::Assert(false);
				return;
			}

			for (auto& task : a_tasks) {
				_taskQueue.push(std::move(task));
			}
		}

		_queueCondition.notify_all();
	}

	void ThreadPool::StopImpl() noexcept
	{
		{
			const auto queueLock = std::scoped_lock(_queueMutex);

			_doStop = true;
		}

		_queueCondition.notify_all();

		for (auto i = static_cast<std::size_t>(0); i < _threads.size(); i++) {
			auto& thread = _threads[i];
			if (!thread.joinable()) [[unlikely]] {
				REX::Assert(false);
				continue;
			}

			try {
				thread.join();
			}
			catch (const std::system_error& error) {
				REX::Fail(
					"Failed to join thread {} at index {}.\n",
					"Exception Error: {}"sv,
					thread.get_id(), i, error.what());
			}
		}

		_threads.clear();
	}
}
