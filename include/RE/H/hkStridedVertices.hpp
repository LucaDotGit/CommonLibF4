#pragma once

namespace RE
{
	class hkStridedVertices
	{
	public:
		// members
		REX::Float32* vertices{ nullptr }; // 00
		std::int32_t numVertices{ 0 };	   // 08
		std::int32_t striding{ 0 };		   // 0C
	};
	static_assert(sizeof(hkStridedVertices) == 0x10);
}
