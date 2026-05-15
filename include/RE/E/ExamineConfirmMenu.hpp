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

	class __declspec(novtable) ExamineConfirmMenu
		: public GameMenuBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExamineConfirmMenu };
		inline static constexpr auto VTABLE{ VTABLE::ExamineConfirmMenu };
		inline static constexpr auto MENU_NAME{ "ExamineConfirmMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kExamineConfirmMenu };

		enum class CONFIRM_TYPE : std::int32_t
		{
			kSimple = 0,
			kBuild = 1,
			kScrap = 2,
			kRepairFailure = 3
		};

		class __declspec(novtable) ICallback
		{
		public:
			inline static constexpr auto RTTI{ RTTI::ExamineConfirmMenu__ICallback };
			inline static constexpr auto VTABLE{ VTABLE::ExamineConfirmMenu__ICallback };

			explicit ICallback(ExamineMenu* a_thisMenu)
				: thisMenu(a_thisMenu)
			{
				REL::EmplaceVtable(this);
			}

			virtual ~ICallback(); // 00

			// add
			virtual void OnAccept(); // 01

			GAME_HEAP_REDEFINE_NEW(ICallback);

			// members
			ExamineMenu* thisMenu; // 08
		};
		static_assert(sizeof(ICallback) == 0x10);

		class __declspec(novtable) InitData
		{
		public:
			inline static constexpr auto RTTI{ RTTI::ExamineConfirmMenu__InitData };
			inline static constexpr auto VTABLE{ VTABLE::ExamineConfirmMenu__InitData };

			InitData(BSFixedString a_confirmQuestion, BSFixedStringCS a_buttonLabel, CONFIRM_TYPE a_confirmType)
				: confirmQuestion(std::move(a_confirmQuestion)),
				  buttonLabel(std::move(a_buttonLabel)),
				  confirmType(a_confirmType)
			{
				REL::EmplaceVtable(this);
			}

			virtual ~InitData(); // 00

			GAME_HEAP_REDEFINE_NEW(InitData);

			// members
			BSFixedString confirmQuestion;												// 08
			BSFixedStringCS buttonLabel;												// 10
			REX::Enum<CONFIRM_TYPE, std::int32_t> confirmType{ CONFIRM_TYPE::kSimple }; // 18
			bool hasCancelButton{ true };												// 1C
		};
		static_assert(sizeof(InitData) == 0x20);

		class __declspec(novtable) InitDataScrap
			: public InitData // 00
		{
		public:
			inline static constexpr auto RTTI{ RTTI::ExamineConfirmMenu__InitDataScrap };
			inline static constexpr auto VTABLE{ VTABLE::ExamineConfirmMenu__InitDataScrap };

			InitDataScrap(const char* a_confirmQuestion, const char* a_buttonLabel, const char* a_scrapSourceName, BSTArray<BSTPair<TESBoundObject*, std::uint32_t>> a_scrapResults)
				: InitData(a_confirmQuestion, a_buttonLabel, CONFIRM_TYPE::kScrap),
				  scrapSourceName(a_scrapSourceName),
				  scrapResults(std::move(a_scrapResults))
			{
				REL::EmplaceVtable(this);
			}

			~InitDataScrap() override; // 00

			// members
			BSFixedStringCS scrapSourceName;								// 20
			BSTArray<BSTPair<TESBoundObject*, std::uint32_t>> scrapResults; // 28
		};
		static_assert(sizeof(InitDataScrap) == 0x40);

		class __declspec(novtable) InitDataRepairFailure
			: public InitData // 00
		{
		public:
			inline static constexpr auto RTTI{ RTTI::ExamineConfirmMenu__InitDataRepairFailure };
			inline static constexpr auto VTABLE{ VTABLE::ExamineConfirmMenu__InitDataRepairFailure };

			explicit InitDataRepairFailure(BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* a_requiredItems)
				: InitData(GetGameSetting("sCannotRepairMessage"sv)->GetString(), "$OK", CONFIRM_TYPE::kRepairFailure),
				  requiredItems(a_requiredItems)
			{
				hasCancelButton = false;
				REL::EmplaceVtable(this);
			}

			~InitDataRepairFailure() override; // 00

			// members
			BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* requiredItems; // 20
			BSTHashMap<TESBoundObject*, std::uint32_t> availableComponents;				  // 28
		};
		static_assert(sizeof(InitDataRepairFailure) == 0x58);

		~ExamineConfirmMenu() override; // 00

		// members
		::Scaleform::GFx::Value confirmObj; // E0
	};
	static_assert(sizeof(ExamineConfirmMenu) == 0x100);
}
