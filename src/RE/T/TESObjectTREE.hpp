#pragma once

#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/O/OBJ_TREE.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESProduceForm.hpp"

namespace RE
{
	class BaseTreeData;

	class __declspec(novtable) TESObjectTREE :
		public TESBoundObject,		 // 0x000
		public BGSModelMaterialSwap, // 0x068
		public TESFullName,			 // 0x0A8
		public TESProduceForm		 // 0x0B8
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObjectTREE;
		inline static constexpr const auto& VTABLE = VTABLE::TESObjectTREE;
		inline static constexpr auto FORM_TYPE = FormType::Tree;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class etTreeType : std::int32_t
		{
			ShortAndThin = 0,
			ShortAndThick = 1,
			TallAndThin = 2,
			TallAndThick = 3,

			_Count = 4
		};

		// members
		OBJ_TREE data;							  // 0x0D8
		BaseTreeData* baseData;					  // 0x108
		REX::Enum<etTreeType, std::int32_t> type; // 0x110
	};

	static_assert(sizeof(TESObjectTREE) == 0x118);
}
