#include "RE/G/GameVM.hpp"

#include "RE/B/BSScript_Internal_VirtualMachine.hpp"

namespace RE
{
	GameVM* GameVM::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<GameVM**>{ ID::GameScript::GameVM::Singleton };
		return *SINGLETON;
	}

	BSTSmartPointer<BSScript::IVirtualMachine> GameVM::GetVMInterface()
	{
		auto* singleton = GetSingleton();
		if (!singleton) {
			return nullptr;
		}

		return singleton->impl;
	}

	BSTSmartPointer<BSScript::Internal::VirtualMachine> GameVM::GetInternalVM()
	{
		auto* singleton = GetSingleton();
		if (!singleton) {
			return nullptr;
		}

		return dynamic_pointer_cast<BSScript::Internal::VirtualMachine>(singleton->impl);
	}

	GameVM::RuntimeData& GameVM::GetRuntimeData() noexcept
	{
		return REL::GetMemberAt<RuntimeData>(Offset::GameVM::RuntimeData, this);
	}

	const GameVM::RuntimeData& GameVM::GetRuntimeData() const noexcept
	{
		return REL::GetMemberAt<const RuntimeData>(Offset::GameVM::RuntimeData, this);
	}

	GameVM::Milliseconds GameVM::GetCurrentTime() const noexcept
	{
		const auto timeLock = BSAutoLock(GetRuntimeData().vmTimeLock);
		return Milliseconds(GetRuntimeData().currentTime);
	}

	GameVM::Milliseconds GameVM::GetCurrentMenuModeTime() const noexcept
	{
		const auto timeLock = BSAutoLock(GetRuntimeData().vmTimeLock);
		return Milliseconds(GetRuntimeData().currentMenuModeTime);
	}

	GameVM::Milliseconds GameVM::GetCurrentGameTime() const noexcept
	{
		const auto timeLock = BSAutoLock(GetRuntimeData().vmTimeLock);
		return Milliseconds(GetRuntimeData().currentGameTime);
	}

	bool GameVM::QueuePostRenderCall(const BSTSmartPointer<GameScript::DelayFunctor>& a_functor)
	{
		using FuncType = decltype(&GameVM::QueuePostRenderCall);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameScript::GameVM::QueuePostRenderCall };
		return std::invoke(FUNC, this, a_functor);
	}

	void GameVM::RegisterForAllGameEvents()
	{
		using FuncType = decltype(&GameVM::RegisterForAllGameEvents);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameScript::GameVM::RegisterForAllGameEvents };
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
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameScript::GameVM::SendEventToObjectAndRelated };
		std::invoke(FUNC, this, a_object, a_eventName, a_args, a_filter, a_callbackFunctor);
	}
}
