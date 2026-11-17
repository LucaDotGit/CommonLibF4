#pragma once

#include "RE/A/ADDON_DATA.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BSNonReentrantSpinLock.hpp"
#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	class __declspec(novtable) BGSAddonNode :
		public TESBoundObject,		// 0x00
		public BGSModelMaterialSwap // 0x68
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSAddonNode;
		inline static constexpr const auto& VTABLE = VTABLE::BGSAddonNode;
		inline static constexpr auto FORM_TYPE = FormType::AddonNode;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		std::uint32_t index;							   // 0xA8
		BGSSoundDescriptorForm* sound;					   // 0xB0
		TESObjectLIGH* light;							   // 0xB8
		ADDON_DATA data;								   // 0xC0
		mutable BSNonReentrantSpinLock masterParticleLock; // 0xC4
	};

	static_assert(sizeof(BGSAddonNode) == 0xC8);
}
