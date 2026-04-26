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
	class __declspec(novtable) BGSExplosion
		: public TESBoundObject,			 // 000
		  public TESFullName,				 // 068
		  public TESModel,					 // 078
		  public TESEnchantableForm,		 // 0A8
		  public BGSPreloadable,			 // 0C0
		  public TESImageSpaceModifiableForm // 0C8
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSExplosion };
		inline static constexpr auto VTABLE{ VTABLE::BGSExplosion };
		inline static constexpr auto FORM_TYPE{ FormType::kExplosion };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class EXPLOSION_TYPE : std::int32_t
		{
			kNormal = 0,
			kChain = 1
		};

		enum class KnockDownMode : std::int32_t
		{
			kNever = 0,
			kAlways = 1,
			kFormula = 2,
			kNPC = 3
		};

		// members
		BGSExplosionData data; // 0D8
	};
	static_assert(sizeof(BGSExplosion) == 0x148);
}
