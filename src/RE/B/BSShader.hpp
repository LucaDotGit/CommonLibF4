#pragma once

#include "RE/B/BSReloadShaderI.hpp"
#include "RE/B/BSShaderTechniqueIDMap.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE::BSGraphics
{
	class ComputeShader;
	class DomainShader;
	class HullShader;
	class PixelShader;
	class VertexShader;
}

namespace RE
{
	class BSRenderPass;
	class BSShaderMaterial;

	class __declspec(novtable) BSShader :
		public NiRefObject,	   // 0x000
		public BSReloadShaderI // 0x010
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSShader;
		inline static constexpr const auto& VTABLE = VTABLE::BSShader;

		~BSShader() override; // 0x00

		// add
		virtual auto SetupTechnique(std::uint32_t a_currentPass) -> bool = 0;	 // 0x02
		virtual void RestoreTechnique(std::uint32_t a_currentPass) = 0;			 // 0x03
		virtual void SetupMaterial(const BSShaderMaterial* a_material);			 // 0x04 - { return; }
		virtual void RestoreMaterial(const BSShaderMaterial* a_material);		 // 0x05 - { return; }
		virtual void SetupMaterialSecondary(const BSShaderMaterial* a_material); // 0x06 - { return; }
		virtual void SetupGeometry(BSRenderPass* a_currentPass) = 0;			 // 0x07
		virtual void RestoreGeometry(BSRenderPass* a_currentPass) = 0;			 // 0x08
		virtual void GetTechniqueName(std::uint32_t a_techniqueID, char* a_buffer, std::uint32_t a_bufferSize); // 0x09
		virtual void RecreateRendererData();						  // 0x0A - { return; }
		virtual void ReloadShaders(bool a_clear);					  // 0x0B
		virtual auto GetBonesVertexConstant() const -> std::uint32_t; // 0x0C - { return 0; }

		// members
		std::int32_t shaderType;													// 0x018
		BSShaderTechniqueIDMap::MapType<BSGraphics::VertexShader*> vertexShaders;	// 0x020
		BSShaderTechniqueIDMap::MapType<BSGraphics::HullShader*> hullShaders;		// 0x050
		BSShaderTechniqueIDMap::MapType<BSGraphics::DomainShader*> domainShaders;	// 0x080
		BSShaderTechniqueIDMap::MapType<BSGraphics::PixelShader*> pixelShaders;		// 0x0B0
		BSShaderTechniqueIDMap::MapType<BSGraphics::ComputeShader*> computeShaders; // 0x0E0
		const char* fxpFilename;													// 0x110
	};

	static_assert(sizeof(BSShader) == 0x118);
}
