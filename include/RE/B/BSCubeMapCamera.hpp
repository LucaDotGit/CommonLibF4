#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiCamera.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSShaderAccumulator;

	class __declspec(novtable) BSCubeMapCamera
		: public NiCamera // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSCubeMapCamera };
		inline static constexpr auto VTABLE{ VTABLE::BSCubeMapCamera };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSCubeMapCamera };

		enum class FaceEnableFlags : std::uint32_t
		{
			kNone = 0,
			kEnablePosX = 1 << 0,
			kEnableNegX = 1 << 1,
			kEnablePosY = 1 << 2,
			kEnableNegY = 1 << 3,
			kEnablePosZ = 1 << 4,
			kEnableNegZ = 1 << 5,

			kEnableAll = kEnablePosX | kEnableNegX | kEnablePosY | kEnableNegY | kEnablePosZ | kEnableNegZ
		};

		enum class Face : std::int32_t
		{
			kPosX = 0x0,
			kNegX = 0x1,
			kPosY = 0x2,
			kNegY = 0x3,
			kPosZ = 0x4,
			kNegZ = 0x5
		};

		// add
		virtual void Click(FaceEnableFlags a_faceEnableFlags, bool a_silhouette, bool a_clearScene, bool a_LODOnly); // 3A

		// members
		BSTArray<NiPointer<NiAVObject>> cubeMapScene;		  // 1A0
		NiPointer<BSShaderAccumulator> accumulator;			  // 1B8
		NiPointer<BSShaderAccumulator> accumulatorBackground; // 1C0
		NiPointer<NiCamera> cameraBackground;				  // 1C8
		NiColorA silhouetteColor;							  // 1D0
	};
	static_assert(sizeof(BSCubeMapCamera) == 0x1E0);
}
