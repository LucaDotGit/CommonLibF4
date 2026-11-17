#pragma once

#include "RE/N/NiAnimationKey.hpp"
#include "RE/N/NiInterpolator.hpp"

namespace RE
{
	class __declspec(novtable) NiKeyBasedInterpolator : public NiInterpolator // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiKeyBasedInterpolator;
		inline static constexpr const auto& VTABLE = VTABLE::NiKeyBasedInterpolator;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiKeyBasedInterpolator;

		~NiKeyBasedInterpolator() override; // 0x00

		// add
		virtual auto GetKeyChannelCount() -> std::uint16_t = 0;								   // 0x3C
		virtual auto GetKeyCount(std::uint16_t a_channel) -> std::uint32_t = 0;				   // 0x3D
		virtual auto GetKeyType(std::uint16_t a_channel) -> NiAnimationKey::KeyType = 0;	   // 0x3E
		virtual auto GetKeyContent(std::uint16_t a_channel) -> NiAnimationKey::KeyContent = 0; // 0x3F
		virtual auto GetKeyArray(std::uint16_t a_channel) -> NiAnimationKey* = 0;			   // 0x40
		virtual auto GetKeyStride(std::uint16_t a_channel) -> std::uint8_t = 0;				   // 0x41
		virtual auto GetChannelPosed(std::uint16_t a_channel) -> bool = 0;					   // 0x42
	};

	static_assert(sizeof(NiKeyBasedInterpolator) == 0x18);
}
