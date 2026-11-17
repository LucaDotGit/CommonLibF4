#pragma once

#include "Scaleform/G/GFx_State.hpp"

namespace Scaleform
{
	class WStringBuffer;
}

namespace Scaleform::GFx
{
	class __declspec(novtable) Translator : public State // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RE::RTTI::Scaleform__GFx__Translator;
		inline static constexpr const auto& VTABLE = RE::VTABLE::Scaleform__GFx__Translator;
		inline static constexpr auto STATE_TYPE = StateType::Translator;

		class LineFormatDesc
		{
		public:
			// members
			const wchar_t* paraText;			  // 0x00
			std::size_t paraTextLen;			  // 0x08
			const REX::Float32* widths;			  // 0x10
			std::size_t lineStartPos;			  // 0x18
			std::size_t numCharsInLine;			  // 0x20
			REX::Float32 visibleRectWidth;		  // 0x28
			REX::Float32 currentLineWidth;		  // 0x2C
			REX::Float32 lineWidthBeforeWordWrap; // 0x30
			REX::Float32 dashSymbolWidth;		  // 0x34
			std::uint8_t alignment;				  // 0x38
			std::size_t proposedWordWrapPoint;	  // 0x40
			bool useHyphenation;				  // 0x48
		};

		static_assert(sizeof(LineFormatDesc) == 0x50);

		class TranslateInfo
		{
		public:
			// members
			const wchar_t* key;				  // 0x00
			Scaleform::WStringBuffer* result; // 0x08
			const char* instanceName;		  // 0x10
			std::uint8_t flags;				  // 0x18
		};

		static_assert(sizeof(TranslateInfo) == 0x20);

		enum class WordWrappingType : std::uint32_t
		{
			Default = 0,
			Asian = 1 << 0,
			Prohibition = 1 << 1,
			NoHangulWrap = 1 << 2,
			Hyphenation = 1 << 3,
			Custom = 1 << 7
		};

		Translator() :
			State(STATE_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		explicit Translator(WordWrappingType a_wordWrappingMode) :
			State(STATE_TYPE),
			wordWrappingMode(a_wordWrappingMode)
		{
			REL::EmplaceVtable(this);
		}

		~Translator() override; // 0x00

		// add
		virtual auto GetCaps() const -> std::uint32_t;							   // 0x01
		virtual void Translate(Scaleform::GFx::Translator::TranslateInfo* a_info); // 0x02
		virtual auto OnWordWrapping(LineFormatDesc* a_formatDesc) -> bool;		   // 0x03
		virtual auto OnBidirectionalText(
			const wchar_t* a_text,
			std::size_t a_textLength,
			wchar_t* a_output,
			std::uint32_t& a_outputLength,
			bool& a_isRTL) -> bool; // 0x04

		// members
		REX::EnumSet<WordWrappingType, std::uint32_t> wordWrappingMode; // 0x18
	};

	static_assert(sizeof(Translator) == 0x20);
}
