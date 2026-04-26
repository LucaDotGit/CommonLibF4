#pragma once

namespace F4SE
{
	class ITaskDelegate
	{
	public:
		ITaskDelegate() = default;

		ITaskDelegate(const ITaskDelegate&) = delete;
		ITaskDelegate(ITaskDelegate&&) = delete;

		ITaskDelegate& operator=(const ITaskDelegate&) = delete;
		ITaskDelegate& operator=(ITaskDelegate&&) = delete;

		virtual ~ITaskDelegate() = default; // 00

		// add
		virtual void Run() = 0; // 01
	};
	static_assert(sizeof(ITaskDelegate) == 0x08);
}
