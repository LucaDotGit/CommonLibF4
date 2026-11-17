#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/G/GridArray.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE
{
	class __declspec(novtable) GridCellArray : public GridArray // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GridCellArray;
		inline static constexpr const auto& VTABLE = VTABLE::GridCellArray;

		inline static constexpr auto CELL_SIZE = static_cast<REX::Float32>(4096.0);

		class QueuedAttach
		{
		private:
			enum class ProgressiveAttachState : std::int32_t
			{
				World = 0,
				Models = 1,
				RegisterCombinedObjectVisibility = 2,
				Done = 3
			};

		public:
			// members
			TESObjectCELL* cell;										 // 0x00
			REX::Enum<ProgressiveAttachState, std::int32_t> attachState; // 0x08
		};

		static_assert(sizeof(QueuedAttach) == 0x10);

		class QueuedDetach
		{
		private:
			enum class ProgressiveDetachState : std::int32_t
			{
				ActorsNext = 0,
				RefsNext = 1,
				CombinedArtNext = 2,
				Done = 3
			};

		public:
			// members
			TESObjectCELL* cell;				// 0x00
			ProgressiveDetachState detachState; // 0x08
		};

		static_assert(sizeof(QueuedDetach) == 0x10);

		class AutoDisableQueuedCellAttachDetach
		{
		public:
			// members
			GridCellArray* grid; // 0x00
		};

		~GridCellArray() override; // 0x00

		// override (GridArray)
		void KillAll() override;											 // 0x02
		auto SetCenter(std::int32_t a_x, std::int32_t a_y) -> bool override; // 0x03
		void Detach(std::uint32_t a_x, std::uint32_t a_y) override;			 // 0x05
		void ClearItem(std::uint32_t a_x, std::uint32_t a_y) override;		 // 0x06
		void MoveItem(std::uint32_t a_fromX, std::uint32_t a_fromY, std::uint32_t a_toX, std::uint32_t a_toY)
			override; // 0x07
		void SwapItem(std::uint32_t a_fromX, std::uint32_t a_fromY, std::uint32_t a_toX, std::uint32_t a_toY)
			override; // 0x08

		[[nodiscard]]
		auto GetCell(std::uint32_t a_x, std::uint32_t a_y) const noexcept -> TESObjectCELL*
		{
			return (a_x < length && a_y < length) ? cells[(a_x * length) + a_y] : nullptr;
		}

		// members
		SimpleArray<TESObjectCELL*> cells;			 // 0x18 - allocated using: `0x08 * numGrids * numGrids`
		std::uint32_t cellAttachDetachQueueDisabled; // 0x20
		BSTArray<QueuedAttach> queuedAttach;		 // 0x28
		BSTArray<QueuedDetach> queuedDetach;		 // 0x40
		NiPoint3 worldCenter;						 // 0x58
		bool landAttached;							 // 0x64
	};

	static_assert(sizeof(GridCellArray) == 0x68);
}
