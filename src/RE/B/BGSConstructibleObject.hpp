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
	class __declspec(novtable) BGSConstructibleObject :
		public TESForm,				   // 0x00
		public BGSPickupPutdownSounds, // 0x20
		public TESDescription		   // 0x38
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSConstructibleObject;
		inline static constexpr const auto& VTABLE = VTABLE::BGSConstructibleObject;
		inline static constexpr auto FORM_TYPE = FormType::ConstructibleObject;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class ConstructibleObjectData
		{
		public:
			// members
			std::uint16_t numConstructed;	// 0x00
			std::uint16_t workshopPriority; // 0x02
		};

		static_assert(sizeof(ConstructibleObjectData) == 0x04);

		inline static constexpr auto ObjectKeywordType = KeywordType::RecipeFilter;

		[[nodiscard]]
		auto GetRecipeKeywords() const -> BSTArray<BGSKeyword*>;
		void SetRecipeKeywords(std::span<BGSKeyword*> a_keywords);

		[[nodiscard]]
		auto GetComponents() const noexcept
			-> std::optional<std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>>;
		void SetComponents(std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>> a_components);

		// members
		BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* requiredItems; // 0x50
		TESCondition conditions;													  // 0x58
		TESForm* createdItem;														  // 0x60
		BGSKeyword* benchKeyword;													  // 0x68
		ConstructibleObjectData data;												  // 0x70
		BGSTypedKeywordValueArray<KeywordType::RecipeFilter> filterKeywords;		  // 0x78
	};

	static_assert(sizeof(BGSConstructibleObject) == 0x88);
}
