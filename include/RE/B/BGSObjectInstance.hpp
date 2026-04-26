#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/T/TBO_InstanceData.hpp"

namespace RE
{
	class BGSObjectInstance
	{
	public:
		BGSObjectInstance(TESForm* a_object, TBO_InstanceData* a_instanceData)
		{
			using FuncType = void (BGSObjectInstance::*)(TESForm*, TBO_InstanceData*);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSObjectInstance::ctor };
			FUNC(this, a_object, a_instanceData);
		}

		// members
		TESForm* object{ nullptr };						// 00
		BSTSmartPointer<TBO_InstanceData> instanceData; // 08
	};
	static_assert(sizeof(BGSObjectInstance) == 0x10);

	template <class T>
	class BGSObjectInstanceT
		: public BGSObjectInstance // 00
	{
	public:
		BGSObjectInstanceT(T* a_object, TBO_InstanceData* a_instanceData)
			: BGSObjectInstance(a_object, a_instanceData)
		{
		}
	};
}
