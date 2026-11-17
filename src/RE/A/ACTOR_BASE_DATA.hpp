#pragma once

namespace RE
{
	class ACTOR_BASE_DATA
	{
	public:
		enum class Flags : std::uint32_t
		{
			None = 0,
			Female = 1 << 0,
			Essential = 1 << 1,
			IsChargenFacePreset = 1 << 2,
			Respawn = 1 << 3,
			AutoCalcStats = 1 << 4,
			Unique = 1 << 5,
			DoesNotAffectStealthMeter = 1 << 6,
			PCLevelMult = 1 << 7,
			UsesTemplate = 1 << 8,
			Protected = 1 << 11,
			Summonable = 1 << 14,
			DoesNotBleed = 1 << 16,
			BleedoutOverride = 1 << 18,
			OppositeGenderAnims = 1 << 19,
			SimpleActor = 1 << 20,
			LoopedScript = 1 << 21,
			LoopedAudio = 1 << 28,
			IsGhost = 1 << 29,
			Invulnerable = static_cast<std::uint32_t>(1) << 31
		};

		enum class TEMPLATE_USE_FLAG : std::uint16_t
		{
			None = 0,
			Traits = 1 << 0,
			Stats = 1 << 1,
			Factions = 1 << 2,
			Spells = 1 << 3,
			AIData = 1 << 4,
			AIPackages = 1 << 5,
			Unused06 = 1 << 6,
			BaseData = 1 << 7,
			Inventory = 1 << 8,
			Script = 1 << 9,
			AIDefPackList = 1 << 10,
			AttackData = 1 << 11,
			Keywords = 1 << 12,

			_Count = 13,

			_All = Traits |
				Stats |
				Factions |
				Spells |
				AIData |
				AIPackages |
				Unused06 |
				BaseData |
				Inventory |
				Script |
				AIDefPackList |
				AttackData |
				Keywords
		};

		[[nodiscard]]
		static constexpr auto GetTemplateUseFlagIndex(TEMPLATE_USE_FLAG a_flag) noexcept
			-> std::optional<std::underlying_type_t<TEMPLATE_USE_FLAG>>
		{
			const auto flagSet = REX::EnumSet(a_flag);
			if (flagSet.none(TEMPLATE_USE_FLAG::_All)) {
				return std::nullopt;
			}

			return static_cast<std::underlying_type_t<TEMPLATE_USE_FLAG>>(std::countr_zero(flagSet.underlying()));
		}

		// members
		REX::EnumSet<Flags, std::uint32_t> actorBaseFlags;				 // 0x00
		std::int16_t xpValueOffset;										 // 0x04
		std::uint16_t level;											 // 0x06
		std::uint16_t calcLevelMin;										 // 0x08
		std::uint16_t calcLevelMax;										 // 0x0A
		std::uint16_t baseDisposition;									 // 0x0C
		REX::EnumSet<TEMPLATE_USE_FLAG, std::uint16_t> templateUseFlags; // 0x0E
		std::int16_t bleedoutOverride;									 // 0x10
	};

	static_assert(sizeof(ACTOR_BASE_DATA) == 0x14);
}
