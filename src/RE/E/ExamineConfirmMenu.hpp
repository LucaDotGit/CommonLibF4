#pragma once

#include "RE/B/BGSTypedFormValuePair.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/S/Setting.hpp"
#include "RE/S/SettingUtil.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class ExamineMenu;

	class __declspec(novtable) ExamineConfirmMenu : public GameMenuBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExamineConfirmMenu;
		inline static constexpr const auto& VTABLE = VTABLE::ExamineConfirmMenu;
		inline static constexpr auto MENU_NAME = "ExamineConfirmMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::ExamineConfirmMenu;

		enum class CONFIRM_TYPE : std::int32_t
		{
			Simple = 0,
			Build = 1,
			Scrap = 2,
			RepairFailure = 3
		};

		class __declspec(novtable) ICallback
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::ExamineConfirmMenu__ICallback;
			inline static constexpr const auto& VTABLE = VTABLE::ExamineConfirmMenu__ICallback;

			explicit ICallback(ExamineMenu* a_thisMenu) :
				thisMenu(a_thisMenu)
			{
				REL::EmplaceVtable(this);
			}

			virtual ~ICallback(); // 0x00

			// add
			virtual void OnAccept(); // 0x01

			GAME_HEAP_REDEFINE_NEW(ICallback);

			// members
			ExamineMenu* thisMenu; // 0x08
		};

		static_assert(sizeof(ICallback) == 0x10);

		class __declspec(novtable) InitData
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::ExamineConfirmMenu__InitData;
			inline static constexpr const auto& VTABLE = VTABLE::ExamineConfirmMenu__InitData;

			InitData(
				const BSFixedStringCS& a_confirmQuestion,
				BSFixedStringCS a_buttonLabel,
				CONFIRM_TYPE a_confirmType = CONFIRM_TYPE::Simple,
				bool a_hasCancelButton = true) :
				confirmQuestion(a_confirmQuestion),
				buttonLabel(std::move(a_buttonLabel)),
				confirmType(a_confirmType),
				hasCancelButton(a_hasCancelButton)
			{
				REL::EmplaceVtable(this);
			}

			virtual ~InitData(); // 0x00

			GAME_HEAP_REDEFINE_NEW(InitData);

			// members
			BSFixedString confirmQuestion;					   // 0x08 - this is not `BSFixedStringCS`, for some reason
			BSFixedStringCS buttonLabel;					   // 0x10
			REX::Enum<CONFIRM_TYPE, std::int32_t> confirmType; // 0x18
			bool hasCancelButton;							   // 0x1C
		};

		static_assert(sizeof(InitData) == 0x20);

		class __declspec(novtable) InitDataScrap : public InitData // 0x00
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::ExamineConfirmMenu__InitDataScrap;
			inline static constexpr const auto& VTABLE = VTABLE::ExamineConfirmMenu__InitDataScrap;

			InitDataScrap(
				const BSFixedStringCS& a_confirmQuestion,
				BSFixedStringCS a_buttonLabel,
				BSFixedStringCS a_scrapSourceName,
				BSTArray<BSTPair<TESBoundObject*, std::uint32_t>> a_scrapResults) :
				InitData(a_confirmQuestion, std::move(a_buttonLabel), CONFIRM_TYPE::Scrap),
				scrapSourceName(std::move(a_scrapSourceName)),
				scrapResults(std::move(a_scrapResults))
			{
				REL::EmplaceVtable(this);
			}

			~InitDataScrap() override; // 0x00

			// members
			BSFixedStringCS scrapSourceName;								// 0x20
			BSTArray<BSTPair<TESBoundObject*, std::uint32_t>> scrapResults; // 0x28
		};

		static_assert(sizeof(InitDataScrap) == 0x40);

		class __declspec(novtable) InitDataRepairFailure : public InitData // 0x00
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::ExamineConfirmMenu__InitDataRepairFailure;
			inline static constexpr const auto& VTABLE = VTABLE::ExamineConfirmMenu__InitDataRepairFailure;

			explicit InitDataRepairFailure(
				BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* a_requiredItems) :
				InitData(
					ExamineConfirmMenu::GetCannotRepairMessage(),
					GetDefaultButtonLabel(),
					CONFIRM_TYPE::RepairFailure,
					false),
				requiredItems(a_requiredItems)
			{
				REL::EmplaceVtable(this);
			}

			~InitDataRepairFailure() override; // 0x00

			[[nodiscard]]
			static auto GetDefaultButtonLabel() -> BSFixedStringCS;

			// members
			BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* requiredItems; // 0x20
			BSTHashMap<TESBoundObject*, std::uint32_t> availableComponents;				  // 0x28
		};

		static_assert(sizeof(InitDataRepairFailure) == 0x58);

		~ExamineConfirmMenu() override; // 0x00

		static auto GetCannotRepairMessageSetting() -> Setting&;
		static auto GetCannotRepairMessage() -> BSFixedStringCS;

		// members
		Scaleform::GFx::Value confirmObj; // 0xE0
	};

	static_assert(sizeof(ExamineConfirmMenu) == 0x100);
}
