#pragma once

#include "RE/A/ApplyColorUpdateEvent.hpp"
#include "RE/B/BSGFxDisplayObject.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/H/HUDColorTypes.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/U/UIShaderColors.hpp"
#include "RE/U/UIShaderFXInfo.hpp"

namespace RE
{
	class /*__declspec(novtable)*/ BSGFxShaderFXTarget
		: public BSGFxDisplayObject,				 // 00
		  public BSTEventSink<ApplyColorUpdateEvent> // 50
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSGFxShaderFXTarget };
		inline static constexpr auto VTABLE{ VTABLE::BSGFxShaderFXTarget };

		// `function get bUseShadedBackground():Boolean;`, `function set bUseShadedBackground(value:Boolean):void;`
		inline static constexpr auto USE_SHADED_BACKGROUND_VAR_NAME = "bUseShadedBackground"sv;

		BSGFxShaderFXTarget(const ::Scaleform::GFx::Value& a_flashObject);
		BSGFxShaderFXTarget(const ::Scaleform::GFx::Value& a_flashObject, const char* a_relativePathToMember);
		BSGFxShaderFXTarget(const ::Scaleform::GFx::Movie& a_parentMovie, const char* a_pathToObject);

		~BSGFxShaderFXTarget() override; // 00

		// override (BSTEventSink<ApplyColorUpdateEvent>)
		BSEventNotifyControl ProcessEvent(const ApplyColorUpdateEvent& a_event, BSTEventSource<ApplyColorUpdateEvent>* a_eventSource) override; // 01

		// add
		virtual void AppendShaderFXInfos(BSTArray<UIShaderFXInfo>& a_colorFXInfo, BSTArray<UIShaderFXInfo>& a_backgroundFXInfo); // 02

		GAME_HEAP_REDEFINE_NEW(BSGFxShaderFXTarget);

		void CreateAndSetFiltersToColor(const NiColor& a_color, REX::Float32 a_brightness = 1.0_f32);
		void CreateAndSetFiltersToColor(std::uint8_t a_r, std::uint8_t a_g, std::uint8_t a_b, REX::Float32 a_brightness = 1.0_f32);
		void CreateAndSetFiltersToHUD(HUDColorTypes a_colorType, REX::Float32 a_scale = 1.0_f32);
		void EnableShadedBackground(HUDColorTypes a_colorType, REX::Float32 a_scale = 1.0_f32);
		void SetToHUDColor(bool a_useWarningColor);

		// members
		UIShaderColors shaderFX;									// 58
		BSTArray<BSGFxShaderFXTarget*> shaderFXObjects;				// 90
		REX::Enum<HUDColorTypes, std::int32_t> hudColorType;		// A8
		REX::Enum<HUDColorTypes, std::int32_t> backgroundColorType; // AC

	private:
		void ctor_shared();
	};
	static_assert(sizeof(BSGFxShaderFXTarget) == 0xB0);
}
