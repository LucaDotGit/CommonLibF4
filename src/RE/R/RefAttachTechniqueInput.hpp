#pragma once

#include "RE/A/AttachTechniqueInput.hpp"
#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class bhkWorld;

	class __declspec(novtable) RefAttachTechniqueInput : public BSAttachTechniques::AttachTechniqueInput // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::RefAttachTechniqueInput;
		inline static constexpr const auto& VTABLE = VTABLE::RefAttachTechniqueInput;

		// members
		TESObjectREFR* object;		   // 0x20
		TESRace* race;				   // 0x28
		bhkWorld* havokWorld;		   // 0x30
		std::uint32_t collisionGroup;  // 0x38
		BSFixedString techniqueSuffix; // 0x40
	};

	static_assert(sizeof(RefAttachTechniqueInput) == 0x48);
}
