#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSCollisionLayer :
		public TESForm,		  // 0x00
		public TESDescription // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSCollisionLayer;
		inline static constexpr const auto& VTABLE = VTABLE::BGSCollisionLayer;
		inline static constexpr auto FORM_TYPE = FormType::CollisionLayer;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			None = 0,
			TriggerVolume = 1 << 0,
			Sensor = 1 << 1,
			NavMeshObstacle = 1 << 2
		};

		// members
		std::uint32_t collisionIndex;			   // 0x38
		std::uint32_t debugColor;				   // 0x3C
		REX::EnumSet<Flags, std::uint32_t> flags;  // 0x40
		BSFixedString name;						   // 0x48
		BSTArray<BGSCollisionLayer*> collidesWith; // 0x50
	};

	static_assert(sizeof(BGSCollisionLayer) == 0x68);
}
