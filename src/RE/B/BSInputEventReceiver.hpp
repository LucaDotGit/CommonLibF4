#pragma once

namespace RE
{
	class InputEvent;

#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class __declspec(novtable) BSInputEventReceiver
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSInputEventReceiver;
		inline static constexpr const auto& VTABLE = VTABLE::BSInputEventReceiver;

		// add
		virtual void PerformInputProcessing(const InputEvent* a_queueHead) = 0; // 0x00

		// members
		std::uint32_t currInputTimeCount{0}; // 0x08
	};

	static_assert(sizeof(BSInputEventReceiver) == 0x10);

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}
