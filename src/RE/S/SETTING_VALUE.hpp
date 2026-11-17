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

		constexpr auto operator=(const SETTING_VALUE&) -> SETTING_VALUE& = default;
		constexpr auto operator=(SETTING_VALUE&&) noexcept -> SETTING_VALUE& = default;

		// members
		std::nullptr_t none{nullptr};
		bool boolean;
		std::int8_t int8;
		std::uint8_t uint8;
		std::int32_t int32;
		std::uint32_t uint32;
		REX::Float32 float32;
		char* string;

		union
		{
		public:
			struct
			{
			public:
				// members
				std::uint8_t red;	// 0x00
				std::uint8_t green; // 0x01
				std::uint8_t blue;	// 0x02
			};

			std::uint32_t hex;
			std::array<std::uint8_t, 3> array;
		} rgb;

		union
		{
		public:
			struct
			{
			public:
				// members
				std::uint8_t red;	// 0x00
				std::uint8_t green; // 0x01
				std::uint8_t blue;	// 0x02
				std::uint8_t alpha; // 0x03
			};

			std::uint32_t hex;
			std::array<std::uint8_t, 4> array;
		} rgba;
	};

	static_assert(sizeof(SETTING_VALUE) == 0x08);
}
