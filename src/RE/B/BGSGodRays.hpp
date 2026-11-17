#pragma once

#include "RE/N/NiColor.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSGodRays : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSGodRays;
		inline static constexpr const auto& VTABLE = VTABLE::BGSGodRays;
		inline static constexpr auto FORM_TYPE = FormType::GodRays;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class GodRaysData
		{
		public:
			// members
			NiColor colorAir;			 // 0x00
			NiColor colorBack;			 // 0x0C
			NiColor colorForward;		 // 0x18
			REX::Float32 intensity;		 // 0x24
			REX::Float32 scatterAir;	 // 0x28
			REX::Float32 scatterBack;	 // 0x2C
			REX::Float32 scatterForward; // 0x30
			REX::Float32 phaseBack;		 // 0x34
			REX::Float32 phaseForward;	 // 0x38
		};

		static_assert(sizeof(GodRaysData) == 0x3C);

		// members
		GodRaysData data; // 0x20
	};

	static_assert(sizeof(BGSGodRays) == 0x60);
}
