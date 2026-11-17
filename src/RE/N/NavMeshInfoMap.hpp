#pragma once

#include "RE/B/BSNavmeshInfoMap.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/P/PrecomputedNavmeshInfoPathMap.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class BSNavmeshInfo;
	class NavMeshInfo;

	class __declspec(novtable) NavMeshInfoMap :
		public TESForm,						 // 0x000
		public BSNavmeshInfoMap,			 // 0x020
		public PrecomputedNavmeshInfoPathMap // 0x030
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NavMeshInfoMap;
		inline static constexpr const auto& VTABLE = VTABLE::NavMeshInfoMap;
		inline static constexpr auto FORM_TYPE = FormType::NavMeshInfoMap;

		~NavMeshInfoMap() override; // 0x00

		GAME_HEAP_REDEFINE_NEW(NavMeshInfoMap);

		// members
		bool updateAll;														 // 0x078
		BSTArray<BSNavmeshInfo*> staleNavmeshInfos;							 // 0x080
		BSTHashMap<std::uint32_t, NavMeshInfo*> infoMap;					 // 0x098
		BSTHashMap<std::size_t, BSTArray<BSNavmeshInfo*>*> ckNavMeshInfoMap; // 0x0C8
		mutable BSReadWriteLock mapLock;									 // 0x0F8
		bool init;															 // 0x100
	};

	static_assert(sizeof(NavMeshInfoMap) == 0x108);
}
