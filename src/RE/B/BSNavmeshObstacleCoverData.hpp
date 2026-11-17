#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class BSNavmeshCoverEdge;

	class BSNavmeshObstacleCoverData : public NiRefObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSNavmeshObstacleCoverData;
		inline static constexpr const auto& VTABLE = VTABLE::BSNavmeshObstacleCoverData;

		enum class Flags : std::uint32_t; // To-Do

		~BSNavmeshObstacleCoverData() override; // 0x00

		// members
		BSTArray<BSNavmeshCoverEdge> coverEdges; // 0x10
		std::uint32_t flags;					 // 0x28
	};

	static_assert(sizeof(BSNavmeshObstacleCoverData) == 0x30);
}
