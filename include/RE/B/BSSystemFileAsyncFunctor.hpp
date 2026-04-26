#pragma once

namespace RE
{
	class __declspec(novtable) BSSystemFileAsyncFunctor
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSSystemFileAsyncFunctor };
		inline static constexpr auto VTABLE{ VTABLE::BSSystemFileAsyncFunctor };

		virtual ~BSSystemFileAsyncFunctor(); // 00

		// members
		std::uint32_t state{ 0 };				   // 08
		REX::W32::THREAD_ID requestingThread{ 0 }; // 0C
		REX::W32::OVERLAPPED data{};			   // 10
	};
	static_assert(sizeof(BSSystemFileAsyncFunctor) == 0x30);
}
