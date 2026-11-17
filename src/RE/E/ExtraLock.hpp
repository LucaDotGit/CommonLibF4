#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class REFR_LOCK;

	class __declspec(novtable) ExtraLock : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraLock;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraLock;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Lock;

		ExtraLock() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLock() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		REFR_LOCK* lock{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraLock) == 0x20);
}
