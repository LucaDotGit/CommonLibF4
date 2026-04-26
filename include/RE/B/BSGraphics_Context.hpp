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
		REX::W32::ID3D11DeviceContext* deferredContext;								  // 0000
		std::array<REX::W32::ID3D11Buffer*, 541> shaderConstantBuffer;				  // 0008
		std::array<REX::W32::ID3D11Buffer*, 20> vertexShaderConstantBufferTechnique;  // 10F0
		std::array<REX::W32::ID3D11Buffer*, 10> vertexShaderConstantBufferMaterial;	  // 1190
		std::array<REX::W32::ID3D11Buffer*, 28> vertexShaderConstantBufferGeometry;	  // 11E0
		std::array<REX::W32::ID3D11Buffer*, 20> hullShaderConstantBufferTechnique;	  // 12C0
		std::array<REX::W32::ID3D11Buffer*, 10> hullShaderConstantBufferMaterial;	  // 1360
		std::array<REX::W32::ID3D11Buffer*, 20> hullShaderConstantBufferGeometry;	  // 13B0
		std::array<REX::W32::ID3D11Buffer*, 20> domainShaderConstantBufferTechnique;  // 1450
		std::array<REX::W32::ID3D11Buffer*, 10> domainShaderConstantBufferMaterial;	  // 14F0
		std::array<REX::W32::ID3D11Buffer*, 20> domainShaderConstantBufferGeometry;	  // 1540
		std::array<REX::W32::ID3D11Buffer*, 36> pixelShaderConstantBufferTechnique;	  // 15E0
		std::array<REX::W32::ID3D11Buffer*, 20> pixelShaderConstantBufferMaterial;	  // 1700
		std::array<REX::W32::ID3D11Buffer*, 40> pixelShaderConstantBufferGeometry;	  // 17A0
		std::array<REX::W32::ID3D11Buffer*, 20> computeShaderConstantBufferTechnique; // 18E0
		std::array<REX::W32::ID3D11Buffer*, 20> computeShaderConstantBufferMaterial;  // 1980
		std::array<REX::W32::ID3D11Buffer*, 34> computeShaderConstantBufferGeometry;  // 1A20
		REX::W32::ID3D11Buffer* alphaTestConstantBuffer;							  // 1B30
		REX::W32::ID3D11Buffer* perFrameConstantBuffer;								  // 1B38
		REX::W32::ID3D11Buffer* computeConstantBuffer;								  // 1B40
		REX::W32::ID3D11Buffer* instanceTransformConstantBuffer;					  // 1B48
		ConstantGroup miscConstantGroup;											  // 1B50
		RendererShadowState shadowState;											  // 1B70
		RendererShadowState lastDrawCallShadowState;								  // 2480
		std::array<REX::W32::ID3D11Buffer*, 8> dynamicVertexBuffer;					  // 2D90
		std::array<REX::W32::ID3D11Query*, 8> dynamicVertexBufferAvailQuery;		  // 2DD0
		std::array<std::int32_t, 8> dynamicVertexBufferAvail;						  // 2E10
		std::uint32_t currentDynamicVertexBuffer;									  // 2E30
		std::uint32_t currentDynamicVertexBufferOffset;								  // 2E34
		REX::W32::ID3D11Buffer* sharedParticleIndexBuffer;							  // 2E38
		REX::W32::ID3D11Buffer* sharedParticleStaticBuffer;							  // 2E40
		std::array<ConstantGroup, 3> vertexConstantBuffers;							  // 2E48
		std::array<ConstantGroup, 3> pixelConstantBuffers;							  // 2E90
		std::array<ConstantGroup, 3> domainConstantBuffers;							  // 2ED8
		std::array<ConstantGroup, 3> hullConstantBuffers;							  // 2F20
		std::array<ConstantGroup, 3> computeConstantBuffers;						  // 2F68
		BSTHashMap<std::uint64_t, REX::W32::ID3D11InputLayout*> inputLayoutMap;		  // 2FB0
		REX::W32::ID3D11InputLayout* particleShaderInputLayout;						  // 2FE0
	};
	static_assert(sizeof(Context) == 0x2FF0);
}
