#pragma once

#include "F4SE/ITaskDelegate.hpp"

#include "REX/NotNull.hpp"

namespace F4SE
{
	class TaskDelegate
		: public ITaskDelegate
	{
	public:
		explicit TaskDelegate(REX::NotNull<std::function<void()>> a_task)
			: _func(std::move(a_task))
		{
		}

		TaskDelegate(const TaskDelegate&) = delete;
		TaskDelegate(TaskDelegate&&) = delete;

		TaskDelegate& operator=(const TaskDelegate&) = delete;
		TaskDelegate& operator=(TaskDelegate&&) = delete;

		~TaskDelegate() noexcept override = default; // 00

		// override (ITaskDelegate)
		void Run() override // 01
		{
			std::invoke(*_func);
		}

	protected:
		REX::NotNull<std::function<void()>> _func;
	};
}
