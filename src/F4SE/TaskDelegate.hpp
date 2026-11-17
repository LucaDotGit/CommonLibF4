#pragma once

#include "F4SE/ITaskDelegate.hpp"
#include "REX/NotNull.hpp"

namespace F4SE
{
	class TaskDelegate final : public ITaskDelegate
	{
	public:
		using value_type = REX::NotNull<std::move_only_function<void() const>>;

		explicit TaskDelegate(value_type a_task) :
			_func(std::move(a_task))
		{
		}

		~TaskDelegate() noexcept override = default;

		TaskDelegate(const TaskDelegate&) = delete;
		TaskDelegate(TaskDelegate&&) = delete;

		auto operator=(const TaskDelegate&) -> TaskDelegate& = delete;
		auto operator=(TaskDelegate&&) -> TaskDelegate& = delete;

		void Run() override
		{
			std::invoke(_func.get());
		}

	private:
		value_type _func;
	};
}
