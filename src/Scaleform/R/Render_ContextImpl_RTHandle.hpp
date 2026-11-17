#pragma once

#include "Scaleform/L/List.hpp"
#include "Scaleform/P/Ptr.hpp"
#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform::Render::ContextImpl
{
	class ContextLock;
	class Entry;

	class RTHandle
	{
	public:
		enum class HandleState : std::int32_t
		{
			PreCapture,
			Valid,
			Dead
		};

		class __declspec(novtable) HandleData :
			public RefCountBase<HandleData, 69>, // 0x00
			public ListNode<HandleData>			 // 0x10
		{
		public:
			// members
			Ptr<ContextLock> contextLock;				// 0x20
			REX::Enum<HandleState, std::int32_t> state; // 0x28
			Entry* entry;								// 0x30
		};

		static_assert(sizeof(HandleData) == 0x38);

		// members
		Ptr<HandleData> data; // 0x00
	};

	static_assert(sizeof(RTHandle) == 0x08);
}
