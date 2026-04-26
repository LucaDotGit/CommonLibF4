#pragma once

#include "RE/B/BGSPreloadable.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSImpactDataSet
		: public TESForm,		// 00
		  public BGSPreloadable // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSImpactDataSet };
		inline static constexpr auto VTABLE{ VTABLE::BGSImpactDataSet };
		inline static constexpr auto FORM_TYPE{ FormType::kImpactDataSet };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BSTHashMap<const BGSMaterialType*, BGSImpactData*> impactMap; // 28
	};
	static_assert(sizeof(BGSImpactDataSet) == 0x58);
}
