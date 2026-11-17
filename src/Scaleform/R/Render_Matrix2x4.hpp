#pragma once

namespace Scaleform::Render
{
	template <class T>
	class Matrix2x4
	{
	public:
		constexpr Matrix2x4() noexcept = default;

		constexpr explicit Matrix2x4(const std::array<std::array<T, 2>, 4>& a_rhs) noexcept :
			matrix(a_rhs)
		{
		}

		constexpr Matrix2x4(
			const std::array<T, 2>& a_row0,
			const std::array<T, 2>& a_row1,
			const std::array<T, 2>& a_row2,
			const std::array<T, 2>& a_row3) noexcept :
			matrix{a_row0, a_row1, a_row2, a_row3}
		{
		}

		constexpr Matrix2x4(T a_m00, T a_m01, T a_m10, T a_m11, T a_m20, T a_m21, T a_m30, T a_m31) noexcept :
			matrix{{{a_m00, a_m01}, {a_m10, a_m11}, {a_m20, a_m21}, {a_m30, a_m31}}}
		{
		}

		constexpr ~Matrix2x4() noexcept = default;

		constexpr Matrix2x4(const Matrix2x4&) noexcept = default;
		constexpr Matrix2x4(Matrix2x4&&) noexcept = default;

		constexpr auto operator=(const Matrix2x4&) noexcept -> Matrix2x4& = default;
		constexpr auto operator=(Matrix2x4&&) noexcept -> Matrix2x4& = default;

		[[nodiscard]]
		constexpr auto operator==(const Matrix2x4&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const Matrix2x4&) const noexcept = default;

		[[nodiscard]]
		constexpr auto operator[](std::size_t a_index) noexcept -> std::array<T, 2>&
		{
			REX::Assert(a_index < matrix.size());
			return matrix[a_index];
		}

		[[nodiscard]]
		constexpr auto operator[](std::size_t a_index) const noexcept -> const std::array<T, 2>&
		{
			REX::Assert(a_index < matrix.size());
			return matrix[a_index];
		}

		constexpr void swap(Matrix2x4& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(matrix, a_other.matrix);
		}

		// members
		std::array<std::array<T, 2>, 4> matrix; // 0x00
	};

	using Matrix2x4F = Matrix2x4<REX::Float32>;
	static_assert(sizeof(Matrix2x4F) == 0x20);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <class T>
	struct formatter<Scaleform::Render::Matrix2x4<T>> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const Scaleform::Render::Matrix2x4<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "[{}, {}, {}, {}]"sv, a_value[0], a_value[1], a_value[2], a_value[3]);
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <class T>
	struct formatter<Scaleform::Render::Matrix2x4<T>> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const Scaleform::Render::Matrix2x4<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "[{}, {}, {}, {}]"sv, a_value[0], a_value[1], a_value[2], a_value[3]);
		}
	};
}
#endif
