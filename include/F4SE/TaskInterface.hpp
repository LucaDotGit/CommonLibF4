#pragma once

#include "F4SE/QueryInterface.hpp"

#include "REX/Own.hpp"

namespace F4SE
{
	class ITaskDelegate;

	class TaskInterface final
	{
	public:
		inline static constexpr auto INTERFACE_ID{ QueryInterface::InterfaceID::kTask };
		inline static constexpr auto INTERFACE_VERSION{ 2ui32 };

		TaskInterface() = delete;
		~TaskInterface() = delete;

		TaskInterface(const TaskInterface&) = delete;
		TaskInterface(TaskInterface&&) = delete;

		TaskInterface& operator=(const TaskInterface&) = delete;
		TaskInterface& operator=(TaskInterface&&) = delete;

		[[nodiscard]] std::uint32_t GetVersion() const noexcept;

		void AddTask(REX::NotNull<REX::Owner<ITaskDelegate*>> a_task) const;
		void AddTask(REX::NotNull<std::function<void()>> a_task) const;
		void AddUITask(REX::NotNull<REX::Owner<ITaskDelegate*>> a_task) const;
		void AddUITask(REX::NotNull<std::function<void()>> a_task) const;
		void AddTaskPermanent(REX::NotNull<REX::Owner<ITaskDelegate*>> a_task) const;
		void AddTaskPermanent(REX::NotNull<std::function<void()>> a_task) const;
		void AddUITaskPermanent(REX::NotNull<REX::Owner<ITaskDelegate*>> a_task) const;
		void AddUITaskPermanent(REX::NotNull<std::function<void()>> a_task) const;
	};
	static_assert(std::is_empty_v<TaskInterface>);
}
