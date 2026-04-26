#pragma once

#include "RE/B/BSStringT.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"

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

	class __declspec(novtable) BSScaleformManager
		: public BSTEventSink<SFRendererInitializedEvent>, // 00
		  public BSTSingletonSDM<BSScaleformManager>	   // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScaleformManager };
		inline static constexpr auto VTABLE{ VTABLE::BSScaleformManager };

		inline static constexpr auto MOVIES_DIRECTORY_PATH = "Data/Interface"sv;
		inline static constexpr auto MOVIES_FILE_EXTENSION = ".swf"sv;

		using ScaleModeType = ::Scaleform::GFx::Movie::ScaleModeType;

		~BSScaleformManager() override; // 00

		// override (BSTEventSink<SFRendererInitializedEvent>)
		BSEventNotifyControl ProcessEvent(const SFRendererInitializedEvent& a_event, BSTEventSource<SFRendererInitializedEvent>* a_eventSource) override; // 01

		[[nodiscard]] static BSScaleformManager* GetSingleton();

		[[nodiscard]] bool IsNameValid(const char* a_name) const;

		[[nodiscard]] bool GetMovieFilename(const char* a_menuName, BSStaticStringT<REX::W32::MAX_PATH>& a_filePath);
		void InitMovieViewport(::Scaleform::GFx::Movie& a_movie, REX::Float32 a_dynamicWidthRatio, REX::Float32 a_dynamicHeightRatio);

		// The menu path has to be relative to "Data/Interface", without the ".swf" extension.
		bool LoadMovie(
			IMenu& a_menu,
			const char* a_menuPath,
			const char* a_menuObjPath = "",
			ScaleModeType a_scaleMode = ScaleModeType::kShowAll,
			REX::Float32 a_backgroundAlpha = 0.0_f32);

		// The file path has to be relative to "Data/Interface", with the file extension.
		static bool LoadAsset(
			const IMenu& a_menu,
			const char* a_filePath,
			const char* a_rootVarPath,
			::Scaleform::GFx::FunctionHandler* a_onComplete = nullptr,
			::Scaleform::GFx::FunctionHandler* a_onError = nullptr);
		static bool UnloadAsset(
			const IMenu& a_menu,
			const char* a_assetVarPath,
			::Scaleform::GFx::FunctionHandler* a_onUnload = nullptr);
		static bool UnloadAsset(
			const IMenu& a_menu,
			const ::Scaleform::GFx::Value& a_assetValue,
			::Scaleform::GFx::FunctionHandler* a_onUnload = nullptr);

		bool LoadMovieImpl(
			IMenu& a_menu,
			::Scaleform::Ptr<::Scaleform::GFx::Movie>& a_movie,
			const char* a_menuPath,
			const char* a_menuObjPath = "",
			ScaleModeType a_scaleMode = ScaleModeType::kShowAll,
			REX::Float32 a_backgroundAlpha = 0.0_f32);

		[[nodiscard]] ::Scaleform::Ptr<BSScaleformTranslator> GetTranslator() const;

		// members
		::Scaleform::GFx::Loader* loader;								 // 10
		BSScaleformRenderer* renderer;									 // 18
		::Scaleform::Ptr<::Scaleform::GFx::DrawTextManager> textManager; // 20
		::Scaleform::Ptr<BSScaleformImageLoader> imageLoader;			 // 28
		BSString validNameChars;										 // 30
	};
	static_assert(sizeof(BSScaleformManager) == 0x40);
}
