#pragma once

#include "RE/B/BSGraphics_ConstantGroup.hpp"
#include "RE/B/BSGraphics_RendererShadowState.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE::BSGraphics
{
	class Context
	{
	public:
		// members
		REX::W32::ID3D11DeviceContext* deferredContext;								  // 0x0000
		std::array<REX::W32::ID3D11Buffer*, 541> shaderConstantBuffer;				  // 0x0008
		std::array<REX::W32::ID3D11Buffer*, 20> vertexShaderConstantBufferTechnique;  // 0x10F0
		std::array<REX::W32::ID3D11Buffer*, 10> vertexShaderConstantBufferMaterial;	  // 0x1190
		std::array<REX::W32::ID3D11Buffer*, 28> vertexShaderConstantBufferGeometry;	  // 0x11E0
		std::array<REX::W32::ID3D11Buffer*, 20> hullShaderConstantBufferTechnique;	  // 0x12C0
		std::array<REX::W32::ID3D11Buffer*, 10> hullShaderConstantBufferMaterial;	  // 0x1360
		std::array<REX::W32::ID3D11Buffer*, 20> hullShaderConstantBufferGeometry;	  // 0x13B0
		std::array<REX::W32::ID3D11Buffer*, 20> domainShaderConstantBufferTechnique;  // 0x1450
		std::array<REX::W32::ID3D11Buffer*, 10> domainShaderConstantBufferMaterial;	  // 0x14F0
		std::array<REX::W32::ID3D11Buffer*, 20> domainShaderConstantBufferGeometry;	  // 0x1540
		std::array<REX::W32::ID3D11Buffer*, 36> pixelShaderConstantBufferTechnique;	  // 0x15E0
		std::array<REX::W32::ID3D11Buffer*, 20> pixelShaderConstantBufferMaterial;	  // 0x1700
		std::array<REX::W32::ID3D11Buffer*, 40> pixelShaderConstantBufferGeometry;	  // 0x17A0
		std::array<REX::W32::ID3D11Buffer*, 20> computeShaderConstantBufferTechnique; // 0x18E0
		std::array<REX::W32::ID3D11Buffer*, 20> computeShaderConstantBufferMaterial;  // 0x1980
		std::array<REX::W32::ID3D11Buffer*, 34> computeShaderConstantBufferGeometry;  // 0x1A20
		REX::W32::ID3D11Buffer* alphaTestConstantBuffer;							  // 0x1B30
		REX::W32::ID3D11Buffer* perFrameConstantBuffer;								  // 0x1B38
		REX::W32::ID3D11Buffer* computeConstantBuffer;								  // 0x1B40
		REX::W32::ID3D11Buffer* instanceTransformConstantBuffer;					  // 0x1B48
		ConstantGroup miscConstantGroup;											  // 0x1B50
		RendererShadowState shadowState;											  // 0x1B70
		RendererShadowState lastDrawCallShadowState;								  // 0x2480
		std::array<REX::W32::ID3D11Buffer*, 8> dynamicVertexBuffer;					  // 0x2D90
		std::array<REX::W32::ID3D11Query*, 8> dynamicVertexBufferAvailQuery;		  // 0x2DD0
		std::array<std::int32_t, 8> dynamicVertexBufferAvail;						  // 0x2E10
		std::uint32_t currentDynamicVertexBuffer;									  // 0x2E30
		std::uint32_t currentDynamicVertexBufferOffset;								  // 0x2E34
		REX::W32::ID3D11Buffer* sharedParticleIndexBuffer;							  // 0x2E38
		REX::W32::ID3D11Buffer* sharedParticleStaticBuffer;							  // 0x2E40
		std::array<ConstantGroup, 3> vertexConstantBuffers;							  // 0x2E48
		std::array<ConstantGroup, 3> pixelConstantBuffers;							  // 0x2E90
		std::array<ConstantGroup, 3> domainConstantBuffers;							  // 0x2ED8
		std::array<ConstantGroup, 3> hullConstantBuffers;							  // 0x2F20
		std::array<ConstantGroup, 3> computeConstantBuffers;						  // 0x2F68
		BSTHashMap<std::uint64_t, REX::W32::ID3D11InputLayout*> inputLayoutMap;		  // 0x2FB0
		REX::W32::ID3D11InputLayout* particleShaderInputLayout;						  // 0x2FE0
	};

	static_assert(sizeof(Context) == 0x2FF0);
}
