#pragma once

#include "RE/E/EffectShaderData.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESModel.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class BSGeometry;

	class __declspec(novtable) TESEffectShader :
		public TESForm, // 0x000
		public TESModel // 0x020
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESEffectShader;
		inline static constexpr const auto& VTABLE = VTABLE::TESEffectShader;
		inline static constexpr auto FORM_TYPE = FormType::EffectShader;

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
		EffectShaderData data;					 // 0x050
		TESTexture textureShaderTexture;		 // 0x0F8
		TESTexture blockOutTexture;				 // 0x108
		TESTexture paletteTexture;				 // 0x118
		NiPointer<BSGeometry> shareableGeometry; // 0x128
	};

	static_assert(sizeof(TESEffectShader) == 0x130);
}
