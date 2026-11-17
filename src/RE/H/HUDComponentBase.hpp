#pragma once

#include "RE/B/BSGFxShaderFXTarget.hpp"
#include "RE/C/CountdownTimer.hpp"
#include "RE/H/HUDModes.hpp"

namespace RE
{
	class __declspec(novtable) HUDComponentBase : public BSGFxShaderFXTarget // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::HUDComponentBase;
		inline static constexpr const auto& VTABLE = VTABLE::HUDComponentBase;

		enum class FADE_STATE : std::int32_t
		{
			In = 0,
			Out = 1,
			FadingIn = 2,
			FadingOut = 3
		};

		~HUDComponentBase() override; // 0x00

		// members
		CountdownTimer fadeOutTimer;				   // 0xB0
		HUDModes validHUDModes;						   // 0xC8
		REX::Float32 fadePerSecond;					   // 0xE8
		REX::Enum<FADE_STATE, std::int32_t> fadeState; // 0xEC
		bool flashElementsRegistered;				   // 0xF0
		bool widgetDisplayEnabled;					   // 0xF1
		bool displayWarningColor;					   // 0xF2
	};

	static_assert(sizeof(HUDComponentBase) == 0xF8);
}
