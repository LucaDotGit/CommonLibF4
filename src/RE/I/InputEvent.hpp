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
	concept InputEventConstraint = std::derived_from<T, InputEvent> &&
								   !REX::pointer<T> &&
								   !REX::reference<T> &&
								   std::same_as<std::remove_cv_t<decltype(T::INPUT_TYPE)>, INPUT_EVENT_TYPE>;
}

namespace RE
{
	class IDEvent;

	class __declspec(novtable) InputEvent
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::InputEvent;
		inline static constexpr const auto& VTABLE = VTABLE::InputEvent;

		enum class HANDLED_RESULT : std::int32_t
		{
			Unhandled = 0,
			Continue = 1,
			Stop = 2
		};

		virtual ~InputEvent() = default; // 0x00

		// add
		virtual auto HasIDCode() const -> bool // 0x02
		{
			return false;
		}

		virtual auto QUserEvent() const -> const BSFixedString&; // 0x03

		GAME_HEAP_REDEFINE_NEW(InputEvent);

		[[nodiscard]]
		auto Is(INPUT_EVENT_TYPE a_eventType) const noexcept -> bool
		{
			return eventType == a_eventType;
		}

		template <class... Args>
		[[nodiscard]]
		auto Is(Args... a_args) const noexcept -> bool
			requires((std::same_as<Args, InputEvent> && ...))
		{
			return (Is(a_args) || ...);
		}

		template <Impl::InputEventConstraint T>
		[[nodiscard]]
		auto Is() const noexcept -> bool
		{
			return Is(T::INPUT_TYPE);
		}

		[[nodiscard]]
		auto IsNot(INPUT_EVENT_TYPE a_type) const noexcept -> bool
		{
			return !Is(a_type);
		}

		template <class... Args>
		[[nodiscard]]
		auto IsNot(Args... a_args) const noexcept -> bool
			requires((std::same_as<Args, InputEvent> && ...))
		{
			return (IsNot(a_args) || ...);
		}

		template <Impl::InputEventConstraint T>
		[[nodiscard]]
		auto IsNot() const noexcept -> bool
		{
			return IsNot(T::INPUT_TYPE);
		}

		template <Impl::InputEventConstraint T>
		[[nodiscard]]
		auto As() noexcept -> T*
		{
			return Is<T>() ? static_cast<T*>(this) : nullptr;
		}

		template <Impl::InputEventConstraint T>
		[[nodiscard]]
		auto As() const noexcept -> const T*
		{
			return Is<T>() ? static_cast<const T*>(this) : nullptr;
		}

		// members
		REX::Enum<INPUT_DEVICE, std::int32_t> device{INPUT_DEVICE::None};			 // 0x08
		std::int32_t deviceID{0};													 // 0x0C
		REX::Enum<INPUT_EVENT_TYPE, std::int32_t> eventType{INPUT_EVENT_TYPE::None}; // 0x10
		InputEvent* next{nullptr};													 // 0x18
		std::uint32_t timeCode{std::numeric_limits<std::uint32_t>::max()};			 // 0x20
		REX::Enum<HANDLED_RESULT, std::int32_t> handled{HANDLED_RESULT::Unhandled};	 // 0x24
	};

	static_assert(sizeof(InputEvent) == 0x28);
}
