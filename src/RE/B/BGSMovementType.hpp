#pragma once

#include "RE/M/Movement_TypedData.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSMovementType : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSMovementType;
		inline static constexpr const auto& VTABLE = VTABLE::BGSMovementType;
		inline static constexpr auto FORM_TYPE = FormType::MovementType;

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
		Movement::TypeData movementTypeData; // 0x20
	};

	static_assert(sizeof(BGSMovementType) == 0xA0);
}
