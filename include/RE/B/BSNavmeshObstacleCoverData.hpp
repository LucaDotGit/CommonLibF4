#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class BSNavmeshCoverEdge;

	class BSNavmeshObstacleCoverData
		: public NiRefObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSNavmeshObstacleCoverData };
		inline static constexpr auto VTABLE{ VTABLE::BSNavmeshObstacleCoverData };

		enum class Flags : std::uint32_t; // TODO

		~BSNavmeshObstacleCoverData() override; // 00

		// members
		BSTArray<BSNavmeshCoverEdge> coverEdges; // 10
		std::uint32_t flags;					 // 28
	};
	static_assert(sizeof(BSNavmeshObstacleCoverData) == 0x30);
}
