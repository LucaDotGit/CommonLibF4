#pragma once

namespace RE
{
	union SETTING_VALUE
	{
	public:
		constexpr SETTING_VALUE() = default;
		constexpr ~SETTING_VALUE() noexcept = default;

		constexpr SETTING_VALUE(const SETTING_VALUE&) = default;
		constexpr SETTING_VALUE(SETTING_VALUE&&) noexcept = default;

		constexpr SETTING_VALUE& operator=(const SETTING_VALUE&) = default;
		constexpr SETTING_VALUE& operator=(SETTING_VALUE&&) noexcept = default;

		// members
		std::nullptr_t none{ nullptr };
		bool boolean;
		std::int8_t int8;
		std::uint8_t uint8;
		std::int32_t int32;
		std::uint32_t uint32;
		REX::Float32 float32;
		char* string;
		union
		{
			struct
			{
				std::uint8_t red;
				std::uint8_t green;
				std::uint8_t blue;
			};
			std::uint32_t hex;
			std::array<std::uint8_t, 3> array;
		} rgb;
		union
		{
			struct
			{
				std::uint8_t red;
				std::uint8_t green;
				std::uint8_t blue;
				std::uint8_t alpha;
			};
			std::uint32_t hex;
			std::array<std::uint8_t, 4> array;
		} rgba;
	};
	static_assert(sizeof(SETTING_VALUE) == 0x08);
}
