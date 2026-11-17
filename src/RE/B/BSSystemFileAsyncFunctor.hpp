#pragma once

namespace RE
{
	class __declspec(novtable) BSSystemFileAsyncFunctor
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSSystemFileAsyncFunctor;
		inline static constexpr const auto& VTABLE = VTABLE::BSSystemFileAsyncFunctor;

		virtual ~BSSystemFileAsyncFunctor(); // 0x00

		// members
		std::uint32_t state{0};					 // 0x08
		REX::W32::THREAD_ID requestingThread{0}; // 0x0C
		REX::W32::OVERLAPPED data{};			 // 0x10
	};

	static_assert(sizeof(BSSystemFileAsyncFunctor) == 0x30);
}
