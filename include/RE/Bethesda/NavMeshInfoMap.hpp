#pragma once

#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/BSTSingleton.hpp"
#include "RE/Bethesda/TESForms.hpp"

namespace RE
{
	class BSNavmeshInfo;
	class NavMeshInfo;

	class __declspec(novtable) BSNavmeshInfoMap
		: public BSTSingletonExplicit<BSNavmeshInfoMap> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSNavmeshInfoMap };
		inline static constexpr auto VTABLE{ VTABLE::BSNavmeshInfoMap };

		struct IVisitor;

		virtual ~BSNavmeshInfoMap(); // 00

		// add
		virtual BSNavmeshInfo* GetNavMeshInfoFixID(std::uint32_t a_navMeshID) = 0;												 // 01
		virtual BSNavmeshInfo* GetNavmeshInfo(std::uint32_t a_navMeshID) = 0;													 // 02
		virtual void GetAllNavMeshInfo(BSTArray<BSNavmeshInfo*>* a_returnArray) = 0;											 // 03
		virtual void BuildListOfConnectedInfos(const BSNavmeshInfo* a_navMeshInfo, BSTArray<BSNavmeshInfo*>* a_returnArray) = 0; // 04
		virtual void ForEach(IVisitor& a_visitor) = 0;																			 // 05
	};
	static_assert(sizeof(BSNavmeshInfoMap) == 0x8);

	class BSPrecomputedNavmeshInfoPathMap
		: public BSTSingletonExplicit<BSPrecomputedNavmeshInfoPathMap> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSPrecomputedNavmeshInfoPathMap };

		// members
		BSTArray<BSTArray<const BSNavmeshInfo*>*> allPaths;				// 00
		BSTHashMap<const BSNavmeshInfo*, std::uint32_t> infoToIndexMap; // 18
	};
	static_assert(sizeof(BSPrecomputedNavmeshInfoPathMap) == 0x48);

	class PrecomputedNavmeshInfoPathMap
		: public BSPrecomputedNavmeshInfoPathMap // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PrecomputedNavmeshInfoPathMap };
	};
	static_assert(sizeof(PrecomputedNavmeshInfoPathMap) == 0x48);

	class __declspec(novtable) NavMeshInfoMap
		: public TESForm,					   // 000
		  public BSNavmeshInfoMap,			   // 020
		  public PrecomputedNavmeshInfoPathMap // 030
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NavMeshInfoMap };
		inline static constexpr auto VTABLE{ VTABLE::NavMeshInfoMap };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kNAVI };

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
