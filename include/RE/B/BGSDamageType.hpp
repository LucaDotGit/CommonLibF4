#pragma once

#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSDamageType
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSDamageType };
		inline static constexpr auto VTABLE{ VTABLE::BGSDamageType };
		inline static constexpr auto FORM_TYPE{ FormType::kDamageType };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class Data
		{
		public:
			// members
			ActorValueInfo* resistance; // 00
			MagicItem* spell;			// 08
		};
		static_assert(sizeof(Data) == 0x10);

		// members
		Data data; // 20
	};
	static_assert(sizeof(BGSDamageType) == 0x30);
}
