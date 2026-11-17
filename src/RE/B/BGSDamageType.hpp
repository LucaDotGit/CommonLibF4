#pragma once

#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSDamageType : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSDamageType;
		inline static constexpr const auto& VTABLE = VTABLE::BGSDamageType;
		inline static constexpr auto FORM_TYPE = FormType::DamageType;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class Data
		{
		public:
			// members
			ActorValueInfo* resistance; // 0x00
			MagicItem* spell;			// 0x08
		};

		static_assert(sizeof(Data) == 0x10);

		// members
		Data data; // 0x20
	};

	static_assert(sizeof(BGSDamageType) == 0x30);
}
