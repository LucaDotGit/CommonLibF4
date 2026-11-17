#pragma once

namespace RE
{
	class hkStridedVertices
	{
	public:
		// members
		REX::Float32* vertices{nullptr}; // 0x00
		std::int32_t numVertices{0};	 // 0x08
		std::int32_t striding{0};		 // 0x0C
	};

	static_assert(sizeof(hkStridedVertices) == 0x10);
}
