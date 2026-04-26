#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESFurniture.hpp"

namespace RE
{
	enum class LOCK_LEVEL : std::int32_t;

	class TESTexture;

	class __declspec(novtable) BGSTerminal
		: public TESFurniture // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSTerminal };
		inline static constexpr auto VTABLE{ VTABLE::BGSTerminal };
		inline static constexpr auto FORM_TYPE{ FormType::kTerminal };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kHasDistantLOD = 1 << 15,
				kRandomAnimStart = 1 << 16
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class BodyTextItem
		{
		public:
			// members
			BGSLocalizedString itemText; // 00
			TESCondition conditions;	 // 08
		};
		static_assert(sizeof(BodyTextItem) == 0x10);

		class MenuItem
		{
		public:
			enum class Type : std::int8_t
			{
				kSubMenu_Terminal = 4,
				kSubMenu_ReturnToTopLevel = 5,
				kSubMenu_ForceRedraw = 6,
				kDisplayText = 8,
				kDisplayImage = 16
			};

			// members
			BGSLocalizedString itemText;	 // 00
			BGSLocalizedString responseText; // 08
			union
			{
				BGSTerminal* subMenu;
				BGSLocalizedString* displayText;
				TESTexture* displayImage;
				BGSNote* holotape;
			} selectionResult;				   // 10
			TESCondition conditions;		   // 18
			std::uint16_t id;				   // 20
			REX::Enum<Type, std::int8_t> type; // 22
		};
		static_assert(sizeof(MenuItem) == 0x28);

		[[nodiscard]] LOCK_LEVEL GetHackDifficultyLockLevel(TESObjectREFR* a_ref) const
		{
			using FuncType = decltype(&BGSTerminal::GetHackDifficultyLockLevel);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSTerminal::GetHackDifficultyLockLevel };
			return std::invoke(FUNC, this, a_ref);
		}

		[[nodiscard]] static bool IsTerminalRefInUse(TESObjectREFR* a_ref)
		{
			using FuncType = decltype(&BGSTerminal::IsTerminalRefInUse);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSTerminal::IsTerminalRefInUse };
			return std::invoke(FUNC, a_ref);
		}

		static void Show(TESObjectREFR* a_ref)
		{
			using FuncType = decltype(&BGSTerminal::Show);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSTerminal::Show };
			FUNC(a_ref);
		}

		// members
		BSTArray<BodyTextItem> bodyTextItems;  // 1A0
		BSTArray<MenuItem> menuItems;		   // 1B8
		BGSLocalizedString headerTextOverride; // 1D0
		BGSLocalizedString welcomeText;		   // 1D8
	};
	static_assert(sizeof(BGSTerminal) == 0x1E0);
}
