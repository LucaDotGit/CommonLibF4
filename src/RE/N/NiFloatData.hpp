#pragma once

#include "RE/N/NiAnimationKey.hpp"
#include "RE/N/NiObject.hpp"

namespace RE
{
	class NiFloatKey;

	class __declspec(novtable) NiFloatData : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiFloatData;
		inline static constexpr const auto& VTABLE = VTABLE::NiFloatData;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiFloatData;

		~NiFloatData() override; // 0x00

		// members
		std::uint32_t numKeys;									  // 0x18
		NiFloatKey* keys;										  // 0x20
		REX::Enum<NiAnimationKey::KeyType, std::int32_t> keyType; // 0x28
		std::uint8_t keySize;									  // 0x2C
	};

	static_assert(sizeof(NiFloatData) == 0x28);
}
