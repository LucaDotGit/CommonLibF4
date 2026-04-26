#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/I/INPUT_DEVICE.hpp"
#include "RE/I/INPUT_EVENT_TYPE.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class InputEvent;
}

namespace RE::Impl
{
	template <class T>
	concept InputEventConstraint =
		std::derived_from<T, InputEvent> &&
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		std::same_as<std::remove_cv_t<decltype(T::INPUT_TYPE)>, INPUT_EVENT_TYPE>;
}

namespace RE
{
	class IDEvent;

	class __declspec(novtable) InputEvent
	{
	public:
		inline static constexpr auto RTTI{ RTTI::InputEvent };
		inline static constexpr auto VTABLE{ VTABLE::InputEvent };

		enum class HANDLED_RESULT : std::int32_t
		{
			kUnhandled = 0,
			kContinue = 1,
			kStop = 2
		};

		virtual ~InputEvent() = default; // 00

		// add
		virtual bool HasIDCode() const { return false; } // 02
		virtual const BSFixedString& QUserEvent() const; // 03

		GAME_HEAP_REDEFINE_NEW(InputEvent);

		[[nodiscard]] bool Is(INPUT_EVENT_TYPE a_eventType) const noexcept
		{
			return eventType == a_eventType;
		}

		template <class... Args>
		[[nodiscard]] bool Is(Args... a_args) const noexcept
			requires((std::same_as<Args, InputEvent> && ...))
		{
			return (Is(a_args) || ...);
		}

		template <Impl::InputEventConstraint T>
		[[nodiscard]] bool Is() const noexcept
		{
			return Is(T::INPUT_TYPE);
		}

		[[nodiscard]] bool IsNot(INPUT_EVENT_TYPE a_type) const noexcept
		{
			return !Is(a_type);
		}

		template <class... Args>
		[[nodiscard]] bool IsNot(Args... a_args) const noexcept
			requires((std::same_as<Args, InputEvent> && ...))
		{
			return (IsNot(a_args) || ...);
		}

		template <Impl::InputEventConstraint T>
		[[nodiscard]] bool IsNot() const noexcept
		{
			return IsNot(T::INPUT_TYPE);
		}

		template <Impl::InputEventConstraint T>
		[[nodiscard]] T* As() noexcept
		{
			return Is<T>() ? static_cast<T*>(this) : nullptr;
		}

		template <Impl::InputEventConstraint T>
		[[nodiscard]] const T* As() const noexcept
		{
			return Is<T>() ? static_cast<const T*>(this) : nullptr;
		}

		// members
		REX::Enum<INPUT_DEVICE, std::int32_t> device{ INPUT_DEVICE::kNone };			// 08
		std::int32_t deviceID{ 0 };														// 0C
		REX::Enum<INPUT_EVENT_TYPE, std::int32_t> eventType{ INPUT_EVENT_TYPE::kNone }; // 10
		InputEvent* next{ nullptr };													// 18
		std::uint32_t timeCode{ std::numeric_limits<std::uint32_t>::max() };			// 20
		REX::Enum<HANDLED_RESULT, std::int32_t> handled{ HANDLED_RESULT::kUnhandled };	// 24
	};
	static_assert(sizeof(InputEvent) == 0x28);
}
