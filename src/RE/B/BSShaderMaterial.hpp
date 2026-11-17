#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/N/NiPoint2.hpp"

namespace RE
{
	class BSShaderProperty;

	class __declspec(novtable) BSShaderMaterial : public BSIntrusiveRefCounted // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSShaderMaterial;
		inline static constexpr const auto& VTABLE = VTABLE::BSShaderMaterial;

		enum class Feature : std::int32_t
		{
			None = -1,
			Default = 0,
			Envmap = 1,
			Glowmap = 2,
			Parallax = 3,
			Face = 4,
			SkinTint = 5,
			HairTint = 6,
			ParallaxOcc = 7,
			Landscape = 8,
			LODLandscape = 9,
			Snow = 10,
			MultiLayerParallax = 11,
			TreeAnim = 12,
			LODObjects = 13,
			MultiIndexSnow = 14,
			LODObjectsHD = 15,
			Eye = 16,
			Cloud = 17,
			LODLandscapeNoise = 18,
			LODLandscapeBlend = 19,
			Dismemberment = 20
		};

		enum class Type : std::int32_t
		{
			Base = 0,
			Effect = 1,
			Lighting = 2,
			Water = 3
		};

		virtual ~BSShaderMaterial();

		// add
		virtual auto Create() -> BSShaderMaterial*;												// 0x01
		virtual void CopyMembers(const BSShaderMaterial* a_other);								// 0x02
		virtual auto ComputeCRC32(std::uint32_t a_uniqueID, bool a_combining) -> std::uint32_t; // 0x03
		virtual auto GetDefault() -> BSShaderMaterial*;											// 0x04
		virtual auto GetFeature() -> Feature;													// 0x05
		virtual auto GetType() -> Type;															// 0x06
		virtual void ReceiveValuesFromRootMaterial(BSShaderProperty* a_property);				// 0x07
		virtual auto DoIsCopy(const BSShaderMaterial* a_other) -> bool;							// 0x08

		// members
		std::array<NiPoint2, 2> texCoordOffset; // 0x0C
		std::array<NiPoint2, 2> texCoordScale;	// 0x1C
		std::uint32_t hashKey{0};				// 0x2C
		std::uint32_t uniqueCode{0};			// 0x30
	};

	static_assert(sizeof(BSShaderMaterial) == 0x38);
}
