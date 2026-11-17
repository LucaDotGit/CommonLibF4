#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESFurniture.hpp"

namespace RE
{
	enum class LOCK_LEVEL : std::int32_t;

	class TESTexture;

	class __declspec(novtable) BGSTerminal : public TESFurniture // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSTerminal;
		inline static constexpr const auto& VTABLE = VTABLE::BGSTerminal;
		inline static constexpr auto FORM_TYPE = FormType::Terminal;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				HasDistantLOD = 1 << 15,
				RandomAnimStart = 1 << 16
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class BodyTextItem
		{
		public:
			// members
			BGSLocalizedString itemText; // 0x00
			TESCondition conditions;	 // 0x08
		};

		static_assert(sizeof(BodyTextItem) == 0x10);

		class MenuItem
		{
		public:
			enum class Type : std::int8_t
			{
				SubMenu_Terminal = 4,
				SubMenu_ReturnToTopLevel = 5,
				SubMenu_ForceRedraw = 6,
				DisplayText = 8,
				DisplayImage = 16
			};

			// members
			BGSLocalizedString itemText;	 // 0x00
			BGSLocalizedString responseText; // 0x08

			union
			{
			public:
				BGSTerminal* subMenu;
				BGSLocalizedString* displayText;
				TESTexture* displayImage;
				BGSNote* holotape;
			} selectionResult; // 0x10

			TESCondition conditions;		   // 0x18
			std::uint16_t id;				   // 0x20
			REX::Enum<Type, std::int8_t> type; // 0x22
		};

		static_assert(sizeof(MenuItem) == 0x28);

		~BGSTerminal() override; // 0x00

		[[nodiscard]]
		auto GetHackDifficultyLockLevel(TESObjectREFR* a_ref) const -> LOCK_LEVEL
		{
			using FuncType = decltype(&BGSTerminal::GetHackDifficultyLockLevel);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSTerminal::GetHackDifficultyLockLevel);
			return std::invoke(FUNC, this, a_ref);
		}

		[[nodiscard]]
		static auto IsTerminalRefInUse(TESObjectREFR* a_ref) -> bool
		{
			using FuncType = decltype(&BGSTerminal::IsTerminalRefInUse);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSTerminal::IsTerminalRefInUse);
			return std::invoke(FUNC, a_ref);
		}

		static void Show(TESObjectREFR* a_ref)
		{
			using FuncType = decltype(&BGSTerminal::Show);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSTerminal::Show);
			std::invoke(FUNC, a_ref);
		}

		// members
		BSTArray<BodyTextItem> bodyTextItems;  // 0x1A0
		BSTArray<MenuItem> menuItems;		   // 0x1B8
		BGSLocalizedString headerTextOverride; // 0x1D0
		BGSLocalizedString welcomeText;		   // 0x1D8
	};

	static_assert(sizeof(BGSTerminal) == 0x1E0);
}
