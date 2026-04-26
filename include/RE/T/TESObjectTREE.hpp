#pragma once

#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/O/OBJ_TREE.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESProduceForm.hpp"

namespace RE
{
	class BaseTreeData;

	class __declspec(novtable) TESObjectTREE
		: public TESBoundObject,	   // 000
		  public BGSModelMaterialSwap, // 068
		  public TESFullName,		   // 0A8
		  public TESProduceForm		   // 0B8
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectTREE };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectTREE };
		inline static constexpr auto FORM_TYPE{ FormType::kTree };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class etTreeType : std::int32_t
		{
			kShortAndThin = 0,
			kShortAndThick = 1,
			kTallAndThin = 2,
			kTallAndThick = 3,

			kTotal = 4
		};

		// members
		OBJ_TREE data;							  // 0D8
		BaseTreeData* baseData;					  // 108
		REX::Enum<etTreeType, std::int32_t> type; // 110
	};
	static_assert(sizeof(TESObjectTREE) == 0x118);
}
