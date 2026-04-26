#pragma once

#include "F4SE/IObject.hpp"

#include "RE/CoreTypes.hpp"

namespace RE::BSScript
{
	class Variable;
}

namespace F4SE
{
	class IDelayFunctor
		: public IObject
	{
	public:
		inline static constexpr auto EMPTY_DELAY = 0i32;
		inline static constexpr auto EMPTY_STACK_ID = static_cast<RE::BSScript::StackID>(0);

		inline static constexpr auto RUN_ON_NEXT_FRAME_DELAY = 1i32;

		IDelayFunctor() = default;

		IDelayFunctor(const IDelayFunctor&) = delete;
		IDelayFunctor(IDelayFunctor&&) = delete;

		IDelayFunctor& operator=(const IDelayFunctor&) = delete;
		IDelayFunctor& operator=(IDelayFunctor&&) = delete;

		~IDelayFunctor() override = default; // 00

		// override (IObject)
		[[nodiscard]] IDelayFunctor* GetAsDelayFunctor() override { return this; } // 03

		// add
		virtual bool Run(RE::BSScript::Variable& a_outResult) = 0;							   // 06
		[[nodiscard]] virtual bool ShouldReschedule(std::int32_t& a_outDelayMS) = 0;		   // 07
		[[nodiscard]] virtual bool ShouldResumeStack(RE::BSScript::StackID& a_outStackID) = 0; // 08
	};
	static_assert(sizeof(IDelayFunctor) == 0x08);
}
