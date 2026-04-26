#pragma once

#include "RE/B/BSEventFlag.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSThread.hpp"

namespace RE
{
	class BGSSaveLoadFile;

	class __declspec(novtable) BGSSaveLoadThread
		: public BSThread // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSaveLoadThread };
		inline static constexpr auto VTABLE{ VTABLE::BGSSaveLoadThread };

		class AsyncRequest
		{
		public:
			using TaskFinishedCallbackType = void (*)(bool);

			// members
			std::uint32_t taskTypeID;						// 00
			BGSSaveLoadFile* savefile;						// 08
			TaskFinishedCallbackType* taskFinishedCallback; // 10
			BSFixedString previousSaveToDelete;				// 18
		};
		static_assert(sizeof(AsyncRequest) == 0x20);

		~BGSSaveLoadThread() override; // 00

		// members
		bool running;																   // 50
		bool busy;																	   // 51
		BSEventFlag haveTask;														   // 58
		alignas(0x80) std::array<std::byte, 0x780 - 0x80> asyncSaveLoadOperationQueue; // 80 - TODO: BSTCommonStaticMessageQueue<AsyncRequest, 8>
	};
	static_assert(sizeof(BGSSaveLoadThread) == 0x780);
}
