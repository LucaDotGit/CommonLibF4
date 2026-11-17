#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TEXTURE_HAVOK_DATA.hpp"

namespace RE
{
	class __declspec(novtable) TESLandTexture : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESLandTexture;
		inline static constexpr const auto& VTABLE = VTABLE::TESLandTexture;
		inline static constexpr auto FORM_TYPE = FormType::LandscapeTexture;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BGSTextureSet* textureSet;				  // 0x20
		TEXTURE_HAVOK_DATA havokData;			  // 0x28
		BGSMaterialType* materialType;			  // 0x30
		std::int8_t specularExponent;			  // 0x38
		std::int32_t shaderTextureIndex;		  // 0x3C
		BSSimpleList<TESGrass*> textureGrassList; // 0x40
	};

	static_assert(sizeof(TESLandTexture) == 0x50);
}
