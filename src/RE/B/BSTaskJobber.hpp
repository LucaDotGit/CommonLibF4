#pragma once

#include "RE/B/BSNonReentrantSpinLock.hpp"
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
		inline static constexpr const auto& RTTI = RTTI::BSTaskJobber;
		inline static constexpr const auto& VTABLE = VTABLE::BSTaskJobber;

		class __declspec(novtable) Task
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::BSTaskJobber__Task;
			inline static constexpr const auto& VTABLE = VTABLE::BSTaskJobber__Task;

			virtual ~Task(); // 0x00

			virtual void Process() = 0; // 0x01

			GAME_HEAP_REDEFINE_NEW(Task);

			BSTaskJobber* next{nullptr};  // 0x08
			BSTaskJobber* owner{nullptr}; // 0x10
		};

		static_assert(sizeof(Task) == 0x18);

		virtual ~BSTaskJobber(); // 0x00

		GAME_HEAP_REDEFINE_NEW(BSTaskJobber);

		// members
		std::array<BSJobs::JobList*, 2> jobList;	// 0x08
		Task** jobListAddingHeads;					// 0x18
		Task*** jobListAddingTails;					// 0x20
		Task* yieldingTaskHead;						// 0x28
		Task** yieldingTaskTail;					// 0x30
		std::uint32_t maxJobCount;					// 0x38
		std::uint32_t whichJobListAdding;			// 0x3C
		std::array<std::uint32_t, 2> addedCount;	// 0x40
		mutable BSNonReentrantSpinLock listProtect; // 0x48
		mutable BSNonReentrantSpinLock addProtect;	// 0x4C
		bool sharedSlots;							// 0x50
	};

	static_assert(sizeof(BSTaskJobber) == 0x58);
}
