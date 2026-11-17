#pragma once

#include "RE/B/BGSIdleCollection.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSIdleMarker :
		public TESBoundObject,	 // 0x00
		public BGSKeywordForm,	 // 0x68
		public TESModel,		 // 0x88
		public BGSIdleCollection // 0xB8
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSIdleMarker;
		inline static constexpr const auto& VTABLE = VTABLE::BGSIdleMarker;
		inline static constexpr auto FORM_TYPE = FormType::IdleMarker;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				ChildCanUse = 1 << 29
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		~BGSIdleMarker() override; // 0x00

		// members
		BGSKeyword* animArchType; // 0xD8
		BGSKeyword* flavorAnim;	  // 0xE0
	};

	static_assert(sizeof(BGSIdleMarker) == 0xE8);
}
