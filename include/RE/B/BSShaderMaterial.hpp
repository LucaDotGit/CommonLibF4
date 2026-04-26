#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class BSShaderProperty;

	class __declspec(novtable) BSShaderMaterial
		: public BSIntrusiveRefCounted // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSShaderMaterial };
		inline static constexpr auto VTABLE{ VTABLE::BSShaderMaterial };

		enum class Feature : std::int32_t
		{
			kNone = -1,
			kDefault = 0,
			kEnvmap = 1,
			kGlowmap = 2,
			kParallax = 3,
			kFace = 4,
			kSkinTint = 5,
			kHairTint = 6,
			kParallaxOcc = 7,
			kLandscape = 8,
			kLODLandscape = 9,
			kSnow = 10,
			kMultiLayerParallax = 11,
			kTreeAnim = 12,
			kLODObjects = 13,
			kMultiIndexSnow = 14,
			kLODObjectsHD = 15,
			kEye = 16,
			kCloud = 17,
			kLODLandscapeNoise = 18,
			kLODLandscapeBlend = 19,
			kDismemberment = 20
		};

		enum class Type : std::int32_t
		{
			kBase = 0,
			kEffect = 1,
			kLighting = 2,
			kWater = 3
		};

		virtual ~BSShaderMaterial();

		// add
		virtual BSShaderMaterial* Create();												// 01
		virtual void CopyMembers(const BSShaderMaterial* a_other);						// 02
		virtual std::uint32_t ComputeCRC32(std::uint32_t a_uniqueID, bool a_combining); // 03
		virtual BSShaderMaterial* GetDefault();											// 04
		virtual Feature GetFeature();													// 05
		virtual Type GetType();															// 06
		virtual void ReceiveValuesFromRootMaterial(BSShaderProperty* a_property);		// 07
		virtual bool DoIsCopy(const BSShaderMaterial* a_other);							// 08

		// members
		std::array<NiPoint2, 2> texCoordOffset; // 0C
		std::array<NiPoint2, 2> texCoordScale;	// 1C
		std::uint32_t hashKey{ 0 };				// 2C
		std::uint32_t uniqueCode{ 0 };			// 30
	};
	static_assert(sizeof(BSShaderMaterial) == 0x38);
}
