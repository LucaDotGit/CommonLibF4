#pragma once

#include "Scaleform/G/GFx_StateBag.hpp"
#include "Scaleform/P/Ptr.hpp"
#include "Scaleform/R/RefCountBase.hpp"
#include "Scaleform/R/Render_Color.hpp"
#include "Scaleform/R/Render_ContextImpl_DisplayHandle.hpp"
#include "Scaleform/R/Render_Matrix2x4.hpp"
#include "Scaleform/R/Render_Matrix3x4.hpp"
#include "Scaleform/R/Render_Matrix4x4.hpp"
#include "Scaleform/R/Render_Point.hpp"
#include "Scaleform/R/Render_Rect.hpp"
#include "Scaleform/R/Render_TreeRoot.hpp"
#include "Scaleform/T/ThreadId.hpp"

namespace Scaleform
{
	class MemoryHeap;
	class StatBag;
}

namespace Scaleform::Render
{
	enum class EdgeAAMode : std::uint32_t;
}

namespace Scaleform::GFx
{
	enum class PlayState : std::int32_t;

	class ASMovieRootBase;
	class Event;
	class FunctionHandler;
	class Log;
	class MovieDef;
	class Value;
	class Viewport;

	class __declspec(novtable) Movie :
		public RefCountBase<Movie, 327>, // 0x00
		public StateBag					 // 0x10
	{
	public:
		enum class SetVarType : std::int32_t
		{
			Normal = 0,
			Sticky = 1,
			Permanent = 2
		};

		enum class SetArrayType : std::int32_t
		{
			Int = 0,
			Double = 1,
			Float = 2,
			String = 3,
			StringW = 4,
			Value = 5
		};

		enum class ScaleModeType : std::int32_t
		{
			NoScale = 0,
			ShowAll = 1,
			ExactFit = 2,
			NoBorder = 3
		};

		enum class AlignType : std::int32_t
		{
			Center = 0,
			TopCenter = 1,
			BottomCenter = 2,
			CenterLeft = 3,
			CenterRight = 4,
			TopLeft = 5,
			TopRight = 6,
			BottomLeft = 7,
			BottomRight = 8
		};

		enum HE_ReturnValueType : std::int32_t
		{
			HE_NotHandled = 0,
			HE_Handled = 1,
			HE_NoDefaultAction = 2,
			HE_Completed = (HE_Handled | HE_NoDefaultAction)
		};

		enum class HitTestType : std::int32_t
		{
			Bounds = 0,
			Shapes = 1,
			ButtonEvents = 2,
			ShapesNoInvisible = 3
		};

		enum class ReportFlags : std::uint32_t
		{
			None = 0,
			ShortFileNames = 1 << 0,
			NoCircularReferences = 1 << 1,
			SuppressOverallStats = 1 << 2,
			AddressesForAnonymObjsOnly = 1 << 3,
			SuppressMovieDefsStats = 1 << 4,
			NoEllipsis = 1 << 5
		};

		enum class MakeAllVisibleFlags : std::uint32_t
		{
			None = 0,
			DoNotScaleDown = 1 << 0,
			ScaleUp50 = 1 << 1,
			LeftTopToZero = 1 << 2
		};

		~Movie() override; // 0x00

		// add
		virtual auto GetMovieDef() const -> MovieDef* = 0;										   // 0x01
		virtual auto GetCurrentFrame() const -> std::uint32_t = 0;								   // 0x02
		virtual auto HasLooped() const -> bool = 0;												   // 0x03
		virtual void GotoFrame(std::uint32_t a_frameNumber) = 0;								   // 0x04
		virtual auto GotoLabeledFrame(const char* a_label, std::int32_t a_offset = 0) -> bool = 0; // 0x05
		virtual void SetPlayState(PlayState a_state) = 0;										   // 0x06
		virtual auto GetPlayState() const -> PlayState = 0;										   // 0x07
		virtual auto IsValid() -> bool = 0;														   // 0x08
		virtual void SetVisible(bool a_visible) = 0;											   // 0x09
		virtual auto GetVisible() const -> bool = 0;											   // 0x0A
		virtual auto GetASTimerMs() const -> std::uint64_t = 0;									   // 0x0B
		virtual void SetViewport(const Viewport& a_viewDesc) = 0;								   // 0x0C
		virtual void GetViewport(Viewport* a_viewDesc) const = 0;								   // 0x0D
		virtual void SetViewScaleMode(ScaleModeType) = 0;										   // 0x0E
		virtual auto GetViewScaleMode() const -> ScaleModeType = 0;								   // 0x0F
		virtual void SetViewAlignment(AlignType) = 0;											   // 0x10
		virtual auto GetViewAlignment() const -> AlignType = 0;									   // 0x11
		virtual auto GetVisibleFrameRect() const -> Render::RectF = 0;							   // 0x12
		virtual auto GetSafeRect() const -> Render::RectF = 0;									   // 0x13
		virtual void SetSafeRect(const Render::RectF& a_rect) = 0;								   // 0x14
		virtual void SetEdgeAAMode(Render::EdgeAAMode a_edgeAA) = 0;							   // 0x15
		virtual auto GetEdgeAAMode() const -> Render::EdgeAAMode = 0;							   // 0x16
		virtual void Restart(bool a_advance0 = true) = 0;										   // 0x17
		virtual auto Advance(
			REX::Float32 a_deltaTime,
			std::uint32_t a_frameCatchUpCount = 2,
			bool a_capture = true) -> REX::Float32 = 0;		  // 0x18
		virtual void Capture(bool a_onChangeOnly = true) = 0; // 0x19
		virtual auto GetDisplayHandle() const
			-> const Render::ContextImpl::DisplayHandle<Render::TreeRoot>& = 0; // 0x1A
		virtual void SetCaptureThread(ThreadId a_captureThreadId) = 0;			// 0x1B
		virtual void ShutdownRendering(bool a_wait) = 0;						// 0x1C
		virtual auto IsShutdownRenderingComplete() const -> bool = 0;			// 0x1D
		virtual void SetPause(bool a_pause) = 0;								// 0x1E
		virtual auto IsPaused() const -> bool = 0;								// 0x1F
		virtual void SetBackgroundColor(Render::Color a_bgColor) = 0;			// 0x20
		virtual void SetBackgroundAlpha(REX::Float32 a_alpha) = 0;				// 0x21
		virtual auto GetBackgroundAlpha() const -> REX::Float32 = 0;			// 0x22
		virtual auto HandleEvent(const Event& a_event) -> std::uint32_t = 0;	// 0x23
		virtual void GetMouseState(
			std::uint32_t a_mouseIndex,
			REX::Float32* a_x,
			REX::Float32* a_y,
			std::uint32_t* a_buttons) = 0; // 0x24
		virtual void NotifyMouseState(
			REX::Float32 a_x,
			REX::Float32 a_y,
			std::uint32_t a_buttons,
			std::uint32_t a_mouseIndex = 0) = 0; // 0x25
		virtual auto HitTest(
			REX::Float32 a_x,
			REX::Float32 a_y,
			HitTestType a_testCond = HitTestType::Shapes,
			std::uint32_t a_controllerIndex = 0) -> bool = 0;			// 0x26
		virtual auto GetUserData() const -> void* = 0;					// 0x27
		virtual void SetUserData(void*) = 0;							// 0x28
		virtual auto IsMovieFocused() const -> bool = 0;				// 0x29
		virtual auto GetDirtyFlag(bool a_doReset = true) -> bool = 0;	// 0x2A
		virtual void SetMouseCursorCount(std::uint32_t a_count) = 0;	// 0x2B
		virtual auto GetMouseCursorCount() const -> std::uint32_t = 0;	// 0x2C
		virtual void SetControllerCount(std::uint32_t a_count) = 0;		// 0x2D
		virtual auto GetControllerCount() const -> std::uint32_t = 0;	// 0x2E
		virtual void GetStats(StatBag* a_bag, bool a_reset = true) = 0; // 0x2F
		virtual auto GetHeap() const -> MemoryHeap* = 0;				// 0x30
		virtual void ForceCollectGarbage() = 0;							// 0x31
		virtual void SuspendGC(bool a_suspend) = 0;						// 0x32
		virtual void ScheduleGC() = 0;									// 0x33
		virtual void PrintObjectsReport(
			ReportFlags a_flags = ReportFlags::None,
			Log* a_log = nullptr,
			const char* a_swfName = nullptr) = 0; // 0x34
		virtual auto TranslateToScreen(
			const Render::PointF& a_pt,
			Render::Matrix2x4F* a_userMatrix = nullptr) -> Render::PointF = 0; // 0x36
		virtual auto TranslateToScreen(
			const Render::RectF& a_pt,
			Render::Matrix2x4F* a_userMatrix = nullptr) -> Render::RectF = 0; // 0x35
		virtual auto TranslateLocalToScreen(
			const char* a_pathToCharacter,
			const Render::PointF& a_pt,
			Render::PointF* a_presPt,
			Render::Matrix2x4F* a_userMatrix = nullptr) -> bool = 0; // 0x37
		virtual auto SetControllerFocusGroup(
			std::uint32_t a_controllerIndex,
			std::uint32_t a_focusGroupIndex) -> bool = 0;												  // 0x38
		virtual auto GetControllerFocusGroup(std::uint32_t a_controllerIndex) const -> std::uint32_t = 0; // 0x39
		virtual void ResetInputFocus(std::uint32_t a_controllerIndex) = 0;								  // 0x3A
		virtual auto IsExitRequested() const -> bool = 0;												  // 0x3B
		virtual void GetViewMatrix3D(Render::Matrix3x4<REX::Float32>* a_matrix) = 0;					  // 0x3C
		virtual void SetViewMatrix3D(const Render::Matrix3x4<REX::Float32>& a_matrix) = 0;				  // 0x3D
		virtual void GetProjectionMatrix3D(Render::Matrix4x4F* a_matrix) = 0;							  // 0x3E
		virtual void SetProjectionMatrix3D(const Render::Matrix4x4F& a_matrix) = 0;						  // 0x3F
		virtual void SetStageAutoOrients(bool a_value = true) = 0;										  // 0x40
		virtual void ForceUpdateImages() = 0;															  // 0x41
		virtual void MakeAreaVisible(
			const Render::RectF& a_screenRect,
			const Render::RectF& a_box,
			MakeAllVisibleFlags a_flags = MakeAllVisibleFlags::None) = 0; // 0x42
		virtual void RestoreViewport() = 0;								  // 0x43

		[[nodiscard]]
		auto IsAvailable(const char* a_pathToVar) const -> bool;
		auto CreateString(Value* a_value, const char* a_string) const -> bool;
		auto CreateStringW(Value* a_value, const wchar_t* a_string) const -> bool;
		auto CreateObject(
			Value* a_value,
			const char* a_className = nullptr,
			const Value* a_args = nullptr,
			std::uint32_t a_numArgs = 0) const -> bool;
		auto CreateObject(Value* a_value, const char* a_className, std::span<const Value> a_args) const -> bool;
		auto CreateArray(Value* a_value, std::uint32_t a_size = 0) const -> bool;
		auto CreateFunction(Value* a_value, FunctionHandler* a_func, void* a_userData = nullptr) const -> bool;
		auto GetVariable(Value* a_val, const char* a_pathToVar) const -> bool;
		auto SetVariable(
			const char* a_pathToVar,
			const Value& a_value,
			Movie::SetVarType a_setType = Movie::SetVarType::Sticky) const -> bool;
		auto GetVariableArray(
			Movie::SetArrayType a_type,
			const char* a_pathToVar,
			std::uint32_t a_index,
			void* a_data,
			std::uint32_t a_count) const -> bool;
		auto SetVariableArray(
			Movie::SetArrayType a_type,
			const char* a_pathToVar,
			std::uint32_t a_index,
			const void* a_data,
			std::uint32_t a_count,
			Movie::SetVarType a_setType = Movie::SetVarType::Sticky) const -> bool;
		[[nodiscard]]
		auto GetVariableArraySize(const char* a_pathToVar) const -> std::uint32_t;
		auto SetVariableArraySize(
			const char* a_pathToVar,
			std::uint32_t a_count,
			Movie::SetVarType a_setType = Movie::SetVarType::Sticky) const -> bool;
		auto Invoke(
			const char* a_pathToMethod,
			Value* a_result = nullptr,
			const Value* a_args = nullptr,
			std::uint32_t a_numArgs = 0) const -> bool;
		auto Invoke(const char* a_pathToMethod, Value* a_result, const char* a_argFmt, ...) const -> bool;
		auto InvokeArgs(const char* a_pathToMethod, Value* a_result, const char* a_argFmt, std::va_list a_args) const
			-> bool;
		auto Invoke(const char* a_methodName, std::span<const Value> a_args) const -> bool;
		auto Invoke(const char* a_methodName, Value* a_result, std::span<const Value> a_args) const -> bool;

		void Release();

		// members
		Ptr<ASMovieRootBase> asMovieRoot; // 0x18
	};

	static_assert(sizeof(Movie) == 0x20);
}
