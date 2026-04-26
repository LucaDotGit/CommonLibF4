#pragma once

namespace RE
{
	class InputEvent;

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class __declspec(novtable) BSInputEventReceiver
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSInputEventReceiver };
		inline static constexpr auto VTABLE{ VTABLE::BSInputEventReceiver };

		// add
		virtual void PerformInputProcessing(const InputEvent* a_queueHead) = 0; // 00

		// members
		std::uint32_t currInputTimeCount{ 0 }; // 08
	};
	static_assert(sizeof(BSInputEventReceiver) == 0x10);
}
