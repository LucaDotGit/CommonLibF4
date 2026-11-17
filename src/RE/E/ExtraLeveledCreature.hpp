#pragma once

#include "RE/A/ACTOR_BASE_DATA.hpp"
#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraLeveledCreature : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraLeveledCreature;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraLeveledCreature;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::LeveledCreature;

		ExtraLeveledCreature() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLeveledCreature() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		TESActorBase* originalBase{nullptr}; // 0x18
		std::array<TESActorBase*, std::to_underlying(ACTOR_BASE_DATA::TEMPLATE_USE_FLAG::_Count)> templates{
			nullptr
		}; // 0x20
	};

	static_assert(sizeof(ExtraLeveledCreature) == 0x88);
}
