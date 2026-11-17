#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"

namespace RE
{
	class BSNavmeshInfo;

	class __declspec(novtable) BSNavmeshInfoMap : public BSTSingletonExplicit<BSNavmeshInfoMap> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSNavmeshInfoMap;
		inline static constexpr const auto& VTABLE = VTABLE::BSNavmeshInfoMap;

		class IVisitor;

		virtual ~BSNavmeshInfoMap(); // 0x00

		// add
		virtual auto GetNavMeshInfoFixID(std::uint32_t a_navMeshID) -> BSNavmeshInfo* = 0; // 0x01
		virtual auto GetNavmeshInfo(std::uint32_t a_navMeshID) -> BSNavmeshInfo* = 0;	   // 0x02
		virtual void GetAllNavMeshInfo(BSTArray<BSNavmeshInfo*>* a_returnArray) = 0;	   // 0x03
		virtual void BuildListOfConnectedInfos(
			const BSNavmeshInfo* a_navMeshInfo,
			BSTArray<BSNavmeshInfo*>* a_returnArray) = 0; // 0x04
		virtual void ForEach(IVisitor& a_visitor) = 0;	  // 0x05
	};

	static_assert(sizeof(BSNavmeshInfoMap) == 0x08);
}
