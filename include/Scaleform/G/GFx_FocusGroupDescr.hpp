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
			kTabableArray_Initialized = 1,
			kTabableArray_WithFocusEnabled = 2
		};

		// members
		Ptr<Render::TreeShape> focusRectNode;							 // 00
		ArrayDH<Ptr<InteractiveObject>, kStatMV_Other_Mem> tabableArray; // 08
		mutable void* lastFocused;										 // 28 - TODO: `mutable WeakPtr<InteractiveObject>`
		Ptr<CharacterHandle> modalClip;									 // 30
		std::uint32_t lastFocusKeyCode;									 // 38
		alignas(0x08) Render::Rect<REX::Float32> lastFocusedRect;		 // 40
		bool focusRectShown;											 // 50
		std::uint8_t tabableArrayStatus;								 // 51
	};
	static_assert(sizeof(FocusGroupDescr) == 0x60);
}
