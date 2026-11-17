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

	class __declspec(novtable) BGSProjectile :
		public TESBoundObject,			 // 0x000
		public TESFullName,				 // 0x068
		public TESModel,				 // 0x078
		public BGSPreloadable,			 // 0x0A8
		public BGSDestructibleObjectForm // 0x0B0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSProjectile;
		inline static constexpr const auto& VTABLE = VTABLE::BGSProjectile;
		inline static constexpr auto FORM_TYPE = FormType::Projectile;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class MotionFlags : std::uint32_t
		{
			FirstBit = 1 << 4,
			Missile = 1 << 16,
			Grenade = 1 << 17,
			Beam = 1 << 18,
			Flamethrower = 1 << 19,
			Cone = 1 << 20,
			Barrier = 1 << 21,
			Arrow = 1 << 22
		};

		// members
		BGSProjectileData data;							 // 0x0C0
		TESModel muzzleFlashModel;						 // 0x150
		REX::Enum<SOUND_LEVEL, std::int32_t> soundLevel; // 0x180
	};

	static_assert(sizeof(BGSProjectile) == 0x188);
}
