#pragma once

#include "F4SE/IObject.hpp"
#include "RE/CoreTypes.hpp"
#include "REX/Ownership.hpp"

namespace RE::BSScript
{
	class Variable;
}

namespace F4SE
{
	class IDelayFunctor : public IObject
	{
	public:
		using Miliseconds = std::int32_t;

		inline static constexpr auto EMPTY_DELAY = static_cast<Miliseconds>(0);
		inline static constexpr auto EMPTY_STACK_ID = static_cast<RE::BSScript::StackID>(0);

		inline static constexpr auto RUN_ON_NEXT_FRAME_DELAY = static_cast<Miliseconds>(1);

		IDelayFunctor() = default;

		IDelayFunctor(const IDelayFunctor&) = delete;
		IDelayFunctor(IDelayFunctor&&) = delete;

		auto operator=(const IDelayFunctor&) -> IDelayFunctor& = delete;
		auto operator=(IDelayFunctor&&) -> IDelayFunctor& = delete;

		~IDelayFunctor() noexcept override = default; // 0x00

		// override (IObject)
		[[nodiscard]]
		auto GetAsDelayFunctor() noexcept -> REX::Observer<IDelayFunctor*> override // 0x03
		{
			return this;
		}

		// add
		virtual auto Run(RE::BSScript::Variable& a_outResult) -> bool = 0; // 0x06
		[[nodiscard]]
		virtual auto ShouldReschedule(Miliseconds& a_outDelay) -> bool = 0; // 0x07
		[[nodiscard]]
		virtual auto ShouldResumeStack(RE::BSScript::StackID& a_outStackID) -> bool = 0; // 0x08
	};

	static_assert(sizeof(IDelayFunctor) == 0x08);
}
