#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraPoison
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraPoison };
		inline static constexpr auto VTABLE{ VTABLE::ExtraPoison };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kPoison };

		ExtraPoison()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraPoison() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		std::uint32_t count{ 0 };		// 18
		AlchemyItem* poison{ nullptr }; // 20
	};
	static_assert(sizeof(ExtraPoison) == 0x28);
}
