#pragma once

#include "RE/B/BSString.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "Scaleform/G/GFx_FunctionHandler.hpp"
#include "Scaleform/G/GFx_Movie.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace Scaleform::GFx
{
	class DrawTextManager;
	class FunctionHandler;
	class Loader;
	class Value;
}

namespace RE
{
	class BSScaleformImageLoader;
	class BSScaleformRenderer;
	class BSScaleformTranslator;
	class IMenu;
	class SFRendererInitializedEvent;

	class __declspec(novtable) BSScaleformManager :
		public BSTEventSink<SFRendererInitializedEvent>, // 0x00
		public BSTSingletonSDM<BSScaleformManager>		 // 0x08
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScaleformManager;
		inline static constexpr const auto& VTABLE = VTABLE::BSScaleformManager;

		inline static constexpr auto MOVIES_DIRECTORY_PATH = "Data/Interface"sv;
		inline static constexpr auto MOVIES_FILE_EXTENSION = ".swf"sv;

		using ScaleModeType = Scaleform::GFx::Movie::ScaleModeType;

		~BSScaleformManager() override; // 0x00

		// override (BSTEventSink<SFRendererInitializedEvent>)
		auto ProcessEvent(
			const SFRendererInitializedEvent& a_event,
			BSTEventSource<SFRendererInitializedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BSScaleformManager*;

		[[nodiscard]]
		auto IsNameValid(std::string_view a_name) const -> bool;

		[[nodiscard]]
		auto GetMovieFilename(const char* a_menuName, BSStaticString<REX::W32::MAX_PATH>& a_filePath) -> bool;
		void InitMovieViewport(
			Scaleform::GFx::Movie& a_movie,
			REX::Float32 a_dynamicWidthRatio,
			REX::Float32 a_dynamicHeightRatio);

		// The menu path has to be relative to "Data/Interface", without the ".swf" extension.
		auto LoadMovie(
			IMenu& a_menu,
			const char* a_menuPath,
			const char* a_menuObjPath = "",
			ScaleModeType a_scaleMode = ScaleModeType::ShowAll,
			REX::Float32 a_backgroundAlpha = static_cast<REX::Float32>(0.0)) -> bool;

		// The file path has to be relative to "Data/Interface", with the file extension.
		static auto LoadAsset(
			const IMenu& a_menu,
			const char* a_filePath,
			const char* a_rootVarPath,
			const Scaleform::Ptr<Scaleform::GFx::FunctionHandler>& a_onComplete = nullptr,
			const Scaleform::Ptr<Scaleform::GFx::FunctionHandler>& a_onError = nullptr) -> bool;

		static auto UnloadAsset(
			const IMenu& a_menu,
			const char* a_assetVarPath,
			const Scaleform::Ptr<Scaleform::GFx::FunctionHandler>& a_onUnload = nullptr) -> bool;

		static auto UnloadAsset(
			const IMenu& a_menu,
			const Scaleform::GFx::Value& a_assetValue,
			const Scaleform::Ptr<Scaleform::GFx::FunctionHandler>& a_onUnload = nullptr) -> bool;

		auto LoadMovieImpl(
			IMenu& a_menu,
			Scaleform::Ptr<Scaleform::GFx::Movie>& a_movie,
			const char* a_menuPath,
			const char* a_menuObjPath = "",
			ScaleModeType a_scaleMode = ScaleModeType::ShowAll,
			REX::Float32 a_backgroundAlpha = static_cast<REX::Float32>(0.0)) -> bool;

		[[nodiscard]]
		auto GetTranslator() const -> Scaleform::Ptr<BSScaleformTranslator>;

		// members
		Scaleform::GFx::Loader* loader;								 // 0x10
		BSScaleformRenderer* renderer;								 // 0x18
		Scaleform::Ptr<Scaleform::GFx::DrawTextManager> textManager; // 0x20
		Scaleform::Ptr<BSScaleformImageLoader> imageLoader;			 // 0x28
		BSString validNameChars;									 // 0x30
	};

	static_assert(sizeof(BSScaleformManager) == 0x40);
}
