#pragma once

#include "RE/B/BSTempEffect.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiAVObject;

	class __declspec(novtable) BSTempEffectWeaponBlood : public BSTempEffect // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSTempEffectWeaponBlood;
		inline static constexpr const auto& VTABLE = VTABLE::BSTempEffectWeaponBlood;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSTempEffect;
		inline static constexpr auto EFFECT_TYPE = TEMP_EFFECT_TYPE::WeaponBlood;

		~BSTempEffectWeaponBlood() override; // 0x00

		static void ClearEffectForWeapon(NiAVObject* a_weapon3D)
		{
			using FuncType = decltype(&BSTempEffectWeaponBlood::ClearEffectForWeapon);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSTempEffectWeaponBlood::ClearEffectForWeapon);
			std::invoke(FUNC, a_weapon3D);
		}

		// members
		NiPointer<NiAVObject> weapon; // 0x30
		REX::Float32 fBloodAmount;	  // 0x38
	};

	static_assert(sizeof(BSTempEffectWeaponBlood) == 0x40);
}
