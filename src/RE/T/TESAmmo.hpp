#pragma once

#include "RE/A/AMMO_DATA.hpp"
#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BGSMessageIcon.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSPickupPutdownSounds.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESIcon.hpp"
#include "RE/T/TESModel.hpp"
#include "RE/T/TESValueForm.hpp"
#include "RE/T/TESWeightForm.hpp"

namespace RE
{
	class __declspec(novtable) TESAmmo :
		public TESBoundObject,			  // 0x000
		public TESFullName,				  // 0x068
		public BGSModelMaterialSwap,	  // 0x078
		public TESIcon,					  // 0x0B8
		public BGSMessageIcon,			  // 0x0C8
		public TESValueForm,			  // 0x0E0
		public BGSDestructibleObjectForm, // 0x0F0
		public BGSPickupPutdownSounds,	  // 0x100
		public TESDescription,			  // 0x118
		public BGSKeywordForm,			  // 0x130
		public TESWeightForm			  // 0x150
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESAmmo;
		inline static constexpr const auto& VTABLE = VTABLE::TESAmmo;
		inline static constexpr auto FORM_TYPE = FormType::Ammo;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				NonPlayable = 1 << 2,
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		~TESAmmo() override; // 0x00

		[[nodiscard]]
		static auto GetReloadsWithAmmoRef(const TESAmmo* a_ammo) -> bool
		{
			using FuncType = decltype(&TESAmmo::GetReloadsWithAmmoRef);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESAmmo::GetReloadsWithAmmoRef);
			return std::invoke(FUNC, a_ammo);
		}

		// members
		AMMO_DATA data;				  // 0x160
		BGSLocalizedString shortDesc; // 0x178
		TESModel shellCasing;		  // 0x180
	};

	static_assert(sizeof(TESAmmo) == 0x1B0);
}
