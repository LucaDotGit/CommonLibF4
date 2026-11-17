#pragma once

#include "RE/B/BSTOptional.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "msvc/memory.hpp"

namespace RE
{
	enum class DifficultyLevel : std::int32_t;

	class __declspec(novtable) StartMenuBase : public GameMenuBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::StartMenuBase;
		inline static constexpr const auto& VTABLE = VTABLE::StartMenuBase;

		~StartMenuBase() override; // 0x00

		// add
		virtual void DoLoadGame(std::int32_t a_saveIndex); // 0x14
		virtual void InitMainList();					   // 0x15
		virtual auto GetIsMenuReady() -> bool;			   // 0x16
		virtual void SaveSettings_Derived();			   // 0x17
		virtual void SetMenuColor();					   // 0x18

		[[nodiscard]]
		auto GetMenuDifficultyLevel() -> DifficultyLevel;

		// members
		msvc::unique_ptr<BSGFxShaderFXTarget> mainPanel;			// 0x0E0
		msvc::unique_ptr<BSGFxShaderFXTarget> versionText;			// 0x0E8
		msvc::unique_ptr<BSGFxShaderFXTarget> mainPanelBackground;	// 0x0F0
		msvc::unique_ptr<BSGFxShaderFXTarget> loadPanelBackground;	// 0x0F8
		msvc::unique_ptr<BSGFxShaderFXTarget> loadPanelBrackets;	// 0x100
		msvc::unique_ptr<BSGFxShaderFXTarget> loadPanelList;		// 0x108
		msvc::unique_ptr<BSGFxShaderFXTarget> loadPanelPlayerInfo;	// 0x110
		msvc::unique_ptr<BSGFxShaderFXTarget> confirmText;			// 0x118
		msvc::unique_ptr<BSGFxShaderFXTarget> levelText;			// 0x120
		msvc::unique_ptr<BSGFxShaderFXTarget> playtimeText;			// 0x128
		msvc::unique_ptr<BSGFxShaderFXTarget> locationText;			// 0x130
		msvc::unique_ptr<BSGFxShaderFXTarget> levelMeter;			// 0x138
		msvc::unique_ptr<BSGFxShaderFXTarget> modsLoadedText;		// 0x140
		msvc::unique_ptr<BSGFxShaderFXTarget> settingsCategoryList; // 0x148
		msvc::unique_ptr<BSGFxShaderFXTarget> settingsList;			// 0x150
		msvc::unique_ptr<BSGFxShaderFXTarget> dlcList;				// 0x158
		msvc::unique_ptr<BSGFxShaderFXTarget> loadingIcon;			// 0x160
		msvc::unique_ptr<BSGFxShaderFXTarget> colorReference;		// 0x168
		msvc::unique_ptr<BSGFxShaderFXTarget> splashScreenText;		// 0x170
		msvc::unique_ptr<BSGFxShaderFXTarget> controlsPanel;		// 0x178
		msvc::unique_ptr<BSGFxShaderFXTarget> helpPanelBackground;	// 0x180
		msvc::unique_ptr<BSGFxShaderFXTarget> helpListBackground;	// 0x188
		msvc::unique_ptr<BSGFxShaderFXTarget> gamerTagPanel;		// 0x190
		msvc::unique_ptr<BSGFxShaderFXTarget> gamerTagText;			// 0x198
		msvc::unique_ptr<BSGFxShaderFXTarget> gamerTagIcon;			// 0x1A0
		msvc::unique_ptr<BSGFxShaderFXTarget> bethesdaLogo;			// 0x1A8
		msvc::unique_ptr<BSGFxShaderFXTarget> characterSelectList;	// 0x1B0
		msvc::unique_ptr<BSGFxShaderFXTarget> remapPrompt;			// 0x1B8
		msvc::unique_ptr<BSGFxShaderFXTarget> settingGuideText;		// 0x1C0
		msvc::unique_ptr<BSGFxShaderFXTarget> blackBackground;		// 0x1C8
		msvc::unique_ptr<BSGFxShaderFXTarget> modManager;			// 0x1D0
		msvc::unique_ptr<BSGFxShaderFXTarget> dlcImageSizer;		// 0x1D8
		msvc::unique_ptr<BSGFxShaderFXTarget> dlcPanelBrackets;		// 0x1E0
		msvc::unique_ptr<BSGFxShaderFXTarget> loginObj;				// 0x1E8
		msvc::unique_ptr<BSGFxShaderFXTarget> motD;					// 0x1F0
		BSTOptional<DifficultyLevel> currentDisplayDifficultyLevel; // 0x1F8
		Scaleform::GFx::Value saveLoadPanelObj;						// 0x218
		bool gameDataReady;											// 0x220
		bool controlsChanged;										// 0x221
	};

	static_assert(sizeof(StartMenuBase) == 0x228);
}
