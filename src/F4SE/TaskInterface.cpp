#include "F4SE/TaskInterface.hpp"

#include "F4SE/Core.hpp"
#include "F4SE/ITaskDelegate.hpp"
#include "F4SE/Runtimes.hpp"
#include "F4SE/TaskDelegate.hpp"
#include "REX/Macros.hpp"
#include "REX/NotNull.hpp"

namespace F4SE::Impl
{
	namespace
	{
		class F4SETaskInterface final
		{
		public:
			F4SETaskInterface() = delete;
			~F4SETaskInterface() = delete;

			F4SETaskInterface(const F4SETaskInterface&) = delete;
			F4SETaskInterface(F4SETaskInterface&&) = delete;

			auto operator=(const F4SETaskInterface&) -> F4SETaskInterface& = delete;
			auto operator=(F4SETaskInterface&&) -> F4SETaskInterface& = delete;

			F4SE::InterfaceVersion interfaceVersion;
			void(F4SE_API* addTask)(ITaskDelegate*);
			void(F4SE_API* addUITask)(ITaskDelegate*);
			void(F4SE_API* addTaskPermanent)(ITaskDelegate*); // since F4SE v0.7.1
		};

		[[nodiscard]] [[REX_ALWAYS_INLINE]]
		auto GetProxy(const TaskInterface& a_interface) noexcept -> const F4SETaskInterface&
		{
			return reinterpret_cast<const F4SETaskInterface&>(a_interface);
		}

		class PermanentTaskState final
		{
		public:
			PermanentTaskState() noexcept = default;
			~PermanentTaskState() noexcept = default;

			PermanentTaskState(const PermanentTaskState&) = delete;
			PermanentTaskState(PermanentTaskState&&) = delete;

			auto operator=(const PermanentTaskState&) -> PermanentTaskState& = delete;
			auto operator=(PermanentTaskState&&) -> PermanentTaskState& = delete;

			[[nodiscard]]
			auto GetExecuteTask() const noexcept -> bool
			{
				return _executeTask;
			}

			void SetExecuteTask(bool a_executeTask) noexcept
			{
				_executeTask = a_executeTask;
			}

			auto ExchangeExecuteTask(bool a_executeTask) noexcept -> bool
			{
				return std::exchange(_executeTask, a_executeTask);
			}

		private:
			bool _executeTask{true};
		};

		class IPermanentTaskDelegate : public ITaskDelegate
		{
		public:
			IPermanentTaskDelegate(
				REX::NotNull<std::unique_ptr<PermanentTaskState>> a_taskState,
				REX::NotNull<std::unique_ptr<ITaskDelegate>> a_taskDelegate) :
				_taskState(std::move(a_taskState)),
				_taskDelegate(std::move(a_taskDelegate))
			{
			}

			~IPermanentTaskDelegate() noexcept override = default;

			IPermanentTaskDelegate(const IPermanentTaskDelegate&) = delete;
			IPermanentTaskDelegate(IPermanentTaskDelegate&&) = delete;

			auto operator=(const IPermanentTaskDelegate&) -> IPermanentTaskDelegate& = delete;
			auto operator=(IPermanentTaskDelegate&&) -> IPermanentTaskDelegate& = delete;

			void Run() override
			{
				if (_taskState->ExchangeExecuteTask(false)) {
					_taskDelegate->Run();
				}
				else {
					_taskState->SetExecuteTask(true);
				}

				Reschedule();
			}

			virtual void Reschedule() = 0;

		protected:
			REX::NotNull<std::unique_ptr<PermanentTaskState>> _taskState;
			REX::NotNull<std::unique_ptr<ITaskDelegate>> _taskDelegate;
		};

		class PermanentTaskDelegate final : public IPermanentTaskDelegate
		{
		public:
			PermanentTaskDelegate(
				REX::NotNull<const TaskInterface*> a_taskInterface,
				REX::NotNull<std::unique_ptr<PermanentTaskState>> a_taskState,
				REX::NotNull<std::unique_ptr<ITaskDelegate>> a_taskDelegate) :
				IPermanentTaskDelegate(std::move(a_taskState), std::move(a_taskDelegate)),
				_taskInterface(a_taskInterface)
			{
			}

			~PermanentTaskDelegate() noexcept override = default;

			PermanentTaskDelegate(const PermanentTaskDelegate&) = delete;
			PermanentTaskDelegate(PermanentTaskDelegate&&) = delete;

			auto operator=(const PermanentTaskDelegate&) -> PermanentTaskDelegate& = delete;
			auto operator=(PermanentTaskDelegate&&) -> PermanentTaskDelegate& = delete;

			void Reschedule() override;

		private:
			REX::NotNull<const TaskInterface*> _taskInterface;
		};

		class PermanentUITaskDelegate final : public IPermanentTaskDelegate
		{
		public:
			PermanentUITaskDelegate(
				REX::NotNull<const TaskInterface*> a_taskInterface,
				REX::NotNull<std::unique_ptr<PermanentTaskState>> a_taskState,
				REX::NotNull<std::unique_ptr<ITaskDelegate>> a_taskDelegate) :
				IPermanentTaskDelegate(std::move(a_taskState), std::move(a_taskDelegate)),
				_taskInterface(a_taskInterface)
			{
			}

			~PermanentUITaskDelegate() noexcept override = default;

			PermanentUITaskDelegate(const PermanentUITaskDelegate&) = delete;
			PermanentUITaskDelegate(PermanentUITaskDelegate&&) = delete;

			auto operator=(const PermanentUITaskDelegate&) -> PermanentUITaskDelegate& = delete;
			auto operator=(PermanentUITaskDelegate&&) -> PermanentUITaskDelegate& = delete;

			void Reschedule() override;

		private:
			REX::NotNull<const TaskInterface*> _taskInterface;
		};

		void PermanentTaskDelegate::Reschedule()
		{
			_taskInterface->AddUITask(
				std::make_unique<PermanentUITaskDelegate>(
					_taskInterface,
					std::move(_taskState),
					std::move(_taskDelegate)));
		}

		void PermanentUITaskDelegate::Reschedule()
		{
			_taskInterface->AddTask(
				std::make_unique<PermanentTaskDelegate>(
					_taskInterface,
					std::move(_taskState),
					std::move(_taskDelegate)));
		}
	}
}

namespace F4SE
{
	auto TaskInterface::GetVersion() const noexcept -> F4SE::InterfaceVersion
	{
		return Impl::GetProxy(*this).interfaceVersion;
	}

	void TaskInterface::AddTask(REX::NotNull<std::unique_ptr<ITaskDelegate>> a_task) const
	{
		Impl::GetProxy(*this).addTask(a_task.get().release());
	}

	void TaskInterface::AddTask(REX::NotNull<std::move_only_function<TaskCallback>> a_task) const
	{
		AddTask(std::make_unique<TaskDelegate>(std::move(a_task)));
	}

	void TaskInterface::AddUITask(REX::NotNull<std::unique_ptr<ITaskDelegate>> a_task) const
	{
		Impl::GetProxy(*this).addUITask(a_task.get().release());
	}

	void TaskInterface::AddUITask(REX::NotNull<std::move_only_function<TaskCallback>> a_task) const
	{
		AddUITask(std::make_unique<TaskDelegate>(std::move(a_task)));
	}

	void TaskInterface::AddTaskPermanent(REX::NotNull<std::unique_ptr<ITaskDelegate>> a_task) const
	{
		if (!F4SE::IsRuntimeAtLeastNG()) {
			AddTask(
				std::make_unique<Impl::PermanentTaskDelegate>(
					this,
					std::make_unique<Impl::PermanentTaskState>(),
					std::move(a_task)));
			return;
		}

		Impl::GetProxy(*this).addTaskPermanent(a_task.get().release());
	}

	void TaskInterface::AddTaskPermanent(REX::NotNull<std::move_only_function<TaskCallback>> a_task) const
	{
		auto taskDelegate = std::make_unique<TaskDelegate>(std::move(a_task));

		if (!F4SE::IsRuntimeAtLeastNG()) {
			AddTask(
				std::make_unique<Impl::PermanentTaskDelegate>(
					this,
					std::make_unique<Impl::PermanentTaskState>(),
					std::move(taskDelegate)));
			return;
		}

		AddTaskPermanent(std::move(taskDelegate));
	}

	void TaskInterface::AddUITaskPermanent(REX::NotNull<std::unique_ptr<ITaskDelegate>> a_task) const
	{
		AddUITask(
			std::make_unique<Impl::PermanentUITaskDelegate>(
				this,
				std::make_unique<Impl::PermanentTaskState>(),
				std::move(a_task)));
	}

	void TaskInterface::AddUITaskPermanent(REX::NotNull<std::move_only_function<TaskCallback>> a_task) const
	{
		AddUITask(
			std::make_unique<Impl::PermanentUITaskDelegate>(
				this,
				std::make_unique<Impl::PermanentTaskState>(),
				std::make_unique<TaskDelegate>(std::move(a_task))));
	}
}
