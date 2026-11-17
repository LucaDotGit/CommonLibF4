#pragma once

namespace RE
{
	class __declspec(novtable) GridArray
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GridArray;
		inline static constexpr const auto& VTABLE = VTABLE::GridArray;

		virtual ~GridArray(); // 0x00

		// add
		virtual void DetachAll();											// 0x01
		virtual void KillAll();												// 0x02
		virtual auto SetCenter(std::int32_t a_x, std::int32_t a_y) -> bool; // 0x03
		virtual void Shift(std::int32_t a_x, std::int32_t a_y);				// 0x04
		virtual void Detach(std::uint32_t a_x, std::uint32_t a_y) = 0;		// 0x05
		virtual void ClearItem(std::uint32_t a_x, std::uint32_t a_y) = 0;	// 0x06
		virtual void MoveItem(
			std::uint32_t a_fromX,
			std::uint32_t a_fromY,
			std::uint32_t a_toX,
			std::uint32_t a_toY) = 0; // 0x07
		virtual void SwapItem(
			std::uint32_t a_fromX,
			std::uint32_t a_fromY,
			std::uint32_t a_toX,
			std::uint32_t a_toY) = 0; // 0x08

		// members
		std::int32_t centerX; // 0x08
		std::int32_t centerY; // 0x0C
		std::uint32_t length; // 0x10
	};

	static_assert(sizeof(GridArray) == 0x18);
}
