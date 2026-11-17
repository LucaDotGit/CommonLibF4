#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class __declspec(novtable) BSAudioListener
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSAudioListener;
		inline static constexpr const auto& VTABLE = VTABLE::BSAudioListener;

		virtual ~BSAudioListener() = default; // 0x00

		// add
		virtual void SetPosition(const NiPoint3& a_position) = 0;
		virtual void Reset(REX::Float32 a_value) = 0;

		// members
		NiPoint3 listenerPosition{NiPoint3::ZERO};					// 0x00
		NiPoint3 frontOrientation{NiPoint3::UNIT_X};				// 0x14
		NiPoint3 topOrientation{NiPoint3::UNIT_Z};					// 0x20
		NiPoint3 velocity{NiPoint3::ZERO};							// 0x2C
		std::chrono::milliseconds timeLastUpdated{0};				// 0x38
		REX::Float32 velocityScale{static_cast<REX::Float32>(1.0)}; // 0x40
	};

	static_assert(sizeof(BSAudioListener) == 0x48);
}
