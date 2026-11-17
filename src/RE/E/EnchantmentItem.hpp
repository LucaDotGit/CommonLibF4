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
	class __declspec(novtable) EnchantmentItem : public MagicItem // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::EnchantmentItem;
		inline static constexpr const auto& VTABLE = VTABLE::EnchantmentItem;
		inline static constexpr auto FORM_TYPE = FormType::Enchantment;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class Data : public MagicItem::Data // 0x00
		{
		public:
			// members
			REX::Enum<MagicSystem::CastingType, std::int32_t> castingType; // 0x08
			std::int32_t chargeOverride;								   // 0x0C
			REX::Enum<MagicSystem::Delivery, std::int32_t> delivery;	   // 0x10
			REX::Enum<MagicSystem::SpellType, std::int32_t> spellType;	   // 0x14
			REX::Float32 chargeTime;									   // 0x18
			EnchantmentItem* baseEnchantment;							   // 0x20
			BGSListForm* wornRestrictions;								   // 0x28
		};

		static_assert(sizeof(Data) == 0x30);

		~EnchantmentItem() override; // 0x00

		// members
		Data data; // 0x0D0
	};

	static_assert(sizeof(EnchantmentItem) == 0x100);
}
