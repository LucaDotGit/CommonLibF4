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
	class __declspec(novtable) SpellItem
		: public MagicItem,			   // 000
		  public BGSEquipType,		   // 0D0
		  public BGSMenuDisplayObject, // 0E0
		  public TESDescription		   // 0F0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::SpellItem };
		inline static constexpr auto VTABLE{ VTABLE::SpellItem };
		inline static constexpr auto FORM_TYPE{ FormType::kSpell };

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
			REX::Enum<MagicSystem::SpellType, std::int32_t> spellType;	   // 08
			REX::Float32 chargeTime;									   // 0C
			REX::Enum<MagicSystem::CastingType, std::int32_t> castingType; // 10
			REX::Enum<MagicSystem::Delivery, std::int32_t> delivery;	   // 14
			REX::Float32 castDuration;									   // 18
			REX::Float32 range;											   // 1C
			BGSPerk* castingPerk;										   // 20
		};
		static_assert(sizeof(Data) == 0x28);

		// members
		Data data; // 108
	};
	static_assert(sizeof(SpellItem) == 0x130);
}
