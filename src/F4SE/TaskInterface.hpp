#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/QueryInterface.hpp"
#include "REX/NotNull.hpp"

namespace F4SE
{
	class ITaskDelegate;

	using TaskCallback = void() const;

	class TaskInterface final
	{
	public:
		inline static constexpr auto INTERFACE_ID = QueryInterface::InterfaceID::Task;
		inline static constexpr auto INTERFACE_VERSION = static_cast<std::uint32_t>(2);

		TaskInterface() = delete;
		~TaskInterface() = delete;

		TaskInterface(const TaskInterface&) = delete;
		TaskInterface(TaskInterface&&) = delete;

		auto operator=(const TaskInterface&) -> TaskInterface& = delete;
		auto operator=(TaskInterface&&) -> TaskInterface& = delete;

		[[nodiscard]]
		auto GetVersion() const noexcept -> F4SE::InterfaceVersion;

		void AddTask(REX::NotNull<std::unique_ptr<ITaskDelegate>> a_task) const;
		void AddTask(REX::NotNull<std::move_only_function<TaskCallback>> a_task) const;
		void AddUITask(REX::NotNull<std::unique_ptr<ITaskDelegate>> a_task) const;
		void AddUITask(REX::NotNull<std::move_only_function<TaskCallback>> a_task) const;
		void AddTaskPermanent(REX::NotNull<std::unique_ptr<ITaskDelegate>> a_task) const;
		void AddTaskPermanent(REX::NotNull<std::move_only_function<TaskCallback>> a_task) const;
		void AddUITaskPermanent(REX::NotNull<std::unique_ptr<ITaskDelegate>> a_task) const;
		void AddUITaskPermanent(REX::NotNull<std::move_only_function<TaskCallback>> a_task) const;
	};

	static_assert(std::is_empty_v<TaskInterface>);
}
