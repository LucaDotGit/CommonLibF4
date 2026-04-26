#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/I/ImageSpaceModifierInstance.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceModifierInstanceForm
		: public ImageSpaceModifierInstance // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ImageSpaceModifierInstanceForm };
		inline static constexpr auto VTABLE{ VTABLE::ImageSpaceModifierInstanceForm };

		~ImageSpaceModifierInstanceForm() override; // 00

		// override (ImageSpaceModifierInstance)
		bool IsExpired() override;						   // 28
		void Apply() override;							   // 29
		void PrintInfo(char* a_buffer) override;		   // 2A
		ImageSpaceModifierInstanceForm* IsForm() override; // 2B

		static ImageSpaceModifierInstanceForm* Trigger(TESImageSpaceModifier* a_mod, REX::Float32 a_strength, NiAVObject* a_target)
		{
			using FuncType = ImageSpaceModifierInstanceForm* (*)(TESImageSpaceModifier*, REX::Float32, NiAVObject*);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::ImageSpaceModifierInstanceForm::Trigger01 };
			return std::invoke(FUNC, a_mod, a_strength, a_target);
		}

		static ImageSpaceModifierInstanceForm* Trigger(const BSFixedString& a_name)
		{
			using FuncType = ImageSpaceModifierInstanceForm* (*)(const BSFixedString&);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::ImageSpaceModifierInstanceForm::Trigger02 };
			return std::invoke(FUNC, a_name);
		}

		static void Stop(TESImageSpaceModifier* a_mod)
		{
			using FuncType = void (*)(TESImageSpaceModifier*);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::ImageSpaceModifierInstanceForm::Stop01 };
			FUNC(a_mod);
		}

		static void Stop(const BSFixedString& a_name)
		{
			using FuncType = void (*)(const BSFixedString&);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::ImageSpaceModifierInstanceForm::Stop02 };
			FUNC(a_name);
		}

		// members
		TESImageSpaceModifier* imageSpaceMod;	  // 28
		TESImageSpaceModifier* lastImageSpaceMod; // 30
		REX::Float32 lastStrength;				  // 38
		NiPointer<NiAVObject> lastTarget;		  // 40
		REX::Float32 transitionTime;			  // 48
	};
	static_assert(sizeof(ImageSpaceModifierInstanceForm) == 0x50);
}
