#pragma once

namespace RE::BSGraphics
{
	class OcclusionQuery
	{
	public:
		// members
		REX::W32::ID3D11Query* occlusionQuery; // 0x00
		std::uint32_t inUse;				   // 0x08
	};

	static_assert(sizeof(OcclusionQuery) == 0x10);
}
