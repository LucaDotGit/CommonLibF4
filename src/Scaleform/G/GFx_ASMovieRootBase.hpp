#pragma once

#include "Scaleform/A/Array.hpp"
#include "Scaleform/G/GFx_FocusMovedType.hpp"
#include "Scaleform/G/GFx_Movie.hpp"
#include "Scaleform/P/Ptr.hpp"
#include "Scaleform/R/RefCountBase.hpp"
#include "Scaleform/R/Render_Point.hpp"

namespace Scaleform
{
	class MemoryHeap;
	class String;
}

namespace Scaleform::Render::Text
{
	class Allocator;
}

namespace Scaleform::GFx
{
	class AccelerometerEvent;
	class AmpMovieObjectDesc;
	class AppLifecycleEvent;
	class ASString;
	class ASStringManager;
	class ASSupport;
	class DisplayObjContainer;
	class DisplayObject;
	class EventId;
	class FunctionHandler;
	class GeolocationEvent;
	class InputEventsQueueEntry;
	class InteractiveObject;
	class LoadQueueEntry;
	class LoadStates;
	class MemoryContext;
	class MouseState;
	class MovieDefImpl;
	class MovieDefRootNode;
	class MovieImpl;
	class OrientationEvent;
	class ProcessFocusKeyInfo;
	class Value;

	class __declspec(novtable) ASMovieRootBase : public RefCountBase<ASMovieRootBase, 327> // 0x00
	{
	public:
		~ASMovieRootBase() override; // 0x00

		// add
		virtual void SetMovie(MovieImpl* a_movie) // 0x01
		{
			movieImpl = a_movie;
		}

		virtual void AdvanceFrame(bool a_nextFrame) = 0;												   // 0x02
		virtual void ChangeMouseCursorType(std::uint32_t a_mouseIndex, std::uint32_t a_newCursorType) = 0; // 0x03
		virtual auto CheckAvm() -> bool = 0;															   // 0x04
		virtual void ClearDisplayList() = 0;															   // 0x05
		virtual auto CreateMovieDefRootNode(
			MemoryHeap* a_heap,
			MovieDefImpl* a_defImpl,
			bool a_importFlag) -> MovieDefRootNode* = 0;								 // 0x06
		virtual void DoActions() = 0;													 // 0x07
		virtual auto FindTarget(const ASString& a_path) const -> InteractiveObject* = 0; // 0x08
		virtual void ForceCollect() = 0;												 // 0x09
		virtual void ForceEmergencyCollect() = 0;										 // 0x0A
		virtual void SuspendGC(bool a_suspend) = 0;										 // 0x0B
		virtual void ScheduleGC() = 0;													 // 0x0C
		virtual void GenerateMouseEvents(std::uint32_t a_mouseIndex) = 0;				 // 0x0D
		virtual void GenerateTouchEvents(std::uint32_t a_mouseStateIndex);				 // 0x0E - { return; }
		virtual void GenerateGestureEvents(
			InteractiveObject* a_topmost,
			std::uint32_t a_phase,
			const Render::PointF& a_position,
			const Render::PointF& a_offset,
			const Render::PointF& a_scale,
			REX::Float32 a_rotation,
			std::uint32_t a_gestureMask); // 0x0F - { return; }
		virtual auto GetRootMovie(DisplayObject* a_dobj = nullptr) const -> DisplayObjContainer* = 0; // 0x10
		virtual auto Init(MovieDefImpl* a_movieDef) -> bool = 0;									  // 0x11
		virtual void NotifyMouseEvent(
			const InputEventsQueueEntry* a_qe,
			const MouseState& a_ms,
			std::int32_t a_mi) = 0;		   // 0x12
		virtual void NotifyOnResize() = 0; // 0x13
		virtual void NotifyQueueSetFocus(
			InteractiveObject* a_ch,
			std::uint32_t a_controllerIndex,
			FocusMovedType a_fmt) = 0; // 0x14
		virtual void NotifyTransferFocus(
			InteractiveObject* a_curFocused,
			InteractiveObject* a_newFocus,
			std::uint32_t a_controllerIndex) = 0; // 0x15
		virtual auto NotifyOnFocusChange(
			InteractiveObject* a_curFocused,
			InteractiveObject* a_toBeFocused,
			std::uint32_t a_controllerIndex,
			FocusMovedType a_fmt,
			ProcessFocusKeyInfo* a_focusKeyInfo = nullptr) -> bool = 0;						 // 0x16
		virtual void NotifyGamePadAnalogEvent(const EventId* a_id);							 // 0x17 - { return; }
		virtual void NotifyStatusEvent(const EventId* a_id);								 // 0x18 - { return; }
		virtual void NotifyAccelerometerEvent(const EventId* a_id, std::int32_t a_evtIDAcc); // 0x19 - { return; }
		virtual void NotifyGeolocationEvent(const EventId* a_id, std::int32_t a_evtIDGeo);	 // 0x1A - { return; }
		virtual void OnMovieFocus(bool a_set) = 0;											 // 0x1B
		virtual void OnNextFrame() = 0;														 // 0x1C
		virtual void OnDeviceOrientationChanged(const OrientationEvent& a_event);			 // 0x1D - { return; }
		virtual void OnAppLifecycleEvent(const AppLifecycleEvent& a_event);					 // 0x1E - { return; }
		virtual void OnAccelerometerEvent(const AccelerometerEvent& a_event);				 // 0x1F - { return; }
		virtual void OnGeolocationEvent(const GeolocationEvent& a_event);					 // 0x20 - { return; }
		virtual void PrintObjectsReport(
			std::uint32_t a_flags = 0,
			Log* a_log = nullptr,
			const char* a_swfName = nullptr); // 0x21 - { return; }
		virtual void GetObjectsTree(
			Array<Ptr<AmpMovieObjectDesc>>* a_rootObjects,
			MemoryHeap* a_heap);														   // 0x22 - { return; }
		virtual auto GetDisplayObjectsTree(MemoryHeap* a_heap) -> AmpMovieObjectDesc*;	   // 0x23 - { return nullptr; }
		virtual void ProcessLoadQueueEntry(LoadQueueEntry* a_entry, LoadStates* a_ls) = 0; // 0x24
		virtual void ProcessLoadVarsMT(
			LoadQueueEntry* a_entry,
			LoadStates* a_ls,
			const String& a_data,
			std::size_t a_fileLength,
			bool a_succeeded) = 0; // 0x25
		virtual void ProcessLoadBinaryMT(
			LoadQueueEntry* a_entry,
			LoadStates* a_ls,
			const ArrayPOD<std::byte>& a_data,
			std::size_t a_fileLength,
			bool a_succeeded);													 // 0x26 - { return; }
		virtual void RegisterAuxASClasses() = 0;								 // 0x27
		virtual void ResolveStickyVariables(InteractiveObject* a_character) = 0; // 0x28
		virtual void SetExternalInterfaceRetVal(const Value&) = 0;				 // 0x29
		virtual void SetMemoryParams(std::uint32_t a_frameBetweenCollections, std::uint32_t a_maxRootCount) = 0; // 0x2A
		virtual void Shutdown() = 0;																			 // 0x2B
		virtual void CreateString(Value* a_value, const char* a_string) = 0;									 // 0x2C
		virtual void CreateStringW(Value* a_value, const wchar_t* a_string) = 0;								 // 0x2D
		virtual void CreateObject(
			Value* a_value,
			const char* a_className = nullptr,
			const Value* a_args = nullptr,
			std::uint32_t a_numArgs = 0) = 0;																  // 0x2E
		virtual void CreateArray(Value* a_value) = 0;														  // 0x2F
		virtual void CreateFunction(Value* a_value, FunctionHandler* a_func, void* a_userData = nullptr) = 0; // 0x30
		virtual auto SetVariable(
			const char* a_pathToVar,
			const Value& a_value,
			Movie::SetVarType a_setType = Movie::SetVarType::Sticky) -> bool = 0;		   // 0x31
		virtual auto GetVariable(Value* a_val, const char* a_pathToVar) const -> bool = 0; // 0x32
		virtual auto SetVariableArray(
			Movie::SetArrayType a_type,
			const char* a_pathToVar,
			std::uint32_t a_index,
			const void* a_data,
			std::uint32_t a_count,
			Movie::SetVarType a_setType = Movie::SetVarType::Sticky) -> bool = 0; // 0x33
		virtual auto SetVariableArraySize(
			const char* a_pathToVar,
			std::uint32_t a_count,
			Movie::SetVarType a_setType = Movie::SetVarType::Sticky) -> bool = 0;		 // 0x35
		virtual auto GetVariableArraySize(const char* a_pathToVar) -> std::uint32_t = 0; // 0x34
		virtual auto GetVariableArray(
			Movie::SetArrayType a_type,
			const char* a_pathToVar,
			std::uint32_t a_index,
			void* a_data,
			std::uint32_t a_count) -> bool = 0;								 // 0x36
		virtual auto IsAvailable(const char* a_pathToVar) const -> bool = 0; // 0x37
		virtual auto Invoke(
			const char* a_pathToMethod,
			Value* a_result = nullptr,
			const Value* a_args = nullptr,
			std::uint32_t a_numArgs = 0) -> bool = 0;															 // 0x39
		virtual auto Invoke(const char* a_pathToMethod, Value* a_result, const char* a_argFmt, ...) -> bool = 0; // 0x38
		virtual auto InvokeArgs(
			const char* a_pathToMethod,
			Value* a_result,
			const char* a_argFmt,
			std::va_list a_args) -> bool = 0;								   // 0x3A
		virtual auto GetMemoryContext() const -> MemoryContext* = 0;		   // 0x3B
		virtual auto GetStringManager() const -> ASStringManager* = 0;		   // 0x3C
		virtual auto GetTextAllocator() -> Render::Text::Allocator* = 0;	   // 0x3D
		virtual void BroadcastGeolocationStatusEvent(const EventId* a_id) = 0; // 0x3E

		void CreateObject(Value* a_value, const char* a_className, std::span<const Value> a_args);
		void CreateArray(Value* a_value, std::uint32_t a_size);
		auto Invoke(const char* a_methodName, std::span<const Value> a_args) -> bool;
		auto Invoke(const char* a_methodName, Value* a_result, std::span<const Value> a_args) -> bool;

		// members
		MovieImpl* movieImpl;	  // 0x10
		Ptr<ASSupport> asSupport; // 0x18
		std::uint8_t avmVersion;  // 0x20
	};

	static_assert(sizeof(ASMovieRootBase) == 0x28);
}
