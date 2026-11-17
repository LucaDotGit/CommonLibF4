#pragma once

#include "Scaleform/A/Array.hpp"
#include "Scaleform/G/GFx_StatMovieView.hpp"
#include "Scaleform/P/Ptr.hpp"
#include "Scaleform/R/Render_Rect.hpp"
#include "Scaleform/R/Render_TreeShape.hpp"

namespace Scaleform::GFx
{
	class CharacterHandle;
	class InteractiveObject;

	class alignas(0x10) FocusGroupDescr
	{
	public:
		enum
		{
			TabableArray_Initialized = 1,
			TabableArray_WithFocusEnabled = 2
		};

		// members
		Ptr<Render::TreeShape> focusRectNode;							// 0x00
		ArrayDH<Ptr<InteractiveObject>, StatMV_Other_Mem> tabableArray; // 0x08
		mutable void* lastFocused;					 // 0x28 - To-Do: `mutable WeakPtr<InteractiveObject>`
		Ptr<CharacterHandle> modalClip;				 // 0x30
		std::uint32_t lastFocusKeyCode;				 // 0x38
		alignas(0x08) Render::RectF lastFocusedRect; // 0x40
		bool focusRectShown;						 // 0x50
		std::uint8_t tabableArrayStatus;			 // 0x51
	};

	static_assert(sizeof(FocusGroupDescr) == 0x60);
}
