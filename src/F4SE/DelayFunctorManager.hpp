#pragma once

#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace F4SE
{
	class IDelayFunctor;

#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class DelayFunctorManager // final
	{
	public:
		inline static constexpr auto RUN_DIRECTLY_DELAY = static_cast<std::int32_t>(-1);
		inline static constexpr auto RUN_ON_NEXT_FRAME_DELAY = static_cast<std::int32_t>(0);

		DelayFunctorManager() = delete;
		~DelayFunctorManager() = delete;

		DelayFunctorManager(const DelayFunctorManager&) = delete;
		DelayFunctorManager(DelayFunctorManager&&) = delete;

		auto operator=(const DelayFunctorManager&) -> DelayFunctorManager& = delete;
		auto operator=(DelayFunctorManager&&) -> DelayFunctorManager& = delete;

		// add
		virtual void Enqueue(
			[[maybe_unused]] REX::NotNull<REX::Owner<IDelayFunctor*>> a_functor,
			[[maybe_unused]] std::int32_t a_delayMS = RUN_ON_NEXT_FRAME_DELAY) const // 0x00
		{
			return;
		}
	};

	static_assert(sizeof(DelayFunctorManager) == 0x08);

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}
