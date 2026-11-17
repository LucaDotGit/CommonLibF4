#include "RE/B/BSScaleformManager.hpp"

#include "RE/B/BSScaleformTranslator.hpp"
#include "RE/I/IMenu.hpp"
#include "Scaleform/G/GFx_ASMovieRootBase.hpp"
#include "Scaleform/G/GFx_FunctionHandler.hpp"
#include "Scaleform/G/GFx_Loader.hpp"
#include "Scaleform/G/GFx_Movie.hpp"
#include "Scaleform/G/GFx_Translator.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace RE
{
	auto BSScaleformManager::GetSingleton() noexcept -> BSScaleformManager*
	{
		static const auto SINGLETON = REL::Relocation<BSScaleformManager**>(ID::BSScaleformManager::Singleton);
		return *SINGLETON;
	}

	auto BSScaleformManager::IsNameValid(std::string_view a_name) const -> bool
	{
		return !a_name.empty() && a_name.find_first_of(validNameChars) == std::string_view::npos;
	}

	auto BSScaleformManager::GetMovieFilename(const char* a_menuName, BSStaticString<REX::W32::MAX_PATH>& a_filePath)
		-> bool
	{
		using FuncType = decltype(&BSScaleformManager::GetMovieFilename);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSScaleformManager::GetMovieFilename);
		return std::invoke(FUNC, this, a_menuName, a_filePath);
	}

	void BSScaleformManager::InitMovieViewport(
		Scaleform::GFx::Movie& a_movie,
		REX::Float32 a_dynamicWidthRatio,
		REX::Float32 a_dynamicHeightRatio)
	{
		using FuncType = decltype(&BSScaleformManager::InitMovieViewport);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSScaleformManager::InitMovieViewport);
		std::invoke(FUNC, this, a_movie, a_dynamicWidthRatio, a_dynamicHeightRatio);
	}

	auto BSScaleformManager::LoadMovie(
		IMenu& a_menu,
		const char* a_menuPath,
		const char* a_menuObjPath,
		ScaleModeType a_scaleMode,
		REX::Float32 a_backgroundAlpha) -> bool
	{
		return LoadMovieImpl(a_menu, a_menu.uiMovie, a_menuPath, a_menuObjPath, a_scaleMode, a_backgroundAlpha);
	}

	auto BSScaleformManager::LoadAsset(
		const IMenu& a_menu,
		const char* a_filePath,
		const char* a_rootVarPath,
		const Scaleform::Ptr<Scaleform::GFx::FunctionHandler>& a_onComplete,
		const Scaleform::Ptr<Scaleform::GFx::FunctionHandler>& a_onError) -> bool
	{
		if (REX::IsNullOrEmpty(a_filePath) || REX::IsNullOrEmpty(a_rootVarPath)) {
			return false;
		}

		const auto menuMovie = a_menu.uiMovie;
		if (!menuMovie) {
			return false;
		}

		const auto menuRoot = menuMovie->asMovieRoot;
		if (!menuRoot) {
			return false;
		}

		auto gfxRootPath = Scaleform::GFx::Value();
		if (!menuRoot->GetVariable(std::addressof(gfxRootPath), a_rootVarPath) || !gfxRootPath.IsDisplayObject()) {
			return false;
		}

		auto gfxLoader = Scaleform::GFx::Value();
		menuRoot->CreateObject(std::addressof(gfxLoader), "flash.display.Loader");

		if (!gfxLoader.IsDisplayObject()) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		if (a_onComplete || a_onError) {
			auto gfxContentLoaderInfo = Scaleform::GFx::Value();
			if (!gfxLoader.GetMember("contentLoaderInfo", std::addressof(gfxContentLoaderInfo)) ||
				!gfxContentLoaderInfo.IsObject()) [[unlikely]] {
				REX::Assert(false);
				return false;
			}

			if (a_onComplete) {
				auto gfxOnCompleteArgs = std::array<Scaleform::GFx::Value, 2>();
				menuRoot->CreateString(std::addressof(gfxOnCompleteArgs[0]), "complete");
				menuRoot->CreateFunction(std::addressof(gfxOnCompleteArgs[1]), a_onComplete.get());

				if (!gfxContentLoaderInfo.Invoke("addEventListener", gfxOnCompleteArgs)) [[unlikely]] {
					REX::Assert(false);
					return false;
				}
			}

			if (a_onError) {
				auto gfxOnErrorArgs = std::array<Scaleform::GFx::Value, 2>();
				menuRoot->CreateString(std::addressof(gfxOnErrorArgs[0]), "ioError");
				menuRoot->CreateFunction(std::addressof(gfxOnErrorArgs[1]), a_onError.get());

				if (!gfxContentLoaderInfo.Invoke("addEventListener", gfxOnErrorArgs)) [[unlikely]] {
					REX::Assert(false);
					return false;
				}

				auto gfxOnSecurityErrorArgs = std::array<Scaleform::GFx::Value, 2>();
				menuRoot->CreateString(std::addressof(gfxOnSecurityErrorArgs[0]), "securityError");
				menuRoot->CreateFunction(std::addressof(gfxOnSecurityErrorArgs[1]), a_onError.get());

				if (!gfxContentLoaderInfo.Invoke("addEventListener", gfxOnSecurityErrorArgs)) [[unlikely]] {
					REX::Assert(false);
					return false;
				}
			}
		}

		const auto gfxRootPathAddChildArgs = std::array{gfxLoader};

		if (!gfxRootPath.Invoke("addChild", gfxRootPathAddChildArgs)) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		auto gfxFilePath = Scaleform::GFx::Value();
		menuRoot->CreateString(std::addressof(gfxFilePath), a_filePath);

		const auto gfxUrlRequestArgs = std::array{gfxFilePath};

		auto gfxUrlRequest = Scaleform::GFx::Value();
		menuRoot->CreateObject(std::addressof(gfxUrlRequest), "flash.net.URLRequest", gfxUrlRequestArgs);

		if (!gfxUrlRequest.IsObject()) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto gfxLoaderLoadArgs = std::array{gfxUrlRequest};

		if (!gfxLoader.Invoke("load", gfxLoaderLoadArgs)) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		return true;
	}

	auto BSScaleformManager::UnloadAsset(
		const IMenu& a_menu,
		const char* a_assetVarPath,
		const Scaleform::Ptr<Scaleform::GFx::FunctionHandler>& a_onUnload) -> bool
	{
		if (REX::IsNullOrEmpty(a_assetVarPath)) {
			return false;
		}

		const auto menuMovie = a_menu.uiMovie;
		if (!menuMovie) {
			return false;
		}

		const auto menuRoot = menuMovie->asMovieRoot;
		if (!menuRoot) {
			return false;
		}

		auto gfxAsset = Scaleform::GFx::Value();
		if (!menuRoot->GetVariable(std::addressof(gfxAsset), a_assetVarPath) || !gfxAsset.IsDisplayObject()) {
			return false;
		}

		return UnloadAsset(a_menu, gfxAsset, a_onUnload);
	}

	auto BSScaleformManager::UnloadAsset(
		const IMenu& a_menu,
		const Scaleform::GFx::Value& a_assetValue,
		const Scaleform::Ptr<Scaleform::GFx::FunctionHandler>& a_onUnload) -> bool
	{
		if (!a_assetValue.IsDisplayObject()) {
			return false;
		}

		const auto menuMovie = a_menu.uiMovie;
		if (!menuMovie) {
			return false;
		}

		const auto menuRoot = menuMovie->asMovieRoot;
		if (!menuRoot) {
			return false;
		}

		auto gfxLoaderInfo = Scaleform::GFx::Value();
		if (!a_assetValue.GetMember("loaderInfo", std::addressof(gfxLoaderInfo)) || !gfxLoaderInfo.IsObject()) {
			return false;
		}

		auto gfxLoader = Scaleform::GFx::Value();
		if (!gfxLoaderInfo.GetMember("loader", std::addressof(gfxLoader)) || !gfxLoader.IsDisplayObject()) {
			return false;
		}

		if (a_onUnload) {
			auto gfxOnUnloadArgs = std::array<Scaleform::GFx::Value, 2>();
			menuRoot->CreateString(std::addressof(gfxOnUnloadArgs[0]), "unload");
			menuRoot->CreateFunction(std::addressof(gfxOnUnloadArgs[1]), a_onUnload.get());

			if (!gfxLoader.Invoke("addEventListener", gfxOnUnloadArgs)) [[unlikely]] {
				REX::Assert(false);
				return false;
			}
		}

		if (!gfxLoader.Invoke("unload")) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		return true;
	}

	auto BSScaleformManager::LoadMovieImpl(
		IMenu& a_menu,
		Scaleform::Ptr<Scaleform::GFx::Movie>& a_movie,
		const char* a_menuPath,
		const char* a_menuObjPath,
		Scaleform::GFx::Movie::ScaleModeType a_scaleMode,
		REX::Float32 a_backgroundAlpha) -> bool
	{
		// F4SE injects into this function.
		using FuncType = decltype(&BSScaleformManager::LoadMovieImpl);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSScaleformManager::LoadMovieImpl);
		return std::invoke(FUNC, this, a_menu, a_movie, a_menuPath, a_menuObjPath, a_scaleMode, a_backgroundAlpha);
	}

	auto BSScaleformManager::GetTranslator() const -> Scaleform::Ptr<BSScaleformTranslator>
	{
		if (!loader) {
			return nullptr;
		}

		const auto gfxTranslator = loader->GetStateAddRef<Scaleform::GFx::Translator>();
		if (!gfxTranslator) {
			return nullptr;
		}

		return Scaleform::dynamic_pointer_cast<BSScaleformTranslator>(gfxTranslator);
	}
}
