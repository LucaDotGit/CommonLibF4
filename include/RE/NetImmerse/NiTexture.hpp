#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"
#include "RE/NetImmerse/NiObject.hpp"

namespace RE
{
	namespace BSResource
	{
		class Stream;
	}

	namespace BSGraphics
	{
		class Texture;
	}

	struct BSTextureArray
	{
		class Texture;
	};
	static_assert(std::is_empty_v<BSTextureArray>);

	class __declspec(novtable) NiTexture
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiTexture };
		inline static constexpr auto VTABLE{ VTABLE::NiTexture };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::NiTexture };

		// add
		virtual BSTextureArray::Texture* IsBSTextureArray() { return nullptr; } // 28

		static void SetAllowDegrade(bool a_allow)
		{
			using func_t = decltype(&NiTexture::SetAllowDegrade);
			static REL::Relocation<func_t> func{ REL::ID(948181) };
			return func(a_allow);
		}

		[[nodiscard]] std::string_view GetName() const { return name; }

		// members
		BSFixedString name;							// 10
		std::uint32_t flags;						// 18
		NiTexture* prev;							// 29
		NiTexture* next;							// 28
		BSTSmartPointer<BSResource::Stream> stream; // 30
		BSGraphics::Texture* rendererTexture;		// 38
		std::int8_t desiredDegradeLevel;			// 40
		std::int8_t savedDegradeLevel;				// 41
		bool isDDX : 1;								// 42:0
		bool isSRGB : 1;							// 42:1
	};
	static_assert(sizeof(NiTexture) == 0x48);
}
