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
	BSScaleformManager* BSScaleformManager::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<BSScaleformManager**>{ ID::BSScaleformManager::Singleton };
		return *SINGLETON;
	}

	bool BSScaleformManager::IsNameValid(const char* a_name) const
	{
		const auto nameView = std::string_view(a_name);
		return !nameView.empty() && nameView.find_first_not_of(validNameChars) == std::string_view::npos;
	}

	bool BSScaleformManager::GetMovieFilename(const char* a_menuName, BSStaticStringT<REX::W32::MAX_PATH>& a_filePath)
	{
		using FuncType = decltype(&BSScaleformManager::GetMovieFilename);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSScaleformManager::GetMovieFilename };
		return std::invoke(FUNC, this, a_menuName, a_filePath);
	}

	void BSScaleformManager::InitMovieViewport(::Scaleform::GFx::Movie& a_movie, REX::Float32 a_dynamicWidthRatio, REX::Float32 a_dynamicHeightRatio)
	{
		using FuncType = decltype(&BSScaleformManager::InitMovieViewport);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSScaleformManager::InitMovieViewport };
		FUNC(this, a_movie, a_dynamicWidthRatio, a_dynamicHeightRatio);
	}

	bool BSScaleformManager::LoadMovie(
		IMenu& a_menu,
		const char* a_menuPath,
		const char* a_menuObjPath,
		ScaleModeType a_scaleMode,
		REX::Float32 a_backgroundAlpha)
	{
		return LoadMovieImpl(a_menu, a_menu.uiMovie, a_menuPath, a_menuObjPath, a_scaleMode, a_backgroundAlpha);
	}

	bool BSScaleformManager::LoadAsset(
		const IMenu& a_menu,
		const char* a_filePath,
		const char* a_rootVarPath,
		::Scaleform::GFx::FunctionHandler* a_onComplete,
		::Scaleform::GFx::FunctionHandler* a_onError)
	{
		if (REX::IsNullOrEmpty(a_filePath) || REX::IsNullOrEmpty(a_rootVarPath)) {
			return false;
		}

		auto menuMovie = a_menu.uiMovie;
		if (!menuMovie) {
			return false;
		}

		auto menuRoot = menuMovie->asMovieRoot;
		if (!menuRoot) {
			return false;
		}

		auto gfxRootPath = ::Scaleform::GFx::Value();
		if (!menuRoot->GetVariable(std::addressof(gfxRootPath), a_rootVarPath) || !gfxRootPath.IsDisplayObject()) {
			return false;
		}

		auto gfxLoader = ::Scaleform::GFx::Value();
		menuRoot->CreateObject(std::addressof(gfxLoader), "flash.display.Loader");

		if (!gfxLoader.IsDisplayObject()) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		if (a_onComplete || a_onError) {
			auto gfxContentLoaderInfo = ::Scaleform::GFx::Value();
			if (!gfxLoader.GetMember("contentLoaderInfo", std::addressof(gfxContentLoaderInfo)) || !gfxContentLoaderInfo.IsObject()) [[unlikely]] {
				REX::Assert(false);
				return false;
			}

			if (a_onComplete) {
				auto gfxOnCompleteArgs = std::array<::Scaleform::GFx::Value, 2>();
				menuRoot->CreateString(std::addressof(gfxOnCompleteArgs[0]), "complete");
				menuRoot->CreateFunction(std::addressof(gfxOnCompleteArgs[1]), a_onComplete);

				if (!gfxContentLoaderInfo.Invoke("addEventListener", gfxOnCompleteArgs)) [[unlikely]] {
					REX::Assert(false);
					return false;
				}

				// Make it a weak reference.
				a_onComplete->Release();
			}

			if (a_onError) {
				auto gfxOnErrorArgs = std::array<::Scaleform::GFx::Value, 2>();
				menuRoot->CreateString(std::addressof(gfxOnErrorArgs[0]), "ioError");
				menuRoot->CreateFunction(std::addressof(gfxOnErrorArgs[1]), a_onError);

				if (!gfxContentLoaderInfo.Invoke("addEventListener", gfxOnErrorArgs)) [[unlikely]] {
					REX::Assert(false);
					return false;
				}

				auto gfxOnSecurityErrorArgs = std::array<::Scaleform::GFx::Value, 2>();
				menuRoot->CreateString(std::addressof(gfxOnSecurityErrorArgs[0]), "securityError");
				menuRoot->CreateFunction(std::addressof(gfxOnSecurityErrorArgs[1]), a_onError);

				if (!gfxContentLoaderInfo.Invoke("addEventListener", gfxOnSecurityErrorArgs)) [[unlikely]] {
					REX::Assert(false);
					return false;
				}

				// Make it a weak reference.
				a_onError->Release();
			}
		}

		auto gfxRootPathAddChildArgs = std::array<::Scaleform::GFx::Value, 1>();
		gfxRootPathAddChildArgs[0] = gfxLoader;

		if (!gfxRootPath.Invoke("addChild", gfxRootPathAddChildArgs)) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		auto gfxFilePath = ::Scaleform::GFx::Value();
		menuRoot->CreateString(std::addressof(gfxFilePath), a_filePath);

		auto gfxUrlRequestArgs = std::array<::Scaleform::GFx::Value, 1>();
		gfxUrlRequestArgs[0] = gfxFilePath;

		auto gfxUrlRequest = ::Scaleform::GFx::Value();
		menuRoot->CreateObject(std::addressof(gfxUrlRequest), "flash.net.URLRequest", gfxUrlRequestArgs);

		if (!gfxUrlRequest.IsObject()) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		auto gfxLoaderLoadArgs = std::array<::Scaleform::GFx::Value, 1>();
		gfxLoaderLoadArgs[0] = gfxUrlRequest;

		if (!gfxLoader.Invoke("load", gfxLoaderLoadArgs)) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		return true;
	}

	bool BSScaleformManager::UnloadAsset(
		const IMenu& a_menu,
		const char* a_assetVarPath,
		::Scaleform::GFx::FunctionHandler* a_onUnload)
	{
		if (REX::IsNullOrEmpty(a_assetVarPath)) {
			return false;
		}

		auto menuMovie = a_menu.uiMovie;
		if (!menuMovie) {
			return false;
		}

		auto menuRoot = menuMovie->asMovieRoot;
		if (!menuRoot) {
			return false;
		}

		auto gfxAsset = ::Scaleform::GFx::Value();
		if (!menuRoot->GetVariable(std::addressof(gfxAsset), a_assetVarPath) || !gfxAsset.IsDisplayObject()) {
			return false;
		}

		return UnloadAsset(a_menu, gfxAsset, a_onUnload);
	}

	bool BSScaleformManager::UnloadAsset(
		const IMenu& a_menu,
		const ::Scaleform::GFx::Value& a_assetValue,
		::Scaleform::GFx::FunctionHandler* a_onUnload)
	{
		if (!a_assetValue.IsDisplayObject()) {
			return false;
		}

		auto menuMovie = a_menu.uiMovie;
		if (!menuMovie) {
			return false;
		}

		auto menuRoot = menuMovie->asMovieRoot;
		if (!menuRoot) {
			return false;
		}

		auto gfxLoaderInfo = ::Scaleform::GFx::Value();
		if (!a_assetValue.GetMember("loaderInfo", std::addressof(gfxLoaderInfo)) || !gfxLoaderInfo.IsObject()) {
			return false;
		}

		auto gfxLoader = ::Scaleform::GFx::Value();
		if (!gfxLoaderInfo.GetMember("loader", std::addressof(gfxLoader)) || !gfxLoader.IsDisplayObject()) {
			return false;
		}

		if (a_onUnload) {
			auto gfxOnUnloadArgs = std::array<::Scaleform::GFx::Value, 2>();
			menuRoot->CreateString(std::addressof(gfxOnUnloadArgs[0]), "unload");
			menuRoot->CreateFunction(std::addressof(gfxOnUnloadArgs[1]), a_onUnload);

			if (!gfxLoader.Invoke("addEventListener", gfxOnUnloadArgs)) [[unlikely]] {
				REX::Assert(false);
				return false;
			}

			// Make it a weak reference.
			a_onUnload->Release();
		}

		if (!gfxLoader.Invoke("unload")) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		return true;
	}

	bool BSScaleformManager::LoadMovieImpl(
		IMenu& a_menu,
		::Scaleform::Ptr<::Scaleform::GFx::Movie>& a_movie,
		const char* a_menuPath,
		const char* a_menuObjPath,
		::Scaleform::GFx::Movie::ScaleModeType a_scaleMode,
		REX::Float32 a_backgroundAlpha)
	{
		// F4SE injects into this function
		using FuncType = decltype(&BSScaleformManager::LoadMovieImpl);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSScaleformManager::LoadMovieImpl };
		return std::invoke(FUNC, this, a_menu, a_movie, a_menuPath, a_menuObjPath, a_scaleMode, a_backgroundAlpha);
	}

	::Scaleform::Ptr<BSScaleformTranslator> BSScaleformManager::GetTranslator() const
	{
		if (!loader) {
			return nullptr;
		}

		auto* gfxTranslator = loader->GetStateAddRef<::Scaleform::GFx::Translator>();
		if (!gfxTranslator) {
			return nullptr;
		}

		auto* scaleformTranslator = RE::DynamicCast<RE::BSScaleformTranslator*>(gfxTranslator);
		if (!scaleformTranslator) {
			return nullptr;
		}

		return ::Scaleform::Ptr(scaleformTranslator);
	}
}
