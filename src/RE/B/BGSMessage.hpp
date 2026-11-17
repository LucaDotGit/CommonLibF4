#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE
{
	class MESSAGEBOX_BUTTON;

	class __declspec(novtable) BGSMessage :
		public TESForm,		  // 0x00
		public TESFullName,	  // 0x20
		public TESDescription // 0x30
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSMessage;
		inline static constexpr const auto& VTABLE = VTABLE::BGSMessage;
		inline static constexpr auto FORM_TYPE = FormType::Message;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			None = 0,
			MessageBox = 1 << 0,
			InitialDelay = 1 << 1
		};

		auto GetConvertedDescription(BSFixedString& a_outDescription) const -> std::uint32_t
		{
			using FuncType = decltype(&BGSMessage::GetConvertedDescription);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSMessage::GetConvertedDescription);
			return std::invoke(FUNC, this, a_outDescription);
		}

		void SetButtons(std::span<std::unique_ptr<MESSAGEBOX_BUTTON>> a_buttons);
		void ClearButtons();

		// members
		BGSMenuIcon* icon;							 // 0x48
		TESQuest* ownerQuest;						 // 0x50
		BSSimpleList<MESSAGEBOX_BUTTON*> buttonList; // 0x58
		BSFixedStringCS swfFile;					 // 0x68
		BGSLocalizedString shortName;				 // 0x70
		REX::EnumSet<Flags, std::uint32_t> flags;	 // 0x78
		std::uint32_t displayTime;					 // 0x7C
	};

	static_assert(sizeof(BGSMessage) == 0x80);
}
