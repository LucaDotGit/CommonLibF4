#pragma once

#include "RE/B/BGSPreloadable.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSImpactDataSet :
		public TESForm,		  // 0x00
		public BGSPreloadable // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSImpactDataSet;
		inline static constexpr const auto& VTABLE = VTABLE::BGSImpactDataSet;
		inline static constexpr auto FORM_TYPE = FormType::ImpactDataSet;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BSTHashMap<const BGSMaterialType*, BGSImpactData*> impactMap; // 0x28
	};

	static_assert(sizeof(BGSImpactDataSet) == 0x58);
}
