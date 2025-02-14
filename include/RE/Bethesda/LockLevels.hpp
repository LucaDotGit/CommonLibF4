#pragma once

namespace RE
{
	class TESKey;
	class TESObjectREFR;

	enum class LOCK_LEVEL
	{
		kUnlocked = static_cast<std::underlying_type_t<LOCK_LEVEL>>(-1),
		kEasy = 0,
		kAverage = 1,
		kHard = 2,
		kVeryHard = 3,
		kRequiresKey = 4,
		kInaccessible = 5,
		kTerminal = 6,
		kBarred = 7,
		kChained = 8
	};

	struct REFR_LOCK
	{
	public:
		enum class Flags
		{
			kNone = 0,
			kLocked = 1 << 0,
			kLeveled = 1 << 2
		};

		[[nodiscard]] static std::underlying_type_t<LOCK_LEVEL> GetLevelForLock(LOCK_LEVEL a_lockLevel) noexcept
		{
			switch (a_lockLevel) {
				case LOCK_LEVEL::kEasy:
					return 25;
				case LOCK_LEVEL::kAverage:
					return 50;
				case LOCK_LEVEL::kHard:
					return 75;
				case LOCK_LEVEL::kVeryHard:
					return 100;
				case LOCK_LEVEL::kBarred:
					return 251;
				case LOCK_LEVEL::kChained:
					return 252;
				case LOCK_LEVEL::kTerminal:
					return 253;
				case LOCK_LEVEL::kInaccessible:
					return 254;
				case LOCK_LEVEL::kRequiresKey:
					return 255;
				default:
					return 0;
			}
		}

		[[nodiscard]] LOCK_LEVEL GetLockLevel(TESObjectREFR* a_owner)
		{
			using func_t = decltype(&REFR_LOCK::GetLockLevel);
			static REL::Relocation<func_t> func{ REL::RelocationID(782953, 2191018) };
			return func(this, a_owner);
		}

		void SetLocked(bool a_locked)
		{
			using func_t = decltype(&REFR_LOCK::SetLocked);
			static REL::Relocation<func_t> func{ REL::RelocationID(157617, 2191020) };
			return func(this, a_locked);
		}

		F4_HEAP_REDEFINE_NEW(REFR_LOCK);

		// members
		std::uint8_t baseLevel;					  // 00
		TESKey* key;							  // 08
		REX::EnumSet<Flags, std::uint32_t> flags; // 10
		std::uint32_t numTries;					  // 14
	};
	static_assert(sizeof(REFR_LOCK) == 0x18);
}
