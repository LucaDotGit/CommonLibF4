#pragma once

#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSInstanceNamingRules : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSInstanceNamingRules;
		inline static constexpr const auto& VTABLE = VTABLE::BGSInstanceNamingRules;
		inline static constexpr auto FORM_TYPE = FormType::InstanceNamingRules;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				MergeTarget = static_cast<std::uint32_t>(1) << 31
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class RuleData
		{
		public:
			enum class OperatorType : std::int8_t
			{
				GreaterThanEqual = 0,
				GreaterThan = 1,
				LessThanEqual = 2,
				LessThan = 3,
				Equal = 4
			};

			// members
			BGSLocalizedString text;						   // 0x00
			BGSKeywordForm keywords;						   // 0x08
			REX::Float32 compareVal;						   // 0x28
			std::uint8_t propertyBridgeArrayIndex;			   // 0x2C
			REX::Enum<OperatorType, std::int8_t> operatorType; // 0x2D
			std::uint16_t index;							   // 0x2E
			bool revert;									   // 0x30
		};

		static_assert(sizeof(RuleData) == 0x38);

		class RuleSet : public BSTArray<RuleData> // 0x00
		{
		public:
		};

		static_assert(sizeof(RuleSet) == 0x18);

		// members
		REX::Enum<FormType, std::uint8_t> type;				  // 0x020
		std::array<RuleSet, 10> ruleSets;					  // 0x028
		BSTArray<const BGSInstanceNamingRules*> mergeSources; // 0x118
	};

	static_assert(sizeof(BGSInstanceNamingRules) == 0x130);
}
