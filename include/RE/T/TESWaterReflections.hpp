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

	class __declspec(novtable) TESWaterReflections
		: public NiRefObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESWaterReflections };
		inline static constexpr auto VTABLE{ VTABLE::TESWaterReflections };

		enum class Flags : std::uint16_t
		{
			kNone = 0,
			kDirty = 1 << 0,
			kStaticCubemap = 1 << 1,
			kDynamicCubemap = 1 << 2,
			kInterior = 1 << 3,
			kSilhouette = 1 << 4,
			kLODScene = 1 << 5,
			kFullScene = 1 << 6,
			kLand = 1 << 7,
			kSky = 1 << 8,
			kExplosions = 1 << 9,
			kSelective = 1 << 10,
			kDoNotUpdate = 1 << 11,
			kMapMode = 1 << 12
		};

		// members
		REX::EnumSet<Flags, std::uint16_t> flags;			  // 10
		NiPlane reflectWaterPlane;							  // 14
		NiPointer<BSCubeMapCamera> cubeMapCamera;			  // 28
		NiPointer<BSShaderAccumulator> sorter;				  // 30
		BSCullingProcess* cullingProcess;					  // 38
		BSTSmartPointer<BSWaterShaderMaterial> waterMaterial; // 40
		REX::Float32 reflectionUpdateTimer;					  // 48
		std::uint32_t currentCubeMapFace;					  // 4C
		std::array<CubeMapSide, 6> sortedCubeMapSide;		  // 50
		bool activeThisFrame;								  // 80
	};
	static_assert(sizeof(TESWaterReflections) == 0x88);
}
