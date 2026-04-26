#pragma once

#include "RE/B/BSNavmeshInfoMap.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/P/PrecomputedNavmeshInfoPathMap.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class BSNavmeshInfo;
	class NavMeshInfo;

	class __declspec(novtable) NavMeshInfoMap
		: public TESForm,					   // 000
		  public BSNavmeshInfoMap,			   // 020
		  public PrecomputedNavmeshInfoPathMap // 030
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NavMeshInfoMap };
		inline static constexpr auto VTABLE{ VTABLE::NavMeshInfoMap };
		inline static constexpr auto FORM_TYPE{ FormType::kNavMeshInfoMap };

		~NavMeshInfoMap() override; // 00

		GAME_HEAP_REDEFINE_NEW(NavMeshInfoMap);

		// members
		bool updateAll;														 // 078
		BSTArray<BSNavmeshInfo*> staleNavmeshInfos;							 // 080
		BSTHashMap<std::uint32_t, NavMeshInfo*> infoMap;					 // 098
		BSTHashMap<std::size_t, BSTArray<BSNavmeshInfo*>*> ckNavMeshInfoMap; // 0C8
		mutable BSReadWriteLock mapLock;									 // 0F8
		bool init;															 // 100
	};
	static_assert(sizeof(NavMeshInfoMap) == 0x108);
}
