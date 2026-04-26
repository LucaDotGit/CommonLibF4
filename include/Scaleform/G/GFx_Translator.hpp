#pragma once

#include "Scaleform/G/GFx_State.hpp"

namespace Scaleform::GFx
{
	class __declspec(novtable) Translator
		: public State // 00
	{
	public:
		inline static constexpr auto RTTI{ ::RE::RTTI::Scaleform__GFx__Translator };
		inline static constexpr auto VTABLE{ ::RE::VTABLE::Scaleform__GFx__Translator };
		inline static constexpr auto STATE_TYPE{ StateType::kTranslator };

		enum class WordWrappingType : std::uint32_t
		{
			kDefault = 0,
			kAsian = 1 << 0,
			kProhibition = 1 << 1,
			kNoHangulWrap = 1 << 2,
			kHyphenation = 1 << 3,
			kCustom = 1 << 7
		};

		Translator()
			: State(STATE_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		explicit Translator(WordWrappingType a_wordWrappingMode)
			: State(STATE_TYPE),
			  wordWrappingMode(a_wordWrappingMode)
		{
			REL::EmplaceVtable(this);
		}

		~Translator() override; // 01

		// members
		REX::EnumSet<WordWrappingType, std::uint32_t> wordWrappingMode; // 18
	};
	static_assert(sizeof(Translator) == 0x20);
}
