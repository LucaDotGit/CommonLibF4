#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/T/TESObjectACTIDefs_RadioReceiverData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraRadioReceiver
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraRadioReceiver };
		inline static constexpr auto VTABLE{ VTABLE::ExtraRadioReceiver };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kRadioReceiver };

		ExtraRadioReceiver()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraRadioReceiver() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		TESObjectACTIDefs::RadioReceiverData data; // 18
	};
	static_assert(sizeof(ExtraRadioReceiver) == 0x30);
}
