#pragma once

namespace RE::BSGraphics
{
	class DepthStencilTarget
	{
	public:
		// members
		REX::W32::ID3D11Texture2D* texture;											 // 00
		std::array<REX::W32::ID3D11DepthStencilView*, 4> dsView;					 // 08
		std::array<REX::W32::ID3D11DepthStencilView*, 4> dsViewReadOnlyDepth;		 // 28
		std::array<REX::W32::ID3D11DepthStencilView*, 4> dsViewReadOnlyStencil;		 // 48
		std::array<REX::W32::ID3D11DepthStencilView*, 4> dsViewReadOnlyDepthStencil; // 68
		REX::W32::ID3D11ShaderResourceView* srViewDepth;							 // 88
		REX::W32::ID3D11ShaderResourceView* srViewStencil;							 // 90
	};
	static_assert(sizeof(DepthStencilTarget) == 0x98);
}
