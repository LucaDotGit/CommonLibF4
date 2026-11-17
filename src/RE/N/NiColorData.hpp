#pragma once

#include "RE/N/NiAnimationKey.hpp"
#include "RE/N/NiObject.hpp"

namespace RE
{
	class NiColorKey;

	class __declspec(novtable) NiColorData : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiColorData;
		inline static constexpr const auto& VTABLE = VTABLE::NiColorData;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiColorData;

		~NiColorData() override; // 0x00

		// members
		std::uint32_t numKeys;									  // 0x18
		NiColorKey* keys;										  // 0x20
		REX::Enum<NiAnimationKey::KeyType, std::int32_t> keyType; // 0x28
		std::uint8_t keySize;									  // 0x2C
	};

	static_assert(sizeof(NiColorData) == 0x28);
}
