#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/S/SETTING_VALUE.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class __declspec(novtable) BGSShaderParticleGeometryData : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSShaderParticleGeometryData;
		inline static constexpr const auto& VTABLE = VTABLE::BGSShaderParticleGeometryData;
		inline static constexpr auto FORM_TYPE = FormType::ShaderParticleGeometry;

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
		BSTArray<SETTING_VALUE> data; // 0x20
		TESTexture particleTexture;	  // 0x38
		BSFixedString materialName;	  // 0x48
	};

	static_assert(sizeof(BGSShaderParticleGeometryData) == 0x50);
}
