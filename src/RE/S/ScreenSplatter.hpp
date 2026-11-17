#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiCamera;
	class NiNode;
	class NiTexture;
	class Setting;
}

namespace RE::ScreenSplatter
{
	auto ActivateCustom(
		const NiPointer<NiTexture>& a_colorTexture,
		const NiPointer<NiTexture>& a_alphaTexture,
		const NiPointer<NiTexture>& a_lensFlareTexture,
		std::uint16_t a_count,
		REX::Float32 a_duration,
		REX::Float32 a_alpha = static_cast<REX::Float32>(1.0)) -> bool;

	auto ActivateCustom(
		const char* a_colorTexturePath,
		const char* a_alphaTexturePath,
		const char* a_lensFlareTexturePath,
		std::uint16_t a_count,
		REX::Float32 a_duration,
		REX::Float32 a_alpha = static_cast<REX::Float32>(1.0)) -> bool;

	auto ActivateCustom(
		const BGSTextureSet& a_textureSet,
		std::uint16_t a_count,
		REX::Float32 a_duration,
		REX::Float32 a_alpha = static_cast<REX::Float32>(1.0)) -> bool;

	auto Activate() -> bool;

	[[nodiscard]]
	auto GetBloodSplatterDurationSetting() -> Setting&;
	[[nodiscard]]
	auto GetMaxBloodSplatterCountSetting() -> Setting&;

	[[nodiscard]]
	auto GetBloodSplatterColorFileNameSetting() -> Setting&;
	[[nodiscard]]
	auto GetBloodSplatterAlphaFileNameSetting() -> Setting&;
	[[nodiscard]]
	auto GetBloodSplatterLensFlareFileNameSetting() -> Setting&;

	[[nodiscard]]
	auto GetBloodSplatterDuration() -> REX::Float32;
	[[nodiscard]]
	auto GetMaxBloodSplatterCount() -> std::uint32_t;

	[[nodiscard]]
	auto GetBloodSplatterColorFileName() -> BSFixedString;
	[[nodiscard]]
	auto GetBloodSplatterAlphaFileName() -> BSFixedString;
	[[nodiscard]]
	auto GetBloodSplatterLensFlareFileName() -> BSFixedString;

	void SetBloodSplatterDuration(REX::Float32 a_value);
	void SetMaxBloodSplatterCount(std::uint32_t a_value);

	[[nodiscard]]
	auto GetCamera() noexcept -> NiPointer<NiCamera>&;
	[[nodiscard]]
	auto GetCount() noexcept -> std::uint32_t&;
	[[nodiscard]]
	auto GetIsEnabled() noexcept -> bool&;
	[[nodiscard]]
	auto GetRootNode() noexcept -> NiPointer<NiNode>&;
	[[nodiscard]]
	auto GetRootNodeName() -> const BSFixedString&;

	[[nodiscard]]
	auto CreateGeometry(std::uint16_t a_count) -> NiNode*;

	void Update();
	void Clear();
}
