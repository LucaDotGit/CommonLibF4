#pragma once

#include "RE/B/BGSExplosionData.hpp"
#include "RE/B/BGSPreloadable.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESEnchantableForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESImageSpaceModifiableForm.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSExplosion :
		public TESBoundObject,			   // 0x000
		public TESFullName,				   // 0x068
		public TESModel,				   // 0x078
		public TESEnchantableForm,		   // 0x0A8
		public BGSPreloadable,			   // 0x0C0
		public TESImageSpaceModifiableForm // 0x0C8
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSExplosion;
		inline static constexpr const auto& VTABLE = VTABLE::BGSExplosion;
		inline static constexpr auto FORM_TYPE = FormType::Explosion;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class EXPLOSION_TYPE : std::int32_t
		{
			Normal = 0,
			Chain = 1
		};

		enum class KnockDownMode : std::int32_t
		{
			Never = 0,
			Always = 1,
			Formula = 2,
			NPC = 3
		};

		// members
		BGSExplosionData data; // 0x0D8
	};

	static_assert(sizeof(BGSExplosion) == 0x148);
}
