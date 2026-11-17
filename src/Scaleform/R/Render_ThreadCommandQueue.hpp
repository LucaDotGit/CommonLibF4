#pragma once

namespace Scaleform::Render
{
	class Interfaces;
	class ThreadCommand;

	class __declspec(novtable) ThreadCommandQueue
	{
	public:
		virtual ~ThreadCommandQueue() = default; // 0x00

		// add
		virtual void PushThreadCommand(ThreadCommand* a_command) = 0; // 0x01
		virtual void GetRenderInterfaces(Interfaces* a_ptr);		  // 0x02
	};

	static_assert(sizeof(ThreadCommandQueue) == 0x08);
}
