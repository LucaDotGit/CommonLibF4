#pragma once

#include "RE/B/BSGFxShaderFXTarget.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTOptional.hpp"
#include "RE/B/ButtonHintBar.hpp"
#include "RE/H/HUDModeType.hpp"
#include "RE/I/IMenu.hpp"
#include "RE/S/SendHUDMessage.hpp"

#include "msvc/memory.hpp"

namespace RE
{
	class __declspec(novtable) GameMenuBase
		: public IMenu // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameMenuBase };
		inline static constexpr auto VTABLE{ VTABLE::GameMenuBase };

		GameMenuBase();

		~GameMenuBase() override; // 00

		// override (IMenu)
		void SetIsTopButtonBar(bool a_isTopButtonBar) override;									   // 08
		void OnMenuDisplayStateChanged() override;												   // 0A
		void OnAddedToMenuStack() override;														   // 0B
		void OnRemovedFromMenuStack() override;													   // 0C
		bool CacheShaderFXQuadsForRenderer_Impl() override;										   // 10
		void TransferCachedShaderFXQuadsForRenderer(const BSFixedString& a_rendererName) override; // 11
		void SetViewportRect(const NiRect<REX::Float32>& a_viewportRect) override;				   // 12

		// add
		virtual void AppendShaderFXInfos(BSTAlignedArray<UIShaderFXInfo>& a_colorFXInfos, BSTAlignedArray<UIShaderFXInfo>& a_backgroundFXInfos) const; // 13

		void SetUpButtonBar(BSGFxShaderFXTarget& a_parentObject, const char* a_buttonBarPath, HUDColorTypes a_colorType);
		void SetupHUDShaderFXTargets(HUDColorTypes a_colorType, REX::Float32 a_scale = 1.0_f32);

		// members
		BSTArray<BSGFxShaderFXTarget*> shaderFXObjects;			 // 70
		msvc::unique_ptr<BSGFxShaderFXTarget> filterHolder;		 // 88
		msvc::unique_ptr<ButtonHintBar> buttonHintBar;			 // 90
		BSTAlignedArray<UIShaderFXInfo> cachedColorFXInfos;		 // 98
		BSTAlignedArray<UIShaderFXInfo> cachedBackgroundFXInfos; // B0
		mutable BSReadWriteLock cachedQuadsLock;				 // C8
		BSTOptional<HUDModeType> menuHUDMode{ std::nullopt };	 // D0
	};
	static_assert(sizeof(GameMenuBase) == 0xE0);
}
