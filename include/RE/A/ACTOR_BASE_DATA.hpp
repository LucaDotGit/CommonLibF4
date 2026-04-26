#pragma once

namespace RE
{
	class ACTOR_BASE_DATA
	{
	public:
		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kFemale = 1 << 0,
			kEssential = 1 << 1,
			kIsChargenFacePreset = 1 << 2,
			kRespawn = 1 << 3,
			kAutoCalcStats = 1 << 4,
			kUnique = 1 << 5,
			kDoesNotAffectStealthMeter = 1 << 6,
			kPCLevelMult = 1 << 7,
			kUsesTemplate = 1 << 8,
			kProtected = 1 << 11,
			kSummonable = 1 << 14,
			kDoesNotBleed = 1 << 16,
			kBleedoutOverride = 1 << 18,
			kOppositeGenderAnims = 1 << 19,
			kSimpleActor = 1 << 20,
			kLoopedScript = 1 << 21,
			kLoopedAudio = 1 << 28,
			kIsGhost = 1 << 29,
			kInvulnerable = 1ui32 << 31
		};

		enum class TEMPLATE_USE_FLAG : std::uint16_t
		{
			kNone = 0,
			kTraits = 1 << 0,
			kStats = 1 << 1,
			kFactions = 1 << 2,
			kSpells = 1 << 3,
			kAIData = 1 << 4,
			kAIPackages = 1 << 5,
			kUnused06 = 1 << 6,
			kBaseData = 1 << 7,
			kInventory = 1 << 8,
			kScript = 1 << 9,
			kAIDefPackList = 1 << 10,
			kAttackData = 1 << 11,
			kKeywords = 1 << 12,

			kTotal = 13,

			kAll = kTraits |
				   kStats |
				   kFactions |
				   kSpells |
				   kAIData |
				   kAIPackages |
				   kUnused06 |
				   kBaseData |
				   kInventory |
				   kScript |
				   kAIDefPackList |
				   kAttackData |
				   kKeywords
		};

		[[nodiscard]] static constexpr auto GetTemplateUseFlagIndex(TEMPLATE_USE_FLAG a_flag) noexcept -> std::optional<std::underlying_type_t<TEMPLATE_USE_FLAG>>
		{
			const auto flagSet = REX::EnumSet(a_flag);
			const auto flagMask = flagSet & TEMPLATE_USE_FLAG::kAll;

			if (flagMask.empty()) {
				return std::nullopt;
			}

			return static_cast<std::underlying_type_t<TEMPLATE_USE_FLAG>>(std::countr_zero(flagMask.underlying()));
		}

		// members
		REX::EnumSet<Flags, std::uint32_t> actorBaseFlags;				 // 00
		std::int16_t xpValueOffset;										 // 04
		std::uint16_t level;											 // 06
		std::uint16_t calcLevelMin;										 // 08
		std::uint16_t calcLevelMax;										 // 0A
		std::uint16_t baseDisposition;									 // 0C
		REX::EnumSet<TEMPLATE_USE_FLAG, std::uint16_t> templateUseFlags; // 0E
		std::int16_t bleedoutOverride;									 // 10
	};
	static_assert(sizeof(ACTOR_BASE_DATA) == 0x14);
}
