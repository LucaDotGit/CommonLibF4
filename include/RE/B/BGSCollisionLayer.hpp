#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSCollisionLayer
		: public TESForm,		// 00
		  public TESDescription // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSCollisionLayer };
		inline static constexpr auto VTABLE{ VTABLE::BGSCollisionLayer };
		inline static constexpr auto FORM_TYPE{ FormType::kCollisionLayer };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kTriggerVolume = 1 << 0,
			kSensor = 1 << 1,
			kNavMeshObstacle = 1 << 2
		};

		// members
		std::uint32_t collisionIndex;			   // 38
		std::uint32_t debugColor;				   // 3C
		REX::EnumSet<Flags, std::uint32_t> flags;  // 40
		BSFixedString name;						   // 48
		BSTArray<BGSCollisionLayer*> collidesWith; // 50
	};
	static_assert(sizeof(BGSCollisionLayer) == 0x68);
}
