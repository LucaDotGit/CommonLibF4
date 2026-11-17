#pragma once

#include "Scaleform/L/List.hpp"

namespace Scaleform::Render::ContextImpl
{
	class Context;
	class RenderNotify;

	class __declspec(novtable) ContextCaptureNotify : public ListNode<ContextCaptureNotify> // 0x00
	{
	public:
		virtual ~ContextCaptureNotify(); // 0x00

		// add
		virtual void OnCapture();							// 0x01 - { return; }
		virtual void OnNextCapture(RenderNotify* a_notify); // 0x02 - { return; }
		virtual void OnShutdown(bool a_waitFlag);			// 0x03 - { return; }

		// members
		Context* ownedContext{nullptr}; // 0x18
	};

	static_assert(sizeof(ContextCaptureNotify) == 0x20);
}
