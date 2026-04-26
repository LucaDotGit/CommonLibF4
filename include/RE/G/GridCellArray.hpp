#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/G/GridArray.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE
{
	class __declspec(novtable) GridCellArray
		: public GridArray // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GridCellArray };
		inline static constexpr auto VTABLE{ VTABLE::GridCellArray };

		inline static constexpr auto CELL_SIZE = 4096.0_f32;

		class QueuedAttach
		{
		private:
			enum class ProgressiveAttachState : std::int32_t
			{
				kToWorld = 0,
				kModels = 1,
				kRegisterCombinedObjectVisibility = 2,
				kDone = 3
			};

		public:
			// members
			TESObjectCELL* cell;										 // 00
			REX::Enum<ProgressiveAttachState, std::int32_t> attachState; // 08
		};
		static_assert(sizeof(QueuedAttach) == 0x10);

		class QueuedDetach
		{
		private:
			enum class ProgressiveDetachState : std::int32_t
			{
				kProgressiveDetachActorsNext = 0,
				kProgressiveDetachRefsNext = 1,
				kProgressiveDetachCombinedArtNext = 2,
				kProgressiveDetachDone = 3
			};

		public:
			// members
			TESObjectCELL* cell;				// 00
			ProgressiveDetachState detachState; // 08
		};
		static_assert(sizeof(QueuedDetach) == 0x10);

		class AutoDisableQueuedCellAttachDetach
		{
		public:
			// members
			GridCellArray* grid; // 00
		};

		~GridCellArray() override; // 00

		// override (GridArray)
		void KillAll() override;																						// 02
		bool SetCenter(std::int32_t a_x, std::int32_t a_y) override;													// 03
		void Detach(std::uint32_t a_x, std::uint32_t a_y) override;														// 05
		void ClearItem(std::uint32_t a_x, std::uint32_t a_y) override;													// 06
		void MoveItem(std::uint32_t a_fromX, std::uint32_t a_fromY, std::uint32_t a_toX, std::uint32_t a_toY) override; // 07
		void SwapItem(std::uint32_t a_fromX, std::uint32_t a_fromY, std::uint32_t a_toX, std::uint32_t a_toY) override; // 08

		[[nodiscard]] TESObjectCELL* GetCell(std::uint32_t a_x, std::uint32_t a_y) const noexcept
		{
			return (a_x < length && a_y < length) ? cells[(a_x * length) + a_y] : nullptr;
		}

		// members
		SimpleArray<TESObjectCELL*> cells;
		std::uint32_t cellAttachDetachQueueDisabled;
		BSTArray<QueuedAttach> queuedAttach;
		BSTArray<QueuedDetach> queuedDetach;
		NiPoint3 worldCenter;
		bool landAttached;
	};
	static_assert(sizeof(GridCellArray) == 0x68);
}
