#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSNavmeshGrid.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSNavmeshClosedDoorInfo;
	class BSNavmeshCoverEdge;
	class BSNavmeshEdgeExtraInfo;
	class BSNavmeshInfo;
	class BSNavmeshObstacleData;
	class BSNavmeshObstacleUndoData;
	class BSNavmeshTriangle;
	class BSNavmeshTriangleDoorPortal;
	class BSNavmeshVertex;
	class BSNavmeshWaypoint;
	class BSPathingCell;

	class __declspec(novtable) BSNavmesh : public BSIntrusiveRefCounted // 0x008
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSNavmesh;
		inline static constexpr const auto& VTABLE = VTABLE::BSNavmesh;

		class DisabledLink
		{
		public:
			// members
			std::uint16_t triIndex;	   // 0x00
			std::uint16_t adjTriIndex; // 0x02
			std::int32_t edgeIndex;	   // 0x04
			std::int32_t adjEdgeIndex; // 0x08
		};

		static_assert(sizeof(DisabledLink) == 0x0C);

		virtual ~BSNavmesh(); // 0x00

		// add
		virtual auto QNavmeshID() const -> std::uint32_t = 0; // 0x01

		// members
		BSTArray<BSNavmeshVertex> vertices;													// 0x010
		BSTArray<BSNavmeshTriangle> triangles;												// 0x028
		BSTArray<BSNavmeshEdgeExtraInfo> extraEdgeInfo;										// 0x040
		BSTArray<BSNavmeshTriangleDoorPortal> doorPortals;									// 0x058
		BSTArray<BSNavmeshClosedDoorInfo> closedDoors;										// 0x070
		BSTArray<BSNavmeshCoverEdge> coverArray;											// 0x088
		BSTHashMap<std::uint16_t, std::uint16_t> coverMap;									// 0x0A0
		BSNavmeshGrid meshGrid;																// 0x0D0
		BSTArray<NiPointer<BSNavmeshObstacleUndoData>> obstacles;							// 0x100
		BSTHashMap<std::uint16_t, NiPointer<BSNavmeshObstacleData>>* triangleToObstacleMap; // 0x118
		BSTArray<std::uint16_t> obstaclePOVs;												// 0x120
		BSTHashMap<std::uint32_t, BSTArray<std::uint16_t>*> precuts;						// 0x138
		BSTSet<std::uint32_t> activePrecuts;												// 0x168
		BSTHashMap<std::uint32_t, std::uint32_t> portalSwaps;								// 0x198
		BSTArray<BSNavmesh::DisabledLink> disabledLinks;									// 0x1C8
		BSTSmartPointer<BSPathingCell> parentCell;											// 0x1E0
		BSNavmeshInfo* navmeshInfo;															// 0x1E8
		BSTArray<BSNavmeshWaypoint> waypoints;												// 0x1F0
	};

	static_assert(sizeof(BSNavmesh) == 0x208);
}
