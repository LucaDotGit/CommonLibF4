#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSShaderProperty.hpp"
#include "RE/NetImmerse/NiObject.hpp"
#include "RE/NetImmerse/NiSmartPointer.hpp"

namespace RE
{
	class NiTexture;

	class __declspec(novtable) BSTextureSet
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSTextureSet };
		inline static constexpr auto VTABLE{ VTABLE::BSTextureSet };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::BSTextureSet };

		// add
		virtual const BSFixedString* GetTextureFilenameFS(BSShaderProperty::TextureTypeEnum a_type) = 0;												 // 28
		virtual const char* GetTextureFilename(BSShaderProperty::TextureTypeEnum a_type) = 0;															 // 29
		virtual void GetTexture(const void* a_prefetchedHandle, BSShaderProperty::TextureTypeEnum a_type, NiPointer<NiTexture>* a_texture, bool a_srgb); // 2A
		virtual void GetTexture(BSShaderProperty::TextureTypeEnum a_type, NiPointer<NiTexture>* a_texture, bool a_srgb) = 0;							 // 2B
		virtual void SetTextureFilename(BSShaderProperty::TextureTypeEnum a_type, const char* a_filename) = 0;											 // 2C
	};
	static_assert(sizeof(BSTextureSet) == 0x10);

	class __declspec(novtable) BSShaderTextureSet
		: public BSTextureSet // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSShaderTextureSet };
		inline static constexpr auto VTABLE{ VTABLE::BSShaderTextureSet };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::BSShaderTextureSet };

		static BSShaderTextureSet* CreateObject()
		{
			using func_t = decltype(&BSShaderTextureSet::CreateObject);
			static REL::Relocation<func_t> func{ REL::RelocationID(0, 2316324) };
			return func();
		}

		// members
		BSFixedString textureNames[10]; // 10
	};
	static_assert(sizeof(BSShaderTextureSet) == 0x60);
}
