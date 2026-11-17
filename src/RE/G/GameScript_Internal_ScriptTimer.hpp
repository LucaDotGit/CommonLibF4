#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Object;
}

namespace RE::GameScript::Internal
{
	class ScriptTimer : public BSIntrusiveRefCounted // 0x00
	{
	public:
		using Miliseconds = std::chrono::duration<std::uint32_t, std::chrono::milliseconds::period>;
		using Seconds = std::chrono::duration<REX::Float32, std::chrono::seconds::period>;

		[[nodiscard]]
		auto GetRemainingSeconds(Miliseconds a_currentTime) const noexcept -> Seconds;
		void SetRemainingSeconds(Miliseconds a_currentTime, Seconds a_seconds) noexcept;

		[[nodiscard]]
		auto GetRemainingGameTimeSeconds(Miliseconds a_currentGameTime) const noexcept -> Seconds;
		void SetRemainingGameTimeSeconds(Miliseconds a_currentGameTime, Seconds a_seconds) noexcept;

		// members
		Miliseconds targetTime;					  // 0x04
		std::uint32_t timerID;					  // 0x08
		BSTSmartPointer<BSScript::Object> object; // 0x10
	};

	static_assert(sizeof(ScriptTimer) == 0x18);
}
