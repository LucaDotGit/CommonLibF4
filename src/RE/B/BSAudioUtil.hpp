#pragma once

namespace RE::BSAudioUtil
{
	inline auto ClampFadeTimeSeconds(REX::Float32 a_seconds) -> std::uint16_t
	{
		constexpr auto MAX_VALUE = std::numeric_limits<std::uint16_t>::max();

		const auto result = a_seconds * static_cast<REX::Float32>(1000.0);
		return (result > MAX_VALUE) ? MAX_VALUE : static_cast<std::uint16_t>(result);
	}
}
