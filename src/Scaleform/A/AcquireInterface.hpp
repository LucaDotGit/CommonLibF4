#pragma once

namespace Scaleform
{
	class __declspec(novtable) AcquireInterface
	{
	public:
		inline static constexpr const auto& RTTI = RE::RTTI::Scaleform__AcquireInterface;
		inline static constexpr const auto& VTABLE = RE::VTABLE::Scaleform__AcquireInterface;

		virtual ~AcquireInterface() = default; // 0x00

		// add
		virtual auto CanAcquire() -> bool;		 // 0x01
		virtual auto TryAcquire() -> bool;		 // 0x02
		virtual auto TryAcquireCommit() -> bool; // 0x03
		virtual auto TryAcquireCancel() -> bool; // 0x04
	};

	static_assert(sizeof(AcquireInterface) == 0x08);
}
