#pragma once

#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/T/TESBoundAnimObject.hpp"
#include "RE/T/TESLeveledList.hpp"

namespace RE
{
	class __declspec(novtable) TESLevCharacter
		: public TESBoundAnimObject,  // 00
		  public TESLeveledList,	  // 68
		  public BGSModelMaterialSwap // 98
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESLevCharacter };
		inline static constexpr auto VTABLE{ VTABLE::TESLevCharacter };
		inline static constexpr auto FORM_TYPE{ FormType::kLeveledActor };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;
	};
	static_assert(sizeof(TESLevCharacter) == 0xD8);
}
