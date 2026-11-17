#include "RE/S/ScreenSplatter.hpp"

#include "RE/B/BGSTextureSet.hpp"
#include "RE/B/BSBloodSplatterShaderProperty.hpp"
#include "RE/B/BSShaderProperty.hpp"
#include "RE/B/BSSplatterData.hpp"
#include "RE/B/BSSplatterExtraData.hpp"
#include "RE/B/BSTriShape.hpp"
#include "RE/N/NiNode.hpp"
#include "RE/N/NiTexture.hpp"
#include "RE/N/NiUpdateData.hpp"
#include "RE/S/Setting.hpp"
#include "RE/S/SettingUtil.hpp"
#include "RE/T/TES.hpp"

namespace RE::ScreenSplatter
{
	auto ActivateCustom(
		const NiPointer<NiTexture>& a_colorTexture,
		const NiPointer<NiTexture>& a_alphaTexture,
		const NiPointer<NiTexture>& a_lensFlareTexture,
		std::uint16_t a_count,
		REX::Float32 a_duration,
		REX::Float32 a_alpha) -> bool
	{
		if (a_count == 0 ||
			a_duration <= static_cast<REX::Float32>(0.0) ||
			a_alpha <= static_cast<REX::Float32>(0.0) ||
			!GetIsEnabled()) {
			return false;
		}

		const auto rootNode = GetRootNode();
		if (!rootNode) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto splatterNode = NiPointer(CreateGeometry(a_count));
		if (!splatterNode) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		auto& splatterCount = GetCount();
		splatterCount += a_count;

		const auto splatterTriShape = dynamic_ni_pointer_cast<BSTriShape>(splatterNode->GetChildAt(0));
		if (!splatterTriShape) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto splatterBloodProperty = splatterTriShape->GetPropertyByType<BSBloodSplatterShaderProperty>();
		if (!splatterBloodProperty) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		if (a_colorTexture) {
			splatterBloodProperty->colorTexture = a_colorTexture;
		}

		if (a_alphaTexture) {
			splatterBloodProperty->alphaTexture = a_alphaTexture;
		}

		if (a_lensFlareTexture) {
			splatterBloodProperty->lensFlareTexture = a_lensFlareTexture;
		}

		const auto splatterData = BSSplatterData{
			.age = static_cast<REX::Float32>(0.0),
			.duration = a_duration,
			.alpha = a_alpha,
			.count = a_count
		};

		const auto splatterExtraData = make_ni_shared<BSSplatterExtraData>(splatterData);
		if (!splatterExtraData) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		splatterNode->AddExtraData(splatterExtraData);
		splatterNode->SetName(GetRootNodeName());

		constexpr auto FIRST_AVAILABLE = true;
		rootNode->AttachChild(splatterNode.get(), FIRST_AVAILABLE);

		BSBloodSplatterShaderProperty::SetFadeSourceRecurse(
			splatterNode.get(),
			std::addressof(splatterExtraData->splatterData.alpha));

		auto updateData = NiUpdateData();
		rootNode->Update(updateData);

		return true;
	}

	auto ActivateCustom(
		const char* a_colorTexturePath,
		const char* a_alphaTexturePath,
		const char* a_lensFlareTexturePath,
		std::uint16_t a_count,
		REX::Float32 a_duration,
		REX::Float32 a_alpha) -> bool
	{
		if (a_count == 0 ||
			a_duration <= static_cast<REX::Float32>(0.0) ||
			a_alpha <= static_cast<REX::Float32>(0.0) ||
			!GetIsEnabled()) {
			return false;
		}

		const auto* tes = TES::GetSingleton();
		if (!tes) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		auto colorTexture = NiPointer<NiTexture>();
		tes->CreateTextureImage(a_colorTexturePath, colorTexture);

		auto alphaTexture = NiPointer<NiTexture>();
		tes->CreateTextureImage(a_alphaTexturePath, alphaTexture);

		auto lensFlareTexture = NiPointer<NiTexture>();
		tes->CreateTextureImage(a_lensFlareTexturePath, lensFlareTexture);

		return ActivateCustom(colorTexture, alphaTexture, lensFlareTexture, a_count, a_duration, a_alpha);
	}

	auto ActivateCustom(
		const BGSTextureSet& a_textureSet,
		std::uint16_t a_count,
		REX::Float32 a_duration,
		REX::Float32 a_alpha) -> bool
	{
		if (a_count == 0 ||
			a_duration <= static_cast<REX::Float32>(0.0) ||
			a_alpha <= static_cast<REX::Float32>(0.0) ||
			!GetIsEnabled()) {
			return false;
		}

		const auto getTextureName = [](const BGSTextureSet& a_textureSet,
									   BSShaderProperty::TextureType a_textureType) noexcept -> BSFixedString {
			const auto& textures = a_textureSet.textures;
			REX::Assert(std::cmp_less(std::to_underlying(a_textureType), textures.size()));

			const auto& texture = textures[REX::ToUnsigned(std::to_underlying(a_textureType))];
			return texture.textureName;
		};

		const auto colorTextureName = getTextureName(a_textureSet, BSShaderProperty::TextureType::Diffuse);
		const auto alphaTextureName = getTextureName(a_textureSet, BSShaderProperty::TextureType::Height);
		const auto lensFlareTextureName = getTextureName(a_textureSet, BSShaderProperty::TextureType::Glow);

		return ActivateCustom(
			colorTextureName.data(),
			alphaTextureName.data(),
			lensFlareTextureName.data(),
			a_count,
			a_duration,
			a_alpha);
	}

	auto Activate() -> bool
	{
		constexpr auto COLOR_TEXTURE = NiPointer<NiTexture>();
		constexpr auto ALPHA_TEXTURE = NiPointer<NiTexture>();
		constexpr auto LENS_FLARE_TEXTURE = NiPointer<NiTexture>();

		const auto effectCount = static_cast<std::uint16_t>(GetMaxBloodSplatterCount());
		const auto effectDuration = GetBloodSplatterDuration();

		constexpr auto EFFECT_ALPHA = static_cast<REX::Float32>(1.0);

		return ActivateCustom(
			COLOR_TEXTURE,
			ALPHA_TEXTURE,
			LENS_FLARE_TEXTURE,
			effectCount,
			effectDuration,
			EFFECT_ALPHA);
	}

	auto GetBloodSplatterDurationSetting() -> Setting&
	{
		static auto* BloodSplatterDuration = GetGameSetting("fBloodSplatterDuration"sv);
		REX::Assert(BloodSplatterDuration != nullptr);
		return *BloodSplatterDuration;
	}

	auto GetMaxBloodSplatterCountSetting() -> Setting&
	{
		static auto* MaxBloodSplatterCount = GetGameSetting("iBloodSplatterMaxCount"sv);
		REX::Assert(MaxBloodSplatterCount != nullptr);
		return *MaxBloodSplatterCount;
	}

	auto GetBloodSplatterColorFileNameSetting() -> Setting&
	{
		static auto* BloodSplatterColorFileName = GetGameSetting("sBloodSplatterColor01OPTFilename"sv);
		REX::Assert(BloodSplatterColorFileName != nullptr);
		return *BloodSplatterColorFileName;
	}

	auto GetBloodSplatterAlphaFileNameSetting() -> Setting&
	{
		static auto* BloodSplatterAlphaFileName = GetGameSetting("sBloodSplatterAlpha01OPTFilename"sv);
		REX::Assert(BloodSplatterAlphaFileName != nullptr);
		return *BloodSplatterAlphaFileName;
	}

	auto GetBloodSplatterLensFlareFileNameSetting() -> Setting&
	{
		static auto* BloodSplatterLensFlareFileName = GetGameSetting("sBloodSplatterFlare01Filename"sv);
		REX::Assert(BloodSplatterLensFlareFileName != nullptr);
		return *BloodSplatterLensFlareFileName;
	}

	auto GetBloodSplatterDuration() -> REX::Float32
	{
		const auto& setting = GetBloodSplatterDurationSetting();
		if (!setting.IsFloat()) [[unlikely]] {
			REX::Assert(false);
			return static_cast<REX::Float32>(0.0);
		}

		return setting.GetFloat();
	}

	auto GetMaxBloodSplatterCount() -> std::uint32_t
	{
		const auto& setting = GetMaxBloodSplatterCountSetting();
		if (!setting.IsInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return static_cast<std::uint32_t>(setting.GetInt());
	}

	auto GetBloodSplatterColorFileName() -> BSFixedString
	{
		const auto& setting = GetBloodSplatterColorFileNameSetting();
		if (!setting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return {};
		}

		return {setting.GetString()};
	}

	auto GetBloodSplatterAlphaFileName() -> BSFixedString
	{
		const auto& setting = GetBloodSplatterAlphaFileNameSetting();
		if (!setting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return {};
		}

		return {setting.GetString()};
	}

	auto GetBloodSplatterLensFlareFileName() -> BSFixedString
	{
		const auto& setting = GetBloodSplatterLensFlareFileNameSetting();
		if (!setting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return {};
		}

		return {setting.GetString()};
	}

	void SetBloodSplatterDuration(REX::Float32 a_value)
	{
		auto& setting = GetBloodSplatterDurationSetting();
		if (!setting.IsFloat()) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		setting.SetFloat(a_value);
	}

	void SetMaxBloodSplatterCount(std::uint32_t a_value)
	{
		auto& setting = GetMaxBloodSplatterCountSetting();
		if (!setting.IsInt()) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		setting.SetInt(static_cast<std::int32_t>(a_value));
	}

	auto GetCamera() noexcept -> NiPointer<NiCamera>&
	{
		static const auto CAMERA = REL::Relocation<NiPointer<NiCamera>*>(ID::ScreenSplatter::Camera);
		return *CAMERA;
	}

	auto GetCount() noexcept -> std::uint32_t&
	{
		static const auto COUNT = REL::Relocation<std::uint32_t*>(ID::ScreenSplatter::Count);
		return *COUNT;
	}

	auto GetIsEnabled() noexcept -> bool&
	{
		static const auto ENABLED = REL::Relocation<bool*>(ID::ScreenSplatter::IsEnabled);
		return *ENABLED;
	}

	auto GetRootNode() noexcept -> NiPointer<NiNode>&
	{
		static const auto ROOT_NODE = REL::Relocation<NiPointer<NiNode>*>(ID::ScreenSplatter::RootNode);
		return *ROOT_NODE;
	}

	auto GetRootNodeName() -> const BSFixedString&
	{
		static const auto ROOT_NODE_NAME = BSFixedString("ScreenSplatterRoot"sv);
		return ROOT_NODE_NAME;
	}

	auto CreateGeometry(std::uint16_t a_count) -> NiNode*
	{
		using FuncType = decltype(&ScreenSplatter::CreateGeometry);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ScreenSplatter::CreateGeometry);
		return std::invoke(FUNC, a_count);
	}

	void Update()
	{
		using FuncType = decltype(&ScreenSplatter::Update);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ScreenSplatter::Update);
		std::invoke(FUNC);
	}

	void Clear()
	{
		using FuncType = decltype(&ScreenSplatter::Clear);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ScreenSplatter::Clear);
		std::invoke(FUNC);
	}
}
