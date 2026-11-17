#pragma once

namespace RE::BSGraphics
{
	class RenderTarget
	{
	public:
		// members
		REX::W32::ID3D11Texture2D* texture;				// 0x00
		REX::W32::ID3D11Texture2D* copyTexture;			// 0x08
		REX::W32::ID3D11RenderTargetView* rtView;		// 0x10
		REX::W32::ID3D11ShaderResourceView* srView;		// 0x18
		REX::W32::ID3D11ShaderResourceView* copySRView; // 0x20
		REX::W32::ID3D11UnorderedAccessView* uaView;	// 0x28
	};

	static_assert(sizeof(RenderTarget) == 0x30);
}
