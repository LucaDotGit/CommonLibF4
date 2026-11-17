#pragma once

namespace F4SE
{
	class ITaskDelegate
	{
	public:
		ITaskDelegate() noexcept = default;

		ITaskDelegate(const ITaskDelegate&) = delete;
		ITaskDelegate(ITaskDelegate&&) = delete;

		auto operator=(const ITaskDelegate&) -> ITaskDelegate& = delete;
		auto operator=(ITaskDelegate&&) -> ITaskDelegate& = delete;

		virtual ~ITaskDelegate() noexcept = default; // 0x00

		// add
		virtual void Run() = 0; // 0x01
	};

	static_assert(sizeof(ITaskDelegate) == 0x08);
}
