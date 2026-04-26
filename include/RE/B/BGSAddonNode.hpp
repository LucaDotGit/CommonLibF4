#pragma once

#include "RE/A/ADDON_DATA.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	class __declspec(novtable) BGSAddonNode
		: public TESBoundObject,	  // 00
		  public BGSModelMaterialSwap // 68
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAddonNode };
		inline static constexpr auto VTABLE{ VTABLE::BGSAddonNode };
		inline static constexpr auto FORM_TYPE{ FormType::kAddonNode };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		std::uint32_t index;							   // A8
		BGSSoundDescriptorForm* sound;					   // B0
		TESObjectLIGH* light;							   // B8
		ADDON_DATA data;								   // C0
		mutable BSNonReentrantSpinLock masterParticleLock; // C4
	};
	static_assert(sizeof(BGSAddonNode) == 0xC8);
}
