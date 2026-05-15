#pragma once

#include "RE/B/BSTempEffect.hpp"
#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class __declspec(novtable) BSTempEffectDebris
		: public BSTempEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSTempEffectDebris };
		inline static constexpr auto VTABLE{ VTABLE::BSTempEffectDebris };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSTempEffectDebris };
		inline static constexpr auto EFFECT_TYPE{ TEMP_EFFECT_TYPE::kDebris };

		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
		BSTempEffectDebris(
			TESObjectCELL* a_parentCell,
			REX::Float32 a_lifetime,
			const char* a_fileName,
			TESObjectREFR* a_sourceRef,
			const NiPoint3& a_position,
			const NiMatrix3& a_rotation,
			const NiPoint3& a_startLinearVelocity,
			const NiPoint3& a_startAngularVelocity,
			REX::Float32 a_scale,
			bool a_useCache,
			bool a_addDebrisCount,
			bool isFirstPerson)
		{
			using FuncType = void (BSTempEffectDebris::*)(
				TESObjectCELL*,
				REX::Float32,
				const char*,
				TESObjectREFR*,
				const NiPoint3&,
				const NiMatrix3&,
				const NiPoint3&,
				const NiPoint3&,
				REX::Float32,
				bool,
				bool,
				bool);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSTempEffectDebris::ctor };
			std::invoke(FUNC, this,
				a_parentCell,
				a_lifetime,
				a_fileName,
				a_sourceRef,
				a_position,
				a_rotation,
				a_startLinearVelocity,
				a_startAngularVelocity,
				a_scale,
				a_useCache,
				a_addDebrisCount,
				isFirstPerson);
		}

		~BSTempEffectDebris() override; // 00

		// members
		NiPointer<NiAVObject> debris3D; // 30
		const char* debrisFilename;		// 38
		bool useDebrisCounter;			// 40
		bool forceDelete;				// 41
		bool firstPerson;				// 42
	};
	static_assert(sizeof(BSTempEffectDebris) == 0x48);
}
