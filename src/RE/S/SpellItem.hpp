#pragma once

#include "RE/B/BGSEquipType.hpp"
#include "RE/B/BGSMenuDisplayObject.hpp"
#include "RE/M/MagicItem.hpp"
#include "RE/T/TESDescription.hpp"

namespace RE::MagicSystem
{
	enum class CastingType : std::int32_t;
	enum class Delivery : std::int32_t;
	enum class SpellType : std::int32_t;
}

namespace RE
{
	class __declspec(novtable) SpellItem :
		public MagicItem,			 // 0x000
		public BGSEquipType,		 // 0x0D0
		public BGSMenuDisplayObject, // 0x0E0
		public TESDescription		 // 0x0F0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::SpellItem;
		inline static constexpr const auto& VTABLE = VTABLE::SpellItem;
		inline static constexpr auto FORM_TYPE = FormType::Spell;

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
			REX::Enum<MagicSystem::SpellType, std::int32_t> spellType;	   // 0x08
			REX::Float32 chargeTime;									   // 0x0C
			REX::Enum<MagicSystem::CastingType, std::int32_t> castingType; // 0x10
			REX::Enum<MagicSystem::Delivery, std::int32_t> delivery;	   // 0x14
			REX::Float32 castDuration;									   // 0x18
			REX::Float32 range;											   // 0x1C
			BGSPerk* castingPerk;										   // 0x20
		};

		static_assert(sizeof(Data) == 0x28);

		~SpellItem() override; // 0x00

		// members
		Data data; // 0x108
	};

	static_assert(sizeof(SpellItem) == 0x130);
}
