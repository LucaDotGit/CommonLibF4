#pragma once

namespace RE::BSGraphics
{
	class DepthStencilTarget
	{
	public:
		// members
		REX::W32::ID3D11Texture2D* texture;											 // 0x00
		std::array<REX::W32::ID3D11DepthStencilView*, 4> dsView;					 // 0x08
		std::array<REX::W32::ID3D11DepthStencilView*, 4> dsViewReadOnlyDepth;		 // 0x28
		std::array<REX::W32::ID3D11DepthStencilView*, 4> dsViewReadOnlyStencil;		 // 0x48
		std::array<REX::W32::ID3D11DepthStencilView*, 4> dsViewReadOnlyDepthStencil; // 0x68
		REX::W32::ID3D11ShaderResourceView* srViewDepth;							 // 0x88
		REX::W32::ID3D11ShaderResourceView* srViewStencil;							 // 0x90
	};

	static_assert(sizeof(DepthStencilTarget) == 0x98);
}
