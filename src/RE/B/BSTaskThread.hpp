#pragma once

#include "RE/B/BSEventFlag.hpp"
#include "RE/B/BSTAtomicValue.hpp"
#include "RE/B/BSThread.hpp"

namespace RE
{
	class __declspec(novtable) BSTaskThread : public BSThread // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSTaskThread;
		inline static constexpr const auto& VTABLE = VTABLE::BSTaskThread;

		~BSTaskThread() override; // 0x00

		auto ThreadProc() -> std::uint32_t override; // 0x01

		// members
		std::array<std::byte, 0x80 - 0x50> pad50;		  // 0x50
		BSTAtomicValue<std::uint32_t> pauseResumeRequest; // 0x80
		BSEventFlag taskEvent;							  // 0x88
		bool exit;										  // 0x90
		std::array<std::byte, 0xC0 - 0x91> pad91;		  // 0x91
	};

	static_assert(sizeof(BSTaskThread) == 0xC0);
}
