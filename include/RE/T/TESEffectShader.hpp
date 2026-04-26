#pragma once

#include "RE/E/EffectShaderData.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESModel.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class BSGeometry;

	class __declspec(novtable) TESEffectShader
		: public TESForm, // 000
		  public TESModel // 020
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESEffectShader };
		inline static constexpr auto VTABLE{ VTABLE::TESEffectShader };
		inline static constexpr auto FORM_TYPE{ FormType::kEffectShader };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		EffectShaderData data;					 // 050
		TESTexture textureShaderTexture;		 // 0F8
		TESTexture blockOutTexture;				 // 108
		TESTexture paletteTexture;				 // 118
		NiPointer<BSGeometry> shareableGeometry; // 128
	};
	static_assert(sizeof(TESEffectShader) == 0x130);
}
