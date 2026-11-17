#pragma once

#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTOptional.hpp"
#include "RE/H/HUDModeType.hpp"
#include "RE/I/IMenu.hpp"
#include "RE/U/UIShaderFXInfo.hpp"
#include "msvc/memory.hpp"

namespace RE
{
	enum class HUDColorTypes : std::int32_t;

	class BSGFxShaderFXTarget;
	class ButtonHintBar;
	class NiColor;

	class /*__declspec(novtable)*/ GameMenuBase : public IMenu // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameMenuBase;
		inline static constexpr const auto& VTABLE = VTABLE::GameMenuBase;

		GameMenuBase();

		GameMenuBase(const GameMenuBase&) = delete;
		GameMenuBase(GameMenuBase&&) = delete;

		auto operator=(const GameMenuBase&) -> GameMenuBase& = delete;
		auto operator=(GameMenuBase&&) -> GameMenuBase& = delete;

		~GameMenuBase() override; // 0x00

		// override (IMenu)
		void SetIsTopButtonBar(bool a_isTopButtonBar) override;									   // 0x08
		void OnMenuDisplayStateChanged() override;												   // 0x0A
		void OnAddedToMenuStack() override;														   // 0x0B
		void OnRemovedFromMenuStack() override;													   // 0x0C
		auto CacheShaderFXQuadsForRenderer_Impl() -> bool override;								   // 0x10
		void TransferCachedShaderFXQuadsForRenderer(const BSFixedString& a_rendererName) override; // 0x11
		void SetViewportRect(const NiRectF& a_viewportRect) override;							   // 0x12

		// add
		virtual void AppendShaderFXInfos(
			BSTAlignedArray<UIShaderFXInfo>& a_colorFXInfos,
			BSTAlignedArray<UIShaderFXInfo>& a_backgroundFXInfos) const; // 0x13

		void SetUpButtonBar(
			BSGFxShaderFXTarget& a_parentObject,
			const char* a_buttonBarPath,
			HUDColorTypes a_colorType);

		void SetupHUDShaderFXTargets(HUDColorTypes a_colorType, REX::Float32 a_scale = static_cast<REX::Float32>(1.0));
		void SetupCustomShaderFXTargets(
			const NiColor& a_color,
			REX::Float32 a_brightness = static_cast<REX::Float32>(1.0));
		void SetupCustomShaderFXTargets(
			std::uint8_t a_red,
			std::uint8_t a_green,
			std::uint8_t a_blue,
			REX::Float32 a_brightness = static_cast<REX::Float32>(1.0));

		// members
		BSTArray<BSGFxShaderFXTarget*> shaderFXObjects;			 // 0x70
		msvc::unique_ptr<BSGFxShaderFXTarget> filterHolder;		 // 0x88
		msvc::unique_ptr<ButtonHintBar> buttonHintBar;			 // 0x90
		BSTAlignedArray<UIShaderFXInfo> cachedColorFXInfos;		 // 0x98
		BSTAlignedArray<UIShaderFXInfo> cachedBackgroundFXInfos; // 0xB0
		mutable BSReadWriteLock cachedQuadsLock;				 // 0xC8
		BSTOptional<HUDModeType> menuHUDMode{std::nullopt};		 // 0xD0
	};

	static_assert(sizeof(GameMenuBase) == 0xE0);
}
