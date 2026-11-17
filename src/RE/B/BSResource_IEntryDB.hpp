#pragma once

#include "RE/B/BSResource_EntryBucketQueue.hpp"

namespace RE::BSResource
{
	class __declspec(novtable) IEntryDB
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSResource__IEntryDB;
		inline static constexpr const auto& VTABLE = VTABLE::BSResource__IEntryDB;

		class NotifyLoadDone
		{
		public:
			virtual ~NotifyLoadDone(); // 0x00

			// add
			virtual void operator()() = 0; // 0x01
		};

		static_assert(sizeof(NotifyLoadDone) == 0x08);

		class PostFlushNotify
		{
		public:
			virtual ~PostFlushNotify(); // 0x00

			// add
			virtual auto DoOnNotify() -> bool = 0; // 0x01
			virtual void DoOnFinalize() = 0;	   // 0x02

			// members
			std::uint32_t state;   // 0x08
			PostFlushNotify* next; // 0x10
		};

		static_assert(sizeof(PostFlushNotify) == 0x18);

		virtual ~IEntryDB(); // 0x00

		// add
		virtual void CancelLoads() = 0;																		// 0x01
		virtual void FlushReleases() = 0;																	// 0x02
		virtual auto DoLoadIfSameOrBetter(std::uint32_t a_priority) -> bool = 0;							// 0x03
		virtual void DoMergeLoadsFromTo(std::uint32_t a_from, std::uint32_t a_to) = 0;						// 0x04
		virtual auto UserFlush(NotifyLoadDone* a_notify, std::uint32_t a_maxPriority) -> std::uint32_t = 0; // 0x05

		// members
		EntryBucketQueue<PostFlushNotify, 8> postFlushNotifyQueue; // 0x00
	};

	static_assert(sizeof(IEntryDB) == 0xD0);
}
