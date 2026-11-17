#pragma once

#include "Scaleform/L/List.hpp"
#include "Scaleform/R/Render_PagedItemBuffer.hpp"
#include "Scaleform/R/Render_ThreadCommand.hpp"

namespace Scaleform::Render::ContextImpl
{
	class Context;
	class Entry;
	class EntryChange;
	class ThreadCommandQueue;

	class __declspec(novtable) RenderNotify
	{
	public:
		class ContextNode : public ListNode<ContextNode> // 0x00
		{
		public:
			// members
			Context* context{nullptr}; // 0x10
		};

		static_assert(sizeof(ContextNode) == 0x18);

		class __declspec(novtable) ServiceCommand : public ThreadCommand // 0x00
		{
		public:
			void Execute() override; // 0x01

			// members
			RenderNotify* notify{nullptr}; // 0x10
		};

		static_assert(sizeof(ServiceCommand) == 0x18);

		virtual ~RenderNotify(); // 0x00

		// add
		virtual void NewCapture(Context* a_context, bool a_hasChanges); // 0x01
		virtual void ContextReleased(Context* a_context);				// 0x02
		virtual void ServiceQueues();									// 0x03
		virtual void EntryChanges(
			Context& a_context,
			PagedItemBuffer<EntryChange, 63>& a_buffer,
			bool a_forceUpdateImages = false);	   // 0x04 - { return; }
		virtual void EntryDestroy(Entry* a_entry); // 0x05 - { return; }
		virtual void EntryFlush(Entry* a_entry);   // 0x06 - { return; }

		// members
		List<ContextNode> activeContextSet;			 // 0x08
		ThreadCommandQueue* rtCommandQueue{nullptr}; // 0x18
		ServiceCommand serviceCommandInstance;		 // 0x20
	};

	static_assert(sizeof(RenderNotify) == 0x38);
}
