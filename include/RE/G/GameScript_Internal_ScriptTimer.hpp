#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Object;
}

namespace RE::GameScript::Internal
{
	class ScriptTimer
		: public BSIntrusiveRefCounted // 00
	{
	public:
		[[nodiscard]] REX::Float32 GetRemainingSeconds(std::uint32_t a_currentTime) const noexcept;
		void SetRemainingSeconds(std::uint32_t a_currentTime, REX::Float32 a_seconds) noexcept;

		[[nodiscard]] REX::Float32 GetRemainingGameTimeSeconds(std::uint32_t a_currentGameTime) const noexcept;
		void SetRemainingGameTimeSeconds(std::uint32_t a_currentGameTime, REX::Float32 a_seconds) noexcept;

		// members
		std::uint32_t targetTime;				  // 04
		std::uint32_t timerID;					  // 08
		BSTSmartPointer<BSScript::Object> object; // 10
	};
	static_assert(sizeof(ScriptTimer) == 0x18);
}
