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

	class __declspec(novtable) BGSMessage
		: public TESForm,		// 00
		  public TESFullName,	// 20
		  public TESDescription // 30
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMessage };
		inline static constexpr auto VTABLE{ VTABLE::BGSMessage };
		inline static constexpr auto FORM_TYPE{ FormType::kMessage };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kMessageBox = 1 << 0,
			kInitialDelay = 1 << 1
		};

		std::uint32_t GetConvertedDescription(BSFixedString& a_outDescription) const
		{
			using FuncType = decltype(&BGSMessage::GetConvertedDescription);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSMessage::GetConvertedDescription };
			return std::invoke(FUNC, this, a_outDescription);
		}

		void SetButtons(std::span<std::unique_ptr<MESSAGEBOX_BUTTON>> a_buttons);
		void ClearButtons();

		// members
		BGSMenuIcon* icon;							 // 48
		TESQuest* ownerQuest;						 // 50
		BSSimpleList<MESSAGEBOX_BUTTON*> buttonList; // 58
		BSFixedStringCS swfFile;					 // 68
		BGSLocalizedString shortName;				 // 70
		REX::EnumSet<Flags, std::uint32_t> flags;	 // 78
		std::uint32_t displayTime;					 // 7C
	};
	static_assert(sizeof(BGSMessage) == 0x80);
}
