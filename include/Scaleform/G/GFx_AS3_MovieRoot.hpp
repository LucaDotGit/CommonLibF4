#pragma once

#include "Scaleform/A/AutoPtr.hpp"
#include "Scaleform/G/GFx_AS3_FlashUI.hpp"
#include "Scaleform/G/GFx_ASMovieRootBase.hpp"
#include "Scaleform/G/GFx_KeyboardState.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace Scaleform::GFx::AS3
{
	class ASVM;
	class MemoryContextImpl;

	class __declspec(novtable) MovieRoot
		: public Scaleform::GFx::ASMovieRootBase,		  // 00
		  public Scaleform::GFx::AS3::FlashUI,			  // 28
		  public Scaleform::GFx::KeyboardState::IListener // 38
	{
	public:
		class MemContextPtr : Ptr<MemoryContextImpl>
		{
		public:
		};
		static_assert(sizeof(MemContextPtr) == 0x08);

		// members
		MemContextPtr memContext;					// 040
		AutoPtr<ASVM> asVM;							// 048
		std::array<std::byte, 0x4A8 - 0x58> unk058; // 058 - TODO
	};
	static_assert(sizeof(MovieRoot) == 0x4A8);
}
