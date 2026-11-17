#pragma once

#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/T/TESBoundAnimObject.hpp"
#include "RE/T/TESLeveledList.hpp"

namespace RE
{
	class __declspec(novtable) TESLevCharacter :
		public TESBoundAnimObject,	// 0x00
		public TESLeveledList,		// 0x68
		public BGSModelMaterialSwap // 0x98
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESLevCharacter;
		inline static constexpr const auto& VTABLE = VTABLE::TESLevCharacter;
		inline static constexpr auto FORM_TYPE = FormType::LeveledActor;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;
	};

	static_assert(sizeof(TESLevCharacter) == 0xD8);
}
