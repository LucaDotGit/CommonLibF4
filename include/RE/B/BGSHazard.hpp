#pragma once

#include "RE/B/BGSHazardData.hpp"
#include "RE/B/BGSPreloadable.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESImageSpaceModifiableForm.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSHazard
		: public TESBoundObject,			 // 000
		  public TESFullName,				 // 068
		  public TESModel,					 // 078
		  public BGSPreloadable,			 // 0A8
		  public TESImageSpaceModifiableForm // 0B0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSHazard };
		inline static constexpr auto VTABLE{ VTABLE::BGSHazard };
		inline static constexpr auto FORM_TYPE{ FormType::kHazard };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BGSHazardData data; // 0C0
	};
	static_assert(sizeof(BGSHazard) == 0x108);
}
