#include "RE/G/GameVM.hpp"

#include "RE/B/BSScript_Internal_VirtualMachine.hpp"

namespace RE
{
	auto GameVM::GetSingleton() noexcept -> GameVM*
	{
		static const auto SINGLETON = REL::Relocation<GameVM**>(ID::GameScript::GameVM::Singleton);
		return *SINGLETON;
	}

	auto GameVM::GetVMInterface() noexcept -> BSTSmartPointer<BSScript::IVirtualMachine>
	{
		const auto* singleton = GetSingleton();
		if (!singleton) {
			return nullptr;
		}

		return singleton->impl;
	}

	auto GameVM::GetInternalVM() noexcept -> BSTSmartPointer<BSScript::Internal::VirtualMachine>
	{
		const auto* singleton = GetSingleton();
		if (!singleton) {
			return nullptr;
		}

		return dynamic_pointer_cast<BSScript::Internal::VirtualMachine>(singleton->impl);
	}

	auto GameVM::GetRuntimeData() noexcept -> GameVM::RuntimeData&
	{
		return REL::GetMemberAt<RuntimeData>(Offset::GameVM::RuntimeData, this);
	}

	auto GameVM::GetRuntimeData() const noexcept -> const GameVM::RuntimeData&
	{
		return REL::GetMemberAt<const RuntimeData>(Offset::GameVM::RuntimeData, this);
	}

	auto GameVM::QueuePostRenderCall(const BSTSmartPointer<GameScript::DelayFunctor>& a_functor) -> bool
	{
		using FuncType = decltype(&GameVM::QueuePostRenderCall);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GameScript::GameVM::QueuePostRenderCall);
		return std::invoke(FUNC, this, a_functor);
	}

	void GameVM::RegisterForAllGameEvents()
	{
		using FuncType = decltype(&GameVM::RegisterForAllGameEvents);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GameScript::GameVM::RegisterForAllGameEvents);
		std::invoke(FUNC, this);
	}

	void GameVM::SendEventToObjectAndRelated(
		BSScript::ObjectHandle a_object,
		const BSFixedString& a_eventName,
		const BSTThreadScrapFunction<bool(BSScrapArray<BSScript::Variable>&)>& a_args,
		const BSTThreadScrapFunction<bool(const BSTSmartPointer<BSScript::Object>&)>& a_filter,
		const BSTSmartPointer<BSScript::IStackCallbackFunctor>& a_callbackFunctor)
	{
		using FuncType = decltype(&GameVM::SendEventToObjectAndRelated);
		static const auto FUNC = REL::Relocation<FuncType>(ID::GameScript::GameVM::SendEventToObjectAndRelated);
		std::invoke(FUNC, this, a_object, a_eventName, a_args, a_filter, a_callbackFunctor);
	}
}
