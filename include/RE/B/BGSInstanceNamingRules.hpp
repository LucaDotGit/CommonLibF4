#pragma once

#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSInstanceNamingRules
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSInstanceNamingRules };
		inline static constexpr auto VTABLE{ VTABLE::BGSInstanceNamingRules };
		inline static constexpr auto FORM_TYPE{ FormType::kInstanceNamingRules };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kMergeTarget = 1ui32 << 31
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class RuleData
		{
		public:
			enum class OperatorType : std::int8_t
			{
				kGreaterThanEqual = 0,
				kGreaterThan = 1,
				kLessThanEqual = 2,
				kLessThan = 3,
				kEqual = 4
			};

			// members
			BGSLocalizedString text;						   // 00
			BGSKeywordForm keywords;						   // 08
			REX::Float32 compareVal;						   // 28
			std::uint8_t propertyBridgeArrayIndex;			   // 2C
			REX::Enum<OperatorType, std::int8_t> operatorType; // 2D
			std::uint16_t index;							   // 2E
			bool revert;									   // 30
		};
		static_assert(sizeof(RuleData) == 0x38);

		class RuleSet
			: public BSTArray<RuleData> // 00
		{
		public:
		};
		static_assert(sizeof(RuleSet) == 0x18);

		// members
		REX::Enum<FormType, std::uint8_t> type;				  // 020
		std::array<RuleSet, 10> ruleSets;					  // 028
		BSTArray<const BGSInstanceNamingRules*> mergeSources; // 118
	};
	static_assert(sizeof(BGSInstanceNamingRules) == 0x130);
}
