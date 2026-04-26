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

	class __declspec(novtable) BSShader
		: public NiRefObject,	 // 000
		  public BSReloadShaderI // 010
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSShader };
		inline static constexpr auto VTABLE{ VTABLE::BSShader };

		// add
		virtual bool SetupTechnique(std::uint32_t a_currentPass) = 0;											// 02
		virtual void RestoreTechnique(std::uint32_t a_currentPass) = 0;											// 03
		virtual void SetupMaterial(const BSShaderMaterial* a_material);											// 04 - { return; }
		virtual void RestoreMaterial(const BSShaderMaterial* a_material);										// 05 - { return; }
		virtual void SetupMaterialSecondary(const BSShaderMaterial* a_material);								// 06 - { return; }
		virtual void SetupGeometry(BSRenderPass* a_currentPass) = 0;											// 07
		virtual void RestoreGeometry(BSRenderPass* a_currentPass) = 0;											// 08
		virtual void GetTechniqueName(std::uint32_t a_techniqueID, char* a_buffer, std::uint32_t a_bufferSize); // 09
		virtual void RecreateRendererData();																	// 0A - { return; }
		virtual void ReloadShaders(bool a_clear);																// 0B
		virtual std::uint32_t GetBonesVertexConstant() const;													// 0C - { return 0; }

		// members
		std::int32_t shaderType;													// 018
		BSShaderTechniqueIDMap::MapType<BSGraphics::VertexShader*> vertexShaders;	// 020
		BSShaderTechniqueIDMap::MapType<BSGraphics::HullShader*> hullShaders;		// 050
		BSShaderTechniqueIDMap::MapType<BSGraphics::DomainShader*> domainShaders;	// 080
		BSShaderTechniqueIDMap::MapType<BSGraphics::PixelShader*> pixelShaders;		// 0B0
		BSShaderTechniqueIDMap::MapType<BSGraphics::ComputeShader*> computeShaders; // 0E0
		const char* fxpFilename;													// 110
	};
	static_assert(sizeof(BSShader) == 0x118);
}
