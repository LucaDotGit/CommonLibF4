#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/S/SETTING_VALUE.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class __declspec(novtable) BGSShaderParticleGeometryData
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSShaderParticleGeometryData };
		inline static constexpr auto VTABLE{ VTABLE::BGSShaderParticleGeometryData };
		inline static constexpr auto FORM_TYPE{ FormType::kShaderParticleGeometry };

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
		BSTArray<SETTING_VALUE> data; // 20
		TESTexture particleTexture;	  // 38
		BSFixedString materialName;	  // 48
	};
	static_assert(sizeof(BGSShaderParticleGeometryData) == 0x50);
}
