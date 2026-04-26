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
			kPreCapture,
			kValid,
			kDead
		};

		class __declspec(novtable) HandleData
			: public RefCountBase<HandleData, 69>, // 00
			  public ListNode<HandleData>		   // 10
		{
		public:
			// members
			Ptr<ContextLock> contextLock;				// 20
			REX::Enum<HandleState, std::int32_t> state; // 28
			Entry* entry;								// 30
		};
		static_assert(sizeof(HandleData) == 0x38);

		// members
		Ptr<HandleData> data; // 00
	};
	static_assert(sizeof(RTHandle) == 0x08);
}
