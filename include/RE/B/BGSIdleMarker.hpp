#pragma once

#include "RE/B/BGSIdleCollection.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSIdleMarker
		: public TESBoundObject,   // 00
		  public BGSKeywordForm,   // 68
		  public TESModel,		   // 88
		  public BGSIdleCollection // B8
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSIdleMarker };
		inline static constexpr auto VTABLE{ VTABLE::BGSIdleMarker };
		inline static constexpr auto FORM_TYPE{ FormType::kIdleMarker };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kChildCanUse = 1 << 29
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BGSKeyword* animArchType; // D8
		BGSKeyword* flavorAnim;	  // E0
	};
	static_assert(sizeof(BGSIdleMarker) == 0xE8);
}
