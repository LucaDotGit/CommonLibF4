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
	class __declspec(novtable) NiTexture
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiTexture };
		inline static constexpr auto VTABLE{ VTABLE::NiTexture };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiTexture };

		enum class Flags : std::uint32_t; // TODO

		// add
		virtual BSTextureArray::Texture* IsBSTextureArray(); // 28 - { return nullptr; }

		static void SetAllowDegrade(bool a_set)
		{
			using FuncType = decltype(&NiTexture::SetAllowDegrade);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::NiTexture::SetAllowDegrade };
			std::invoke(FUNC, a_set);
		}

		// members
		BSFixedString name;							// 10
		REX::EnumSet<Flags, std::uint32_t> flags;	// 18
		NiTexture* prev;							// 29
		NiTexture* next;							// 28
		BSTSmartPointer<BSResource::Stream> stream; // 30
		BSGraphics::Texture* rendererTexture;		// 38
		std::uint8_t desiredDegradeLevel;			// 40
		std::uint8_t savedDegradeLevel;				// 41
		bool isDDX	: 1;							// 42:0
		bool isSRGB : 1;							// 42:1
	};
	static_assert(sizeof(NiTexture) == 0x48);
}
