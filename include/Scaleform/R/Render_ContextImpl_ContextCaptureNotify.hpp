#pragma once

#include "Scaleform/L/List.hpp"

namespace Scaleform::Render::ContextImpl
{
	class Context;
	class RenderNotify;

	class __declspec(novtable) ContextCaptureNotify
		: public ListNode<ContextCaptureNotify> // 00
	{
	public:
		virtual ~ContextCaptureNotify(); // 00

		// add
		virtual void OnCapture();							// 01 - { return; }
		virtual void OnNextCapture(RenderNotify* a_notify); // 02 - { return; }
		virtual void OnShutdown(bool a_waitFlag);			// 03 - { return; }

		// members
		Context* ownedContext{ nullptr }; // 18
	};
	static_assert(sizeof(ContextCaptureNotify) == 0x20);
}
