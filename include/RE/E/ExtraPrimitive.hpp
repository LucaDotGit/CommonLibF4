#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class BGSPrimitive;

	class __declspec(novtable) ExtraPrimitive
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraPrimitive };
		inline static constexpr auto VTABLE{ VTABLE::ExtraPrimitive };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kPrimitive };

		ExtraPrimitive()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraPrimitive() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		BGSPrimitive* primitive{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraPrimitive) == 0x20);
}
