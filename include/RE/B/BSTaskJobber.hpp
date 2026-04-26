#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSJobs
{
	class JobList;
}

namespace RE
{
	class __declspec(novtable) BSTaskJobber
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSTaskJobber };
		inline static constexpr auto VTABLE{ VTABLE::BSTaskJobber };

		class __declspec(novtable) Task
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BSTaskJobber__Task };
			inline static constexpr auto VTABLE{ VTABLE::BSTaskJobber__Task };

			virtual ~Task(); // 00

			virtual void Process() = 0; // 01

			GAME_HEAP_REDEFINE_NEW(Task);

			BSTaskJobber* next{ nullptr };	// 08
			BSTaskJobber* owner{ nullptr }; // 10
		};
		static_assert(sizeof(Task) == 0x18);

		virtual ~BSTaskJobber(); // 00

		GAME_HEAP_REDEFINE_NEW(BSTaskJobber);

		// members
		std::array<BSJobs::JobList*, 2> jobList;	// 08
		Task** jobListAddingHeads;					// 18
		Task*** jobListAddingTails;					// 20
		Task* yieldingTaskHead;						// 28
		Task** yieldingTaskTail;					// 30
		std::uint32_t maxJobCount;					// 38
		std::uint32_t whichJobListAdding;			// 3C
		std::array<std::uint32_t, 2> addedCount;	// 40
		mutable BSNonReentrantSpinLock listProtect; // 48
		mutable BSNonReentrantSpinLock addProtect;	// 4C
		bool sharedSlots;							// 50
	};
	static_assert(sizeof(BSTaskJobber) == 0x58);
}
