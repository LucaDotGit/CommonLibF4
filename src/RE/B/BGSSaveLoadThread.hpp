#pragma once

#include "RE/B/BSEventFlag.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSThread.hpp"

namespace RE
{
	class BGSSaveLoadFile;

	class __declspec(novtable) BGSSaveLoadThread : public BSThread // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSaveLoadThread;
		inline static constexpr const auto& VTABLE = VTABLE::BGSSaveLoadThread;

		class AsyncRequest
		{
		public:
			using TaskFinishedCallbackType = void (*)(bool);

			// members
			std::uint32_t taskTypeID;						// 0x00
			BGSSaveLoadFile* savefile;						// 0x08
			TaskFinishedCallbackType* taskFinishedCallback; // 0x10
			BSFixedString previousSaveToDelete;				// 0x18
		};

		static_assert(sizeof(AsyncRequest) == 0x20);

		~BGSSaveLoadThread() override; // 0x00

		// members
		bool running;		  // 0x50
		bool busy;			  // 0x51
		BSEventFlag haveTask; // 0x58
		alignas(0x80) std::array<
			std::byte,
			0x780 - 0x80> asyncSaveLoadOperationQueue; // 0x80 - To-Do:
													   // BSTCommonStaticMessageQueue<AsyncRequest,
													   // 8>
	};

	static_assert(sizeof(BGSSaveLoadThread) == 0x780);
}
