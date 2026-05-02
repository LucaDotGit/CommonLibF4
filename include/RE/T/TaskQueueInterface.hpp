#pragma once

#include "RE/B/BGSEquipIndex.hpp"
#include "RE/D/DEFAULT_OBJECT.hpp"

namespace RE
{
	class BSPackedTask;
	class BSPackedTaskQueue;
	class NiAVObject;

	class TaskQueueInterface
	{
	public:
		static TaskQueueInterface* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<TaskQueueInterface**>{ ID::TaskQueueInterface::Singleton };
			return *SINGLETON;
		}

		void QueueClosePipboy()
		{
			using FuncType = decltype(&TaskQueueInterface::QueueClosePipboy);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TaskQueueInterface::QueueClosePipboy };
			FUNC(this);
		}

		void QueueRebuildBendableSpline(TESObjectREFR& a_ref, bool a_createPhysics, NiAVObject* a_childNode)
		{
			using FuncType = decltype(&TaskQueueInterface::QueueRebuildBendableSpline);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TaskQueueInterface::QueueRebuildBendableSpline };
			FUNC(this, a_ref, a_createPhysics, a_childNode);
		}

		void QueueShow1stPerson(bool a_show1stPerson)
		{
			using FuncType = decltype(&TaskQueueInterface::QueueShow1stPerson);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TaskQueueInterface::QueueShow1stPerson };
			FUNC(this, a_show1stPerson);
		}

		void QueueShowPipboy(DEFAULT_OBJECT a_animType)
		{
			using FuncType = decltype(&TaskQueueInterface::QueueShowPipboy);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TaskQueueInterface::QueueShowPipboy };
			FUNC(this, a_animType);
		}

		void QueueUpdate3D(TESObjectREFR* a_ref, std::uint32_t a_flags)
		{
			using FuncType = decltype(&TaskQueueInterface::QueueUpdate3D);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TaskQueueInterface::QueueUpdate3D };
			FUNC(this, a_ref, a_flags);
		}

		void QueueWeaponFire(TESObjectWEAP* a_weapon, TESObjectREFR* a_refObject, BGSEquipIndex a_equipIndex, TESAmmo* a_ammo)
		{
			using FuncType = decltype(&TaskQueueInterface::QueueWeaponFire);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TaskQueueInterface::QueueWeaponFire };
			FUNC(this, a_weapon, a_refObject, a_equipIndex, a_ammo);
		}

		void TaskUnpackFunc(const BSPackedTask& a_task)
		{
			using FuncType = decltype(&TaskQueueInterface::TaskUnpackFunc);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TaskQueueInterface::TaskUnpackFunc };
			FUNC(this, a_task);
		}

		// members
		BSPackedTaskQueue* queue;		   // 00
		BSPackedTaskQueue* secondaryQueue; // 08
		BSPackedTaskQueue* activeQueue;	   // 18
	};
	static_assert(sizeof(TaskQueueInterface) == 0x18);
}
