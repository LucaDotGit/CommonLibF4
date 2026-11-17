#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/I/ImageSpaceModifierInstance.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceModifierInstanceForm : public ImageSpaceModifierInstance // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceModifierInstanceForm;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceModifierInstanceForm;

		~ImageSpaceModifierInstanceForm() override; // 0x00

		// override (ImageSpaceModifierInstance)
		auto IsExpired() -> bool override;						   // 0x28
		void Apply() override;									   // 0x29
		void PrintInfo(char* a_buffer) override;				   // 0x2A
		auto IsForm() -> ImageSpaceModifierInstanceForm* override; // 0x2B

		static auto Trigger(TESImageSpaceModifier* a_mod, REX::Float32 a_strength, NiAVObject* a_target)
			-> ImageSpaceModifierInstanceForm*
		{
			using FuncType = ImageSpaceModifierInstanceForm* (*)(TESImageSpaceModifier*, REX::Float32, NiAVObject*);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ImageSpaceModifierInstanceForm::Trigger01);
			return std::invoke(FUNC, a_mod, a_strength, a_target);
		}

		static auto Trigger(const BSFixedString& a_name) -> ImageSpaceModifierInstanceForm*
		{
			using FuncType = ImageSpaceModifierInstanceForm* (*)(const BSFixedString&);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ImageSpaceModifierInstanceForm::Trigger02);
			return std::invoke(FUNC, a_name);
		}

		static void Stop(TESImageSpaceModifier* a_mod)
		{
			using FuncType = void (*)(TESImageSpaceModifier*);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ImageSpaceModifierInstanceForm::Stop01);
			std::invoke(FUNC, a_mod);
		}

		static void Stop(const BSFixedString& a_name)
		{
			using FuncType = void (*)(const BSFixedString&);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ImageSpaceModifierInstanceForm::Stop02);
			std::invoke(FUNC, a_name);
		}

		// members
		TESImageSpaceModifier* imageSpaceMod;	  // 0x28
		TESImageSpaceModifier* lastImageSpaceMod; // 0x30
		REX::Float32 lastStrength;				  // 0x38
		NiPointer<NiAVObject> lastTarget;		  // 0x40
		REX::Float32 transitionTime;			  // 0x48
	};

	static_assert(sizeof(ImageSpaceModifierInstanceForm) == 0x50);
}
