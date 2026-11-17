#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSResource_Stream.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiObject.hpp"

namespace RE::BSGraphics
{
	class Texture;
}

namespace RE::BSTextureArray
{
	class Texture;
}

namespace RE
{
	class __declspec(novtable) NiTexture : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiTexture;
		inline static constexpr const auto& VTABLE = VTABLE::NiTexture;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiTexture;

		enum class Flags : std::uint32_t; // To-Do

		// add
		virtual auto IsBSTextureArray() -> BSTextureArray::Texture*; // 0x28 - { return nullptr; }

		static void SetAllowDegrade(bool a_set)
		{
			using FuncType = decltype(&NiTexture::SetAllowDegrade);
			static const auto FUNC = REL::Relocation<FuncType>(ID::NiTexture::SetAllowDegrade);
			std::invoke(FUNC, a_set);
		}

		// members
		BSFixedString name;							// 0x10
		REX::EnumSet<Flags, std::uint32_t> flags;	// 0x18
		NiTexture* prev;							// 0x29
		NiTexture* next;							// 0x28
		BSTSmartPointer<BSResource::Stream> stream; // 0x30
		BSGraphics::Texture* rendererTexture;		// 0x38
		std::uint8_t desiredDegradeLevel;			// 0x40
		std::uint8_t savedDegradeLevel;				// 0x41
		bool isDDX	: 1;							// 0x42:0
		bool isSRGB : 1;							// 0x42:1
	};

	static_assert(sizeof(NiTexture) == 0x48);
}
