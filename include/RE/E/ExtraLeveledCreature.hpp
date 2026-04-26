#pragma once

#include "RE/A/ACTOR_BASE_DATA.hpp"
#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraLeveledCreature
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraLeveledCreature };
		inline static constexpr auto VTABLE{ VTABLE::ExtraLeveledCreature };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kLeveledCreature };

		ExtraLeveledCreature()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLeveledCreature() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		TESActorBase* originalBase{ nullptr };																			// 18
		std::array<TESActorBase*, std::to_underlying(ACTOR_BASE_DATA::TEMPLATE_USE_FLAG::kTotal)> templates{ nullptr }; // 20
	};
	static_assert(sizeof(ExtraLeveledCreature) == 0x88);
}
