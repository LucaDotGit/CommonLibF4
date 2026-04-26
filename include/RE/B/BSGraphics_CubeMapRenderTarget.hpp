#pragma once

namespace RE::BSGraphics
{
	class CubeMapRenderTarget
	{
	public:
		// members
		REX::W32::ID3D11Texture2D* texture;						 // 00
		std::array<REX::W32::ID3D11RenderTargetView*, 6> rtView; // 08
		REX::W32::ID3D11ShaderResourceView* srView;				 // 38
	};
	static_assert(sizeof(CubeMapRenderTarget) == 0x40);
}
