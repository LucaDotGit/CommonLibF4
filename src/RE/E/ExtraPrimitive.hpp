#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class BGSPrimitive;

	class __declspec(novtable) ExtraPrimitive : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraPrimitive;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraPrimitive;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Primitive;

		ExtraPrimitive() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraPrimitive() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		BGSPrimitive* primitive{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraPrimitive) == 0x20);
}
