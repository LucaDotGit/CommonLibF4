#pragma once

#include "REX/Enum.hpp"
#include "REX/Logging/Level.hpp"
#include "REX/SourceLocation.hpp"

namespace REX::Logging
{
	class Context final
	{
	public:
		constexpr Context(
			std::string_view a_name,
			REX::Logging::Level a_level,
			std::chrono::system_clock::time_point a_timePoint,
			std::thread::id a_threadId,
			REX::SourceLocation a_sourceLocation,
			std::string_view a_rawMessage) noexcept :
			_name(a_name),
			_level(a_level),
			_timePoint(a_timePoint),
			_threadId(a_threadId),
			_sourceLocation(a_sourceLocation),
			_rawMessage(a_rawMessage)
		{
		}

		constexpr ~Context() noexcept = default;

		constexpr Context(const Context&) noexcept = default;
		constexpr Context(Context&&) noexcept = default;

		constexpr auto operator=(const Context&) noexcept -> Context& = default;
		constexpr auto operator=(Context&&) noexcept -> Context& = default;

		[[nodiscard]]
		constexpr auto GetName() const noexcept
		{
			return _name;
		}

		[[nodiscard]]
		constexpr auto GetLevel() const noexcept
		{
			return _level.get();
		}

		[[nodiscard]]
		constexpr auto GetTimePoint() const noexcept
		{
			return _timePoint;
		}

		[[nodiscard]]
		constexpr auto GetThreadId() const noexcept
		{
			return _threadId;
		}

		[[nodiscard]]
		constexpr auto GetSourceLocation() const noexcept
		{
			return _sourceLocation;
		}

		[[nodiscard]]
		constexpr auto GetRawMessage() const noexcept
		{
			return _rawMessage;
		}

	private:
		std::string_view _name;
		REX::Enum<REX::Logging::Level> _level;
		std::chrono::system_clock::time_point _timePoint;
		std::thread::id _threadId;
		REX::SourceLocation _sourceLocation;
		std::string_view _rawMessage;
	};
}
