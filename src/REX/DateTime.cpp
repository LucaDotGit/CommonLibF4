#include "REX/DateTime.hpp"

#include "REX/Formatting.hpp"
#include "REX/NotNull.hpp"

namespace REX
{
	auto DateTime::GetCurrentTimeZone() noexcept
		-> std::expected<REX::NotNull<const std::chrono::time_zone*>, std::exception>
	{
		try {
			return std::chrono::current_zone();
		}
		catch (const std::runtime_error& error) {
			return std::unexpected(error);
		}
		catch (const std::bad_alloc& error) {
			return std::unexpected(error);
		}
	}

	auto DateTime::Now() noexcept -> std::expected<DateTime, std::exception>
	{
		const auto currentTimeZone = GetCurrentTimeZone();
		if (!currentTimeZone.has_value()) [[unlikely]] {
			return std::unexpected(std::move(currentTimeZone).error());
		}

		const auto currentSystemTime = std::chrono::system_clock::now();
		const auto currentLocalTime = (*currentTimeZone)->to_local(currentSystemTime);
		return FromTimePoint(currentLocalTime);
	}

	auto DateTime::UtcNow() noexcept -> DateTime
	{
		const auto currentSystemTime = std::chrono::system_clock::now();
		return FromTimePoint(currentSystemTime);
	}

	auto DateTime::ToString(std::span<char> a_buffer) const noexcept -> std::string_view
	{
		if (a_buffer.size() < MAX_STRING_SIZE) [[unlikely]] {
			return {};
		}

		const auto timeOfDay = GetTimeOfDay();

		const auto formatResult = REX::FormatToN(
			a_buffer.begin(),
			static_cast<std::ptrdiff_t>(a_buffer.size()),
			"{:04d}-{:02d}-{:02d} {:02d}:{:02d}:{:02d}.{:09d}"sv,
			static_cast<std::int32_t>(GetYear()),
			static_cast<std::uint32_t>(GetMonth()),
			static_cast<std::uint32_t>(GetDay()),
			timeOfDay.hours().count(),
			timeOfDay.minutes().count(),
			timeOfDay.seconds().count(),
			timeOfDay.subseconds().count());

		return std::string_view{a_buffer.data(), static_cast<std::size_t>(formatResult.size)};
	}

	auto DateTime::ToString() const -> std::string
	{
		auto buffer = std::array<char, MAX_STRING_SIZE>();
		const auto bufferView = ToString(buffer);
		return std::string(bufferView);
	}
}
