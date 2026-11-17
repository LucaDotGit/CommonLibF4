#pragma once

#include "Scaleform/A/Array.hpp"
#include "Scaleform/G/GFx_ASIntervalTimerIntf.hpp"
#include "Scaleform/G/GFx_ASString.hpp"
#include "Scaleform/G/GFx_FocusGroupDescr.hpp"
#include "Scaleform/G/GFx_Movie.hpp"
#include "Scaleform/G/GFx_MultitouchInterface.hpp"
#include "Scaleform/G/GFx_Value.hpp"
#include "Scaleform/G/GFx_Viewport.hpp"
#include "Scaleform/L/List.hpp"
#include "Scaleform/N/NewOverrideBase.hpp"
#include "Scaleform/P/Ptr.hpp"
#include "Scaleform/R/Render_Color.hpp"
#include "Scaleform/R/Render_ContextImpl_Context.hpp"
#include "Scaleform/R/Render_ContextImpl_DisplayHandle.hpp"
#include "Scaleform/R/Render_Matrix2x4.hpp"
#include "Scaleform/R/Render_Point.hpp"
#include "Scaleform/R/Render_ScreenToWorld.hpp"
#include "Scaleform/R/Render_TreeRoot.hpp"

namespace Scaleform
{
	class MemoryHeap;
}

namespace Scaleform::Render
{
	class DrawableImageContext;
	class ThreadCommandQueue;
	class TreeContainer;
	class TreeNode;
}

namespace Scaleform::GFx
{
	class AmpStats;
	class ASMovieRootBase;
	class DisplayObjContainer;
	class DisplayObjectBase;

	class DrawingContext;
	class ExternalInterface;
	class ExternalLibPtr;
	class FontManagerStates;
	class FontResource;
	class FSCommandHandler;
	class IMECandidateListStyle;
	class InteractiveObject;
	class LoadQueueEntry;
	class LoadQueueEntryMT;
	class MovieDef;
	class MovieDefImpl;
	class MovieDefRootNode;
	class StateBagImpl;
	class UserEventHandler;

	class __declspec(novtable) MovieImpl : public Movie // 0x00
	{
	public:
		using MultitouchInputMode = MultitouchInterface::MultitouchInputMode;
		using GestureMask = MultitouchInterface::GestureMask;

		class DragState
		{
		public:
			constexpr DragState() = default;

			// members
			InteractiveObject* character{nullptr};	   // 0x00
			InteractiveObject* topmostEntity{nullptr}; // 0x08
			bool lockCenter{false};					   // 0x10
			bool bound{false};						   // 0x11
			Render::PointF boundLT{};				   // 0x14
			Render::PointF boundRB{};				   // 0x1C
			Render::PointF centerDelta{};			   // 0x24
			std::uint32_t mouseIndex{0};			   // 0x2C
		};

		static_assert(sizeof(DragState) == 0x30);

		class FontDesc
		{
		public:
			// members
			Ptr<MovieDef> movieDef;
			Ptr<FontResource> font;
		};

		static_assert(sizeof(FontDesc) == 0x10);

		class IndirectTransPair
		{
		public:
			// members
			Ptr<Render::TreeNode> transformParent;
			Ptr<DisplayObjectBase> obj;
			Ptr<DisplayObjContainer> originalParent;
			mutable std::int32_t origParentDepth{-1};
		};

		static_assert(sizeof(IndirectTransPair) == 0x20);

		class LevelInfo
		{
		public:
			// members
			std::int32_t level;
			Ptr<InteractiveObject> sprite;
		};

		static_assert(sizeof(IndirectTransPair) == 0x20);

		class MDKillListEntry
		{
		public:
			// members
			std::uint64_t killFrameId;
			Ptr<MovieDefImpl> movieDef;
		};

		static_assert(sizeof(MDKillListEntry) == 0x10);

		class ReturnValueHolder : public NewOverrideBase<StatMV_ActionScript_Mem>
		{
		public:
			// members
			std::byte* charBuffer;									// 0x00
			std::uint32_t charBufferSize;							// 0x08
			ArrayCC<ASString, StatMV_ActionScript_Mem> stringArray; // 0x10
			std::uint32_t stringArrayPos;							// 0x30
		};

		static_assert(sizeof(ReturnValueHolder) == 0x38);

		// members
		LoadQueueEntry* loadQueueHead;									  // 0x0020
		std::uint32_t lastLoadQueueEntryCount;							  // 0x0028
		Ptr<AmpStats> advanceStats;										  // 0x0030
		Value::ObjectInterface* objectInterface;						  // 0x0038
		MemoryHeap* heap;												  // 0x0040
		Ptr<MovieDefImpl> mainMovieDef;									  // 0x0048
		InteractiveObject* mainMovie;									  // 0x0050
		ArrayLH<LevelInfo, StatMV_Other_Mem> movieLevels;				  // 0x0058
		List<MovieDefRootNode> rootMovieDefNodes;						  // 0x0070
		Ptr<StateBagImpl> stateBag;										  // 0x0080
		Ptr<Render::TreeRoot> renderRoot;								  // 0x0088
		Render::ContextImpl::DisplayHandle<Render::TreeRoot> displayRoot; // 0x0090
		Ptr<Render::TreeContainer> topMostRoot;							  // 0x0098
		Viewport viewport;												  // 0x00A0
		REX::Float32 pixelScale;										  // 0x00D4
		REX::Float32 viewScaleX;										  // 0x00D8
		REX::Float32 viewScaleY;										  // 0x00DC
		REX::Float32 viewOffsetX;										  // 0x00E8
		REX::Float32 viewOffsetY;										  // 0x00E4
		ScaleModeType viewScaleMode;									  // 0x00E8
		AlignType viewAlignment;										  // 0x00EC
		Render::RectF visibleFrameRect;									  // 0x00F0
		Render::RectF safeRect;											  // 0x0100
		Render::Matrix2x4F viewportMatrix;								  // 0x0110
		Render::ScreenToWorld screenToWorld;							  // 0x0130
		mutable Ptr<Log> cachedLog;										  // 0x0220
		Ptr<UserEventHandler> userEventHandler;							  // 0x0228
		Ptr<FSCommandHandler> fsCommandHandler;							  // 0x0230
		Ptr<ExternalInterface> externalInterfaceHandler;				  // 0x0238
		Ptr<FontManagerStates> fontManagerStates;						  // 0x0240
		ExternalLibPtr* xmlObjectManager;								  // 0x0248
		std::uint64_t timeElapsed;										  // 0x0250
		REX::Float32 timeRemainder;										  // 0x0258
		REX::Float32 frameTime;											  // 0x025C
		std::uint32_t forceFrameCatchUp;								  // 0x0260
		std::array<std::byte, 0x1F60> unk268;							  // 0x0268 - To-Do: `GFx::InputEventsQueue`
		Render::Color backgroundColor;									  // 0x21C8
		std::array<std::byte, 0x50> unk21D0;							  // 0x21D0 - To-Do: `std::array<MouseState, 1>`
		std::uint32_t mouseCursorCount;									  // 0x2220
		std::uint32_t controllerCount;									  // 0x2224
		void* userData;													  // 0x2228
		std::array<std::byte, 0x688> unk2230; // 0x2230 - To-Do: `std::array<KeyboardState, 1>`
		ReturnValueHolder* returnValueHolder; // 0x28B8
		std::uint32_t instanceNameCount;	  // 0x28C0
		DragState currentDragState;			  // 0x28C8
		std::array<std::byte, 0x08> unk28F8;  // 0x28F8 - To-Do: `ASStringHash<StickyVarNode*>`
		ArrayLH<Ptr<InteractiveObject>, StatMV_Other_Mem> topmostLevelCharacters; // 0x2900
		std::uint64_t startTickMS;												  // 0x2918
		std::uint64_t pauseTickMS;												  // 0x2920
		ArrayLH<Ptr<ASIntervalTimerIntf>, StatMV_Other_Mem> intervalTimers;		  // 0x2928
		std::int32_t lastIntervalTimerId;										  // 0x2940
		Ptr<Render::TreeContainer> focusRectContainerNode;						  // 0x2948
		std::array<FocusGroupDescr, 16> focusGroups;							  // 0x2950
		std::uint32_t focusGroupsCount;											  // 0x2F50
		std::array<std::uint8_t, 16> focusGroupIndexes;							  // 0x2F54
		bool focusRectChanged;													  // 0x2F64
		InteractiveObject* playListHead;										  // 0x2F68
		InteractiveObject* playListOptHead;										  // 0x2F70
		InteractiveObject* unloadListHead;										  // 0x2F78
		std::uint32_t flags;													  // 0x2F80
		std::uint32_t flags2;													  // 0x2F84
		IMECandidateListStyle* imeCandidateListStyle;							  // 0x2F88
		LoadQueueEntryMT* loadQueueMTHead;										  // 0x2F90
		ArrayLH<FontDesc> registeredFonts;										  // 0x2F98
		List<DrawingContext> drawingContextList;								  // 0x2FB0
		Array<MDKillListEntry, StatMV_Other_Mem> movieDefKillList;				  // 0x2FC0
		Ptr<ASMovieRootBase> savedASMovieRoot;									  // 0x2FD8
		Render::ContextImpl::Context renderContext;								  // 0x2FE0
		std::int8_t previouslyCaptured;											  // 0x30F0
		Ptr<Render::DrawableImageContext> drawableImageContext;					  // 0x30F8
		Render::ThreadCommandQueue* renderThreadCommandQueue;					  // 0x3100
		Ptr<MultitouchInterface> multitouchHAL;									  // 0x3108
		MultitouchInputMode multitouchMode;										  // 0x3110
		Ptr<InteractiveObject> gestureTopMostChar;								  // 0x3118
		std::int32_t deviceOrientation; // 0x3120 - To-Do: `OrientationEvent::OrientationType`
		ArrayLH<IndirectTransPair> indirectTransformPairs;
	};

	static_assert(sizeof(MovieImpl) == 0x3140);
}
