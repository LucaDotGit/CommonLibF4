#pragma once

namespace Scaleform::Render
{
	template <class T>
	class Matrix4x4
	{
	public:
		constexpr Matrix4x4() noexcept = default;

		constexpr explicit Matrix4x4(const std::array<std::array<T, 4>, 4>& a_rhs) noexcept :
			matrix(a_rhs)
		{
		}

		constexpr Matrix4x4(
			const std::array<T, 4>& a_row0,
			const std::array<T, 4>& a_row1,
			const std::array<T, 4>& a_row2,
			const std::array<T, 4>& a_row3) noexcept :
			matrix{a_row0, a_row1, a_row2, a_row3}
		{
		}

		constexpr Matrix4x4(
			T a_m00,
			T a_m01,
			T a_m02,
			T a_m03,
			T a_m10,
			T a_m11,
			T a_m12,
			T a_m13,
			T a_m20,
			T a_m21,
			T a_m22,
			T a_m23,
			T a_m30,
			T a_m31,
			T a_m32,
			T a_m33) noexcept :
			matrix{
				{{a_m00, a_m01, a_m02, a_m03},
				 {a_m10, a_m11, a_m12, a_m13},
				 {a_m20, a_m21, a_m22, a_m23},
				 {a_m30, a_m31, a_m32, a_m33}}
			}
		{
		}

		constexpr ~Matrix4x4() noexcept = default;

		constexpr Matrix4x4(const Matrix4x4&) noexcept = default;
		constexpr Matrix4x4(Matrix4x4&&) noexcept = default;

		constexpr auto operator=(const Matrix4x4&) noexcept -> Matrix4x4& = default;
		constexpr auto operator=(Matrix4x4&&) noexcept -> Matrix4x4& = default;

		[[nodiscard]]
		constexpr auto operator==(const Matrix4x4&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const Matrix4x4&) const noexcept = default;

		[[nodiscard]]
		constexpr auto operator[](std::size_t a_index) noexcept -> std::array<T, 4>&
		{
			REX::Assert(a_index < matrix.size());
			return matrix[a_index];
		}

		[[nodiscard]]
		constexpr auto operator[](std::size_t a_index) const noexcept -> const std::array<T, 4>&
		{
			REX::Assert(a_index < matrix.size());
			return matrix[a_index];
		}

		constexpr void swap(Matrix4x4& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(matrix, a_other.matrix);
		}

		// members
		std::array<std::array<T, 4>, 4> matrix; // 0x00
	};

	using Matrix4x4F = Matrix4x4<REX::Float32>;
	static_assert(sizeof(Matrix4x4F) == 0x40);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <class T>
	struct formatter<Scaleform::Render::Matrix4x4<T>> : public formatter<std::string>
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
		constexpr auto format(const Scaleform::Render::Matrix4x4<T>& a_value, FormatContext& a_context) const
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
	struct formatter<Scaleform::Render::Matrix4x4<T>> : public formatter<std::string>
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
		constexpr auto format(const Scaleform::Render::Matrix4x4<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "[{}, {}, {}, {}]"sv, a_value[0], a_value[1], a_value[2], a_value[3]);
		}
	};
}
#endif
