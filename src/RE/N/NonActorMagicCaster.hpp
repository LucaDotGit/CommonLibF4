#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/E/ExtraMagicCaster.hpp"

namespace RE
{
	class __declspec(novtable) NonActorMagicCaster : public ExtraMagicCaster // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NonActorMagicCaster;
		inline static constexpr const auto& VTABLE = VTABLE::NonActorMagicCaster;

		~NonActorMagicCaster() override; // 0x00

		// members
		TESObjectREFR* ref;		// 0x60
		ActorHandle blameActor; // 0x68
	};

	static_assert(sizeof(NonActorMagicCaster) == 0x70);
}
