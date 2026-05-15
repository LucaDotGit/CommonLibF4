#pragma once

namespace RE
{
	class NiFrustum
	{
	public:
		constexpr NiFrustum() noexcept = default;

		constexpr NiFrustum(REX::Float32 a_left, REX::Float32 a_right, REX::Float32 a_top, REX::Float32 a_bottom, REX::Float32 a_near, REX::Float32 a_far, bool a_ortho) noexcept
			: left(a_left), right(a_right), top(a_top), bottom(a_bottom), near(a_near), far(a_far), ortho(a_ortho)
		{
		}

		constexpr ~NiFrustum() noexcept = default;

		constexpr NiFrustum(const NiFrustum&) noexcept = default;
		constexpr NiFrustum(NiFrustum&&) noexcept = default;

		constexpr NiFrustum& operator=(const NiFrustum&) noexcept = default;
		constexpr NiFrustum& operator=(NiFrustum&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const NiFrustum&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const NiFrustum&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const NiFrustum&) const noexcept = default;

		constexpr void swap(NiFrustum& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(left, a_other.left);
			std::swap(right, a_other.right);
			std::swap(top, a_other.top);
			std::swap(bottom, a_other.bottom);
			std::swap(near, a_other.near);
			std::swap(far, a_other.far);
			std::swap(ortho, a_other.ortho);
		}

		REX::Float32 left{ 0.0_f32 };	// 00
		REX::Float32 right{ 0.0_f32 };	// 04
		REX::Float32 top{ 0.0_f32 };	// 08
		REX::Float32 bottom{ 0.0_f32 }; // 0C
		REX::Float32 near{ 0.0_f32 };	// 10
		REX::Float32 far{ 0.0_f32 };	// 14
		bool ortho{ false };			// 18
	};
	static_assert(sizeof(NiFrustum) == 0x1C);

	constexpr void swap(NiFrustum& a_lhs, NiFrustum& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<RE::NiFrustum>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiFrustum& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {}, {}, {}, {})"sv,
				a_value.left, a_value.right, a_value.top, a_value.bottom, a_value.near, a_value.far, a_value.ortho);
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<RE::NiFrustum>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiFrustum& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {}, {}, {}, {})"sv,
				a_value.left, a_value.right, a_value.top, a_value.bottom, a_value.near, a_value.far, a_value.ortho);
		}
	};
}
#endif
