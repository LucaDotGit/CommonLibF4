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
		class ContextNode
			: public ListNode<ContextNode> // 00
		{
		public:
			// members
			Context* context{ nullptr }; // 10
		};
		static_assert(sizeof(ContextNode) == 0x18);

		class __declspec(novtable) ServiceCommand
			: public ThreadCommand // 00
		{
		public:
			void Execute() override; // 01

			// members
			RenderNotify* notify{ nullptr }; // 10
		};
		static_assert(sizeof(ServiceCommand) == 0x18);

		virtual ~RenderNotify(); // 00

		// add
		virtual void NewCapture(Context* a_context, bool a_hasChanges);																 // 01
		virtual void ContextReleased(Context* a_context);																			 // 02
		virtual void ServiceQueues();																								 // 03
		virtual void EntryChanges(Context& a_context, PagedItemBuffer<EntryChange, 63>& a_buffer, bool a_forceUpdateImages = false); // 04 - { return; }
		virtual void EntryDestroy(Entry* a_entry);																					 // 05 - { return; }
		virtual void EntryFlush(Entry* a_entry);																					 // 06 - { return; }

		// members
		List<ContextNode> activeContextSet;			   // 08
		ThreadCommandQueue* rtCommandQueue{ nullptr }; // 18
		ServiceCommand serviceCommandInstance;		   // 20
	};
	static_assert(sizeof(RenderNotify) == 0x38);
}
