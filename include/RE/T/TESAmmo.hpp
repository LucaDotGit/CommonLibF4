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
	class __declspec(novtable) TESAmmo
		: public TESBoundObject,			// 000
		  public TESFullName,				// 068
		  public BGSModelMaterialSwap,		// 078
		  public TESIcon,					// 0B8
		  public BGSMessageIcon,			// 0C8
		  public TESValueForm,				// 0E0
		  public BGSDestructibleObjectForm, // 0F0
		  public BGSPickupPutdownSounds,	// 100
		  public TESDescription,			// 118
		  public BGSKeywordForm,			// 130
		  public TESWeightForm				// 150
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESAmmo };
		inline static constexpr auto VTABLE{ VTABLE::TESAmmo };
		inline static constexpr auto FORM_TYPE{ FormType::kAmmo };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kNonPlayable = 1 << 2,
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		[[nodiscard]] static bool GetReloadsWithAmmoRef(const TESAmmo* a_ammo)
		{
			using FuncType = decltype(&TESAmmo::GetReloadsWithAmmoRef);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESAmmo::GetReloadsWithAmmoRef };
			return std::invoke(FUNC, a_ammo);
		}

		// members
		AMMO_DATA data;				  // 160
		BGSLocalizedString shortDesc; // 178
		TESModel shellCasing;		  // 180
	};
	static_assert(sizeof(TESAmmo) == 0x1B0);
}
