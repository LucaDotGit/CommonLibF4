#pragma once

#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSPreloadable.hpp"
#include "RE/B/BGSProjectileData.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	enum class SOUND_LEVEL : std::int32_t;

	class __declspec(novtable) BGSProjectile
		: public TESBoundObject,		   // 000
		  public TESFullName,			   // 068
		  public TESModel,				   // 078
		  public BGSPreloadable,		   // 0A8
		  public BGSDestructibleObjectForm // 0B0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSProjectile };
		inline static constexpr auto VTABLE{ VTABLE::BGSProjectile };
		inline static constexpr auto FORM_TYPE{ FormType::kProjectile };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class MotionFlags : std::uint32_t
		{
			kFirstBit = 1 << 4,
			kMissile = 1 << 16,
			kGrenade = 1 << 17,
			kBeam = 1 << 18,
			kFlamethrower = 1 << 19,
			kCone = 1 << 20,
			kBarrier = 1 << 21,
			kArrow = 1 << 22,

			kAll = kMissile |
				   kGrenade |
				   kBeam |
				   kFlamethrower |
				   kCone |
				   kBarrier |
				   kArrow
		};

		// members
		BGSProjectileData data;							 // 0C0
		TESModel muzzleFlashModel;						 // 150
		REX::Enum<SOUND_LEVEL, std::int32_t> soundLevel; // 180
	};
	static_assert(sizeof(BGSProjectile) == 0x188);
}
