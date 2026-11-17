#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/T/TESObjectACTIDefs_RadioReceiverData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraRadioReceiver : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraRadioReceiver;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraRadioReceiver;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::RadioReceiver;

		ExtraRadioReceiver() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraRadioReceiver() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		TESObjectACTIDefs::RadioReceiverData data; // 0x18
	};

	static_assert(sizeof(ExtraRadioReceiver) == 0x30);
}
