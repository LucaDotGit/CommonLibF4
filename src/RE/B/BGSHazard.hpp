#pragma once

#include "RE/B/BGSHazardData.hpp"
#include "RE/B/BGSPreloadable.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESImageSpaceModifiableForm.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSHazard :
		public TESBoundObject,			   // 0x000
		public TESFullName,				   // 0x068
		public TESModel,				   // 0x078
		public BGSPreloadable,			   // 0x0A8
		public TESImageSpaceModifiableForm // 0x0B0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSHazard;
		inline static constexpr const auto& VTABLE = VTABLE::BGSHazard;
		inline static constexpr auto FORM_TYPE = FormType::Hazard;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BGSHazardData data; // 0x0C0
	};

	static_assert(sizeof(BGSHazard) == 0x108);
}
