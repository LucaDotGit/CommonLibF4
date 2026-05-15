#include "F4SE/TaskInterface.hpp"

#include "F4SE/Core.hpp"
#include "F4SE/TaskDelegate.hpp"

namespace F4SE::Impl
{
	struct F4SETaskInterface final
	{
		std::uint32_t interfaceVersion;
		void(F4SE_API* AddTask)(void*);
		void(F4SE_API* AddUITask)(void*);
		void(F4SE_API* AddTaskPermanent)(void*); // since F4SE v0.7.1
	};

	[[nodiscard]] __forceinline static const F4SETaskInterface& GetProxy(const TaskInterface* a_interface) noexcept
	{
		return reinterpret_cast<const F4SETaskInterface&>(*a_interface);
	}
}

namespace F4SE
{
	std::uint32_t TaskInterface::GetVersion() const noexcept
	{
		return Impl::GetProxy(this).interfaceVersion;
	}

	void TaskInterface::AddTask(REX::NotNull<REX::Owner<ITaskDelegate*>> a_task) const
	{
		Impl::GetProxy(this).AddTask(a_task.get());
	}

	void TaskInterface::AddTask(REX::NotNull<std::function<void()>> a_task) const
	{
		AddTask(new TaskDelegate(std::move(a_task)));
	}

	void TaskInterface::AddUITask(REX::NotNull<REX::Owner<ITaskDelegate*>> a_task) const
	{
		Impl::GetProxy(this).AddTask(a_task.get());
	}

	void TaskInterface::AddUITask(REX::NotNull<std::function<void()>> a_task) const
	{
		AddUITask(new TaskDelegate(std::move(a_task)));
	}

	void TaskInterface::AddTaskPermanent(REX::NotNull<REX::Owner<ITaskDelegate*>> a_task) const
	{
		if (F4SE::IsRuntimeAtLeastNG()) {
			Impl::GetProxy(this).AddTaskPermanent(a_task.get());
			return;
		}

		auto taskRepeater = std::make_shared<std::function<void()>>();
		*taskRepeater = [this, a_task, taskRepeater]() -> void {
			a_task->Run();
			AddTask(*taskRepeater);
		};

		AddTask(*taskRepeater);
	}

	void TaskInterface::AddTaskPermanent(REX::NotNull<std::function<void()>> a_task) const
	{
		if (F4SE::IsRuntimeAtLeastNG()) {
			Impl::GetProxy(this).AddTaskPermanent(new TaskDelegate(std::move(a_task)));
			return;
		}

		auto permanentTask = std::make_shared<TaskDelegate>(std::move(a_task));

		auto taskRepeater = std::make_shared<std::function<void()>>();
		*taskRepeater = [this, permanentTask, taskRepeater]() -> void {
			permanentTask->Run();
			AddTask(*taskRepeater);
		};

		AddTask(*taskRepeater);
	}

	void TaskInterface::AddUITaskPermanent(REX::NotNull<REX::Owner<ITaskDelegate*>> a_task) const
	{
		auto taskRepeater = std::make_shared<std::function<void()>>();
		*taskRepeater = [this, a_task, taskRepeater]() -> void {
			a_task->Run();
			AddUITask(*taskRepeater);
		};

		AddUITask(*taskRepeater);
	}

	void TaskInterface::AddUITaskPermanent(REX::NotNull<std::function<void()>> a_task) const
	{
		auto permanentTask = std::make_shared<TaskDelegate>(std::move(a_task));

		auto taskRepeater = std::make_shared<std::function<void()>>();
		*taskRepeater = [this, permanentTask, taskRepeater]() -> void {
			permanentTask->Run();
			AddUITask(*taskRepeater);
		};

		AddUITask(*taskRepeater);
	}
}
