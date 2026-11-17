#pragma once

#include "RE/I/ImageSpaceModData.hpp"
#include "RE/I/ImageSpaceModifierInstanceTemp.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceModifierInstanceDOF : public ImageSpaceModifierInstanceTemp // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceModifierInstanceDOF;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceModifierInstanceDOF;

		enum class DepthOfFieldMode : std::int32_t
		{
			FrontBack = 0,
			Front,
			Back,
			None
		};

		~ImageSpaceModifierInstanceDOF() override; // 0x00

		// override (ImageSpaceModifierInstanceTemp)
		void Apply() override;					 // 0x29
		void PrintInfo(char* a_buffer) override; // 0x2A

		static auto Trigger(
			REX::Float32 a_distance,
			REX::Float32 a_range,
			REX::Float32 a_vignetteRadius,
			REX::Float32 a_vignetteStrength,
			DepthOfFieldMode a_mode,
			REX::Float32 a_strength,
			REX::Float32 a_duration) -> ImageSpaceModifierInstanceDOF*
		{
			using FuncType = decltype(&ImageSpaceModifierInstanceDOF::Trigger);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ImageSpaceModifierInstanceDOF::Trigger);
			return std::invoke(
				FUNC,
				a_distance,
				a_range,
				a_vignetteRadius,
				a_vignetteStrength,
				a_mode,
				a_strength,
				a_duration);
		}

		// members
		ImageSpaceModData data; // 0x30
	};

	static_assert(sizeof(ImageSpaceModifierInstanceDOF) == 0x80);
}
