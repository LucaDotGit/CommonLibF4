#pragma once

#include "RE/B/BSGraphics_TextureAddressMode.hpp"
#include "RE/B/BSShaderProperty.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiAVObject;
	class NiTexture;

	class __declspec(novtable) BSBloodSplatterShaderProperty : public BSShaderProperty // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSBloodSplatterShaderProperty;
		inline static constexpr const auto& VTABLE = VTABLE::BSBloodSplatterShaderProperty;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSBloodSplatterShaderProperty;

		~BSBloodSplatterShaderProperty() override; // 0x00

		static void SetFadeSourceRecurse(NiAVObject* a_object, REX::Float32* a_fadeAlpha)
		{
			using FuncType = decltype(&BSBloodSplatterShaderProperty::SetFadeSourceRecurse);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSBloodSplatterShaderProperty::SetFadeSourceRecurse);
			std::invoke(FUNC, a_object, a_fadeAlpha);
		}

		// members
		NiPointer<NiTexture> alphaTexture;									 // 0x70
		NiPointer<NiTexture> colorTexture;									 // 0x78
		NiPointer<NiTexture> lensFlareTexture;								 // 0x80
		REX::Enum<BSGraphics::TextureAddressMode, std::int32_t> addressMode; // 0x88
		REX::Float32* fadeAlpha;											 // 0x90
	};

	static_assert(sizeof(BSBloodSplatterShaderProperty) == 0x98);
}
