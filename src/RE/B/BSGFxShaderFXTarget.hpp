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
	class NiColor;

	class /*__declspec(novtable)*/ BSGFxShaderFXTarget :
		public BSGFxDisplayObject,				   // 0x00
		public BSTEventSink<ApplyColorUpdateEvent> // 0x50
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSGFxShaderFXTarget;
		inline static constexpr const auto& VTABLE = VTABLE::BSGFxShaderFXTarget;

		// `function get bUseShadedBackground():Boolean;`, `function set bUseShadedBackground(value:Boolean):void;`
		inline static constexpr auto USE_SHADED_BACKGROUND_VAR_NAME = "bUseShadedBackground"sv;

		explicit BSGFxShaderFXTarget(const Scaleform::GFx::Value& a_flashObject);
		BSGFxShaderFXTarget(const Scaleform::GFx::Value& a_flashObject, const char* a_relativePathToMember);
		BSGFxShaderFXTarget(const Scaleform::GFx::Movie& a_parentMovie, const char* a_pathToObject);

		BSGFxShaderFXTarget(const BSGFxShaderFXTarget&) = delete;
		BSGFxShaderFXTarget(BSGFxShaderFXTarget&&) = delete;

		auto operator=(const BSGFxShaderFXTarget&) -> BSGFxShaderFXTarget& = delete;
		auto operator=(BSGFxShaderFXTarget&&) -> BSGFxShaderFXTarget& = delete;

		~BSGFxShaderFXTarget() override; // 0x00

		// override (BSTEventSink<ApplyColorUpdateEvent>)
		auto ProcessEvent(
			const ApplyColorUpdateEvent& a_event,
			BSTEventSource<ApplyColorUpdateEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// add
		virtual void AppendShaderFXInfos(
			BSTArray<UIShaderFXInfo>& a_colorFXInfo,
			BSTArray<UIShaderFXInfo>& a_backgroundFXInfo); // 0x02

		GAME_HEAP_REDEFINE_NEW(BSGFxShaderFXTarget);

		void CreateAndSetFiltersToColor(
			const NiColor& a_color,
			REX::Float32 a_brightness = static_cast<REX::Float32>(1.0));
		void CreateAndSetFiltersToColor(
			std::uint8_t a_red,
			std::uint8_t a_green,
			std::uint8_t a_blue,
			REX::Float32 a_brightness = static_cast<REX::Float32>(1.0));
		void CreateAndSetFiltersToHUD(HUDColorTypes a_colorType, REX::Float32 a_scale = static_cast<REX::Float32>(1.0));
		void EnableShadedBackground(HUDColorTypes a_colorType, REX::Float32 a_scale = static_cast<REX::Float32>(1.0));

	private:
		void ctor_shared();

	public:
		// members
		UIShaderColors shaderFX;									// 0x58
		BSTArray<BSGFxShaderFXTarget*> shaderFXObjects;				// 0x90
		REX::Enum<HUDColorTypes, std::int32_t> hudColorType;		// 0xA8
		REX::Enum<HUDColorTypes, std::int32_t> backgroundColorType; // 0xAC
	};

	static_assert(sizeof(BSGFxShaderFXTarget) == 0xB0);
}
