#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/C/CubeMapSide.hpp"
#include "RE/N/NiPlane.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class BSCubeMapCamera;
	class BSWaterShaderMaterial;
	class BSShaderAccumulator;
	class BSCullingProcess;

	class __declspec(novtable) TESWaterReflections : public NiRefObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESWaterReflections;
		inline static constexpr const auto& VTABLE = VTABLE::TESWaterReflections;

		enum class Flags : std::uint16_t
		{
			None = 0,
			Dirty = 1 << 0,
			StaticCubemap = 1 << 1,
			DynamicCubemap = 1 << 2,
			Interior = 1 << 3,
			Silhouette = 1 << 4,
			LODScene = 1 << 5,
			FullScene = 1 << 6,
			Land = 1 << 7,
			Sky = 1 << 8,
			Explosions = 1 << 9,
			Selective = 1 << 10,
			DoNotUpdate = 1 << 11,
			MapMode = 1 << 12
		};

		// members
		REX::EnumSet<Flags, std::uint16_t> flags;			  // 0x10
		NiPlane reflectWaterPlane;							  // 0x14
		NiPointer<BSCubeMapCamera> cubeMapCamera;			  // 0x28
		NiPointer<BSShaderAccumulator> sorter;				  // 0x30
		BSCullingProcess* cullingProcess;					  // 0x38
		BSTSmartPointer<BSWaterShaderMaterial> waterMaterial; // 0x40
		REX::Float32 reflectionUpdateTimer;					  // 0x48
		std::uint32_t currentCubeMapFace;					  // 0x4C
		std::array<CubeMapSide, 6> sortedCubeMapSide;		  // 0x50
		bool activeThisFrame;								  // 0x80
	};

	static_assert(sizeof(TESWaterReflections) == 0x88);
}
