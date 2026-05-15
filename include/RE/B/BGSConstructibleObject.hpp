#pragma once

#include "RE/B/BGSPickupPutdownSounds.hpp"
#include "RE/B/BGSTypedFormValuePair.hpp"
#include "RE/B/BGSTypedKeywordValue.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSConstructibleObject
		: public TESForm,				 // 00
		  public BGSPickupPutdownSounds, // 20
		  public TESDescription			 // 38
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSConstructibleObject };
		inline static constexpr auto VTABLE{ VTABLE::BGSConstructibleObject };
		inline static constexpr auto FORM_TYPE{ FormType::kConstructibleObject };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class ConstructibleObjectData
		{
		public:
			// members
			std::uint16_t numConstructed;	// 00
			std::uint16_t workshopPriority; // 02
		};
		static_assert(sizeof(ConstructibleObjectData) == 0x04);

		inline static constexpr auto ObjectKeywordType = KeywordType::kRecipeFilter;

		[[nodiscard]] std::vector<BGSKeyword*> GetRecipeKeywords() const;
		void SetRecipeKeywords(std::span<BGSKeyword*> a_keywords);

		[[nodiscard]] auto GetComponents() const noexcept
			-> std::optional<std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>>;
		void SetComponents(std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>> a_components);

		// members
		BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* requiredItems; // 50
		TESCondition conditions;													  // 58
		TESForm* createdItem;														  // 60
		BGSKeyword* benchKeyword;													  // 68
		ConstructibleObjectData data;												  // 70
		BGSTypedKeywordValueArray<KeywordType::kRecipeFilter> filterKeywords;		  // 78
	};
	static_assert(sizeof(BGSConstructibleObject) == 0x88);
}
