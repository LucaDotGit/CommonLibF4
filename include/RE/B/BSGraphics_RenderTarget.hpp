#pragma once

namespace RE::BSGraphics
{
	class RenderTarget
	{
	public:
		// members
		REX::W32::ID3D11Texture2D* texture;				// 00
		REX::W32::ID3D11Texture2D* copyTexture;			// 08
		REX::W32::ID3D11RenderTargetView* rtView;		// 10
		REX::W32::ID3D11ShaderResourceView* srView;		// 18
		REX::W32::ID3D11ShaderResourceView* copySRView; // 20
		REX::W32::ID3D11UnorderedAccessView* uaView;	// 28
	};
	static_assert(sizeof(RenderTarget) == 0x30);
}
