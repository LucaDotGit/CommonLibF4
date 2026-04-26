#pragma once

namespace RE::BSGraphics
{
	class OcclusionQuery
	{
	public:
		// members
		REX::W32::ID3D11Query* occlusionQuery; // 00
		std::uint32_t inUse;				   // 08
	};
	static_assert(sizeof(OcclusionQuery) == 0x10);
}
