#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSShaderProperty.hpp"
#include "RE/N/NiObject.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiTexture;

	class __declspec(novtable) BSTextureSet : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSTextureSet;
		inline static constexpr const auto& VTABLE = VTABLE::BSTextureSet;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSTextureSet;

		~BSTextureSet() override; // 0x00

		// add
		virtual auto GetTextureFilenameFS(BSShaderProperty::TextureType a_type) -> const BSFixedString* = 0; // 0x28
		virtual auto GetTextureFilename(BSShaderProperty::TextureType a_type) -> const char* = 0;			 // 0x29
		virtual void GetTexture(
			const void* a_prefetchedHandle,
			BSShaderProperty::TextureType a_type,
			NiPointer<NiTexture>* a_texture,
			bool a_srgb); // 0x2A
		virtual void GetTexture(
			BSShaderProperty::TextureType a_type,
			NiPointer<NiTexture>* a_texture,
			bool a_srgb) = 0;																			   // 0x2B
		virtual void SetTextureFilename(BSShaderProperty::TextureType a_type, const char* a_filename) = 0; // 0x2C
	};

	static_assert(sizeof(BSTextureSet) == 0x10);
}
