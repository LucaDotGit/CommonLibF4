#pragma once

#include "RE/M/Movement_TypedData.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSMovementType
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMovementType };
		inline static constexpr auto VTABLE{ VTABLE::BGSMovementType };
		inline static constexpr auto FORM_TYPE{ FormType::kMovementType };

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
		Movement::TypeData movementTypeData; // 20
	};
	static_assert(sizeof(BGSMovementType) == 0xA0);
}
