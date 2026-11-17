#pragma once

#include "Scaleform/G/GFx_FileTypeConstants.hpp"
#include "Scaleform/G/GFx_MemoryParams.hpp"
#include "Scaleform/G/GFx_Resource.hpp"
#include "Scaleform/G/GFx_StateBag.hpp"
#include "Scaleform/R/Render_Rect.hpp"

namespace Scaleform
{
	class MemoryHeap;
}

namespace Scaleform::Render
{
	class ThreadCommandQueue;
}

namespace Scaleform::GFx
{
	class ActionControl;
	class ExporterInfo;
	class MemoryContext;
	class Movie;
	class ResourceId;

	class __declspec(novtable) MovieDef :
		public Resource, // 0x00
		public StateBag	 // 0x18
	{
	public:
		enum class FileAttrFlags : std::uint32_t
		{
			UseNetwork = 1 << 0,
			UseActionScript3 = 1 << 3,
			HasMetadata = 1 << 4
		};

		enum class VisitResourceMask : std::uint32_t
		{
			NestedMovies = 1 << 15,

			Fonts = 1 << 0,
			Bitmaps = 1 << 1,
			GradientImages = 1 << 2,
			EditTextFields = 1 << 3,
			Sounds = 1 << 4,
			Sprite = 1 << 5,

			AllLocalImages = (Bitmaps | GradientImages),
			AllImages = (Bitmaps | GradientImages | NestedMovies)
		};

		class __declspec(novtable) ImportVisitor
		{
		public:
			virtual ~ImportVisitor() = default; // 0x00

			// add
			virtual void Visit(
				MovieDef* a_parentDef,
				MovieDef* a_importDef,
				const char* a_importedMovieFilename) = 0; // 0x01
		};

		static_assert(sizeof(ImportVisitor) == 0x08);

		class __declspec(novtable) ResourceVisitor : public FileTypeConstants // 0x00
		{
		public:
			virtual ~ResourceVisitor() = default; // 0x00

			// add
			virtual void Visit(
				MovieDef* a_movieDef,
				Resource* a_resource,
				ResourceId a_rid,
				const char* a_exportName) = 0; // 0x01
		};

		static_assert(sizeof(ResourceVisitor) == 0x08);

		// add
		virtual auto GetVersion() const -> std::uint32_t = 0;										 // 0x04
		virtual auto GetLoadingFrame() const -> std::uint32_t = 0;									 // 0x05
		virtual auto GetWidth() const -> REX::Float32 = 0;											 // 0x06
		virtual auto GetHeight() const -> REX::Float32 = 0;											 // 0x07
		virtual auto GetFrameCount() const -> std::uint32_t = 0;									 // 0x08
		virtual auto GetFrameRate() const -> REX::Float32 = 0;										 // 0x09
		virtual auto GetFrameRect() const -> Render::RectF = 0;										 // 0x0A
		virtual auto GetSWFFlags() const -> std::uint32_t = 0;										 // 0x0B
		virtual auto GetFileURL() const -> const char* = 0;											 // 0x0C
		virtual void WaitForLoadFinish(bool a_cancel = false) const = 0;							 // 0x0D
		virtual void WaitForFrame(std::uint32_t a_frame) const = 0;									 // 0x0E
		virtual auto GetFileAttributes() const -> FileAttrFlags = 0;								 // 0x0F
		virtual auto GetMetadata(char* a_buff, std::uint32_t a_buffSize) const -> std::uint32_t = 0; // 0x10
		virtual auto GetLoadDataHeap() const -> MemoryHeap* = 0;									 // 0x11
		virtual auto GetBindDataHeap() const -> MemoryHeap* = 0;									 // 0x12
		virtual auto GetImageHeap() const -> MemoryHeap* = 0;										 // 0x13
		virtual auto GetMovieDataResource() const -> Resource* = 0;									 // 0x14
		virtual auto GetExporterInfo() const -> const ExporterInfo* = 0;							 // 0x15
		virtual auto CreateMemoryContext(
			const char* a_heapName,
			const MemoryParams& a_memParams,
			bool a_debugHeap) -> MemoryContext* = 0; // 0x16
		virtual auto CreateInstance(
			const MemoryParams& a_memParams,
			bool a_initFirstFrame,
			ActionControl* a_actionControl,
			Render::ThreadCommandQueue* a_queue = nullptr) -> Movie* = 0; // 0x18
		virtual auto CreateInstance(
			MemoryContext* a_memContext,
			bool a_initFirstFrame,
			ActionControl* a_actionControl,
			Render::ThreadCommandQueue* a_queue = nullptr) -> Movie* = 0; // 0x17
		virtual void VisitImportedMovies(ImportVisitor* a_visitor) = 0;	  // 0x19
		virtual void VisitResources(
			ResourceVisitor* a_visitor,
			VisitResourceMask a_visitMask = VisitResourceMask::AllImages) = 0;	   // 0x1A
		virtual auto GetResource(const char* a_exportName) const -> Resource* = 0; // 0x1B

		[[nodiscard]]
		auto CreateInstance(
			bool a_initFirstFrame = false,
			std::size_t a_memoryArena = 0,
			ActionControl* a_actionControl = nullptr,
			Render::ThreadCommandQueue* a_queue = nullptr) -> Movie*
		{
			auto memParams = MemoryParams();
			memParams.desc.arena = a_memoryArena;
			return CreateInstance(memParams, a_initFirstFrame, a_actionControl, a_queue);
		}
	};

	static_assert(sizeof(MovieDef) == 0x20);
}
