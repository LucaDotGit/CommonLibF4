#pragma once

#include "RE/M/MagicItem.hpp"

namespace RE::MagicSystem
{
	enum class CastingType : std::int32_t;
	enum class Delivery : std::int32_t;
	enum class SpellType : std::int32_t;
}

namespace RE
{
	class __declspec(novtable) EnchantmentItem
		: public MagicItem // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::EnchantmentItem };
		inline static constexpr auto VTABLE{ VTABLE::EnchantmentItem };
		inline static constexpr auto FORM_TYPE{ FormType::kEnchantment };

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
			: public MagicItem::Data // 00
		{
		public:
			// members
			REX::Enum<MagicSystem::CastingType, std::int32_t> castingType; // 08
			std::int32_t chargeOverride;								   // 0C
			REX::Enum<MagicSystem::Delivery, std::int32_t> delivery;	   // 10
			REX::Enum<MagicSystem::SpellType, std::int32_t> spellType;	   // 14
			REX::Float32 chargeTime;									   // 18
			EnchantmentItem* baseEnchantment;							   // 20
			BGSListForm* wornRestrictions;								   // 28
		};
		static_assert(sizeof(Data) == 0x30);

		// members
		Data data; // 0D0
	};
	static_assert(sizeof(EnchantmentItem) == 0x100);
}
