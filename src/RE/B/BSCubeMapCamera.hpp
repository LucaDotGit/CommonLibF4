#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiCamera.hpp"
#include "RE/N/NiColorA.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSShaderAccumulator;

	class __declspec(novtable) BSCubeMapCamera : public NiCamera // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSCubeMapCamera;
		inline static constexpr const auto& VTABLE = VTABLE::BSCubeMapCamera;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSCubeMapCamera;

		enum class FaceEnableFlags : std::uint32_t
		{
			None = 0,
			EnablePosX = 1 << 0,
			EnableNegX = 1 << 1,
			EnablePosY = 1 << 2,
			EnableNegY = 1 << 3,
			EnablePosZ = 1 << 4,
			EnableNegZ = 1 << 5,

			EnableAll = EnablePosX | EnableNegX | EnablePosY | EnableNegY | EnablePosZ | EnableNegZ
		};

		enum class Face : std::int32_t
		{
			PosX = 0,
			NegX = 1,
			PosY = 2,
			NegY = 3,
			PosZ = 4,
			NegZ = 5
		};

		// add
		virtual void Click(
			FaceEnableFlags a_faceEnableFlags,
			bool a_silhouette,
			bool a_clearScene,
			bool a_LODOnly); // 0x3A

		// members
		BSTArray<NiPointer<NiAVObject>> cubeMapScene;		  // 0x1A0
		NiPointer<BSShaderAccumulator> accumulator;			  // 0x1B8
		NiPointer<BSShaderAccumulator> accumulatorBackground; // 0x1C0
		NiPointer<NiCamera> cameraBackground;				  // 0x1C8
		NiColorA silhouetteColor;							  // 0x1D0
	};

	static_assert(sizeof(BSCubeMapCamera) == 0x1E0);
}
