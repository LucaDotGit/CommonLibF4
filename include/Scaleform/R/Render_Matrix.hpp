#pragma once

namespace Scaleform::Render
{
	template <class T>
	class Matrix2x4
	{
	public:
		constexpr Matrix2x4() noexcept = default;

		constexpr Matrix2x4(const std::array<std::array<T, 2>, 4>& a_rhs) noexcept
			: matrix(a_rhs)
		{
		}

		constexpr Matrix2x4(const std::array<T, 2>& a_row0, const std::array<T, 2>& a_row1, const std::array<T, 2>& a_row2, const std::array<T, 2>& a_row3) noexcept
			: matrix{ a_row0, a_row1, a_row2, a_row3 }
		{
		}

		constexpr Matrix2x4(T a_m00, T a_m01, T a_m10, T a_m11, T a_m20, T a_m21, T a_m30, T a_m31) noexcept
			: matrix{ { { a_m00, a_m01 }, { a_m10, a_m11 }, { a_m20, a_m21 }, { a_m30, a_m31 } } }
		{
		}

		constexpr ~Matrix2x4() noexcept = default;

		constexpr Matrix2x4(const Matrix2x4&) noexcept = default;
		constexpr Matrix2x4(Matrix2x4&&) noexcept = default;

		constexpr Matrix2x4& operator=(const Matrix2x4&) noexcept = default;
		constexpr Matrix2x4& operator=(Matrix2x4&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Matrix2x4&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Matrix2x4&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Matrix2x4&) const noexcept = default;

		[[nodiscard]] constexpr std::array<T, 2>& operator[](std::size_t a_index) noexcept
		{
			REX::Assert(a_index < matrix.size());
			return matrix[a_index];
		}

		[[nodiscard]] constexpr const std::array<T, 2>& operator[](std::size_t a_index) const noexcept
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
		std::array<std::array<T, 2>, 4> matrix; // 00
	};

	extern template class Matrix2x4<REX::Float32>;

	template <class T>
	constexpr void swap(Matrix2x4<T>& a_lhs, Matrix2x4<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	extern template void swap(Matrix2x4<REX::Float32>&, Matrix2x4<REX::Float32>&) noexcept;
}

namespace Scaleform::Render
{
	template <class T>
	class Matrix3x4
	{
	public:
		constexpr Matrix3x4() noexcept = default;

		constexpr Matrix3x4(const std::array<std::array<T, 3>, 4>& a_rhs) noexcept
			: matrix(a_rhs)
		{
		}

		constexpr Matrix3x4(const std::array<T, 3>& a_row0, const std::array<T, 3>& a_row1, const std::array<T, 3>& a_row2, const std::array<T, 3>& a_row3) noexcept
			: matrix{ a_row0, a_row1, a_row2, a_row3 }
		{
		}

		constexpr Matrix3x4(T a_m00, T a_m01, T a_m02, T a_m10, T a_m11, T a_m12, T a_m20, T a_m21, T a_m22, T a_m30, T a_m31, T a_m32) noexcept
			: matrix{ { { a_m00, a_m01, a_m02 }, { a_m10, a_m11, a_m12 }, { a_m20, a_m21, a_m22 }, { a_m30, a_m31, a_m32 } } }
		{
		}

		constexpr ~Matrix3x4() noexcept = default;

		constexpr Matrix3x4(const Matrix3x4&) noexcept = default;
		constexpr Matrix3x4(Matrix3x4&&) noexcept = default;

		constexpr Matrix3x4& operator=(const Matrix3x4&) noexcept = default;
		constexpr Matrix3x4& operator=(Matrix3x4&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Matrix3x4&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Matrix3x4&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Matrix3x4&) const noexcept = default;

		[[nodiscard]] constexpr std::array<T, 3>& operator[](std::size_t a_index) noexcept
		{
			REX::Assert(a_index < matrix.size());
			return matrix[a_index];
		}

		[[nodiscard]] constexpr const std::array<T, 3>& operator[](std::size_t a_index) const noexcept
		{
			REX::Assert(a_index < matrix.size());
			return matrix[a_index];
		}

		constexpr void swap(Matrix3x4& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(matrix, a_other.matrix);
		}

		// members
		std::array<std::array<T, 3>, 4> matrix; // 00
	};

	extern template class Matrix3x4<REX::Float32>;

	template <class T>
	constexpr void swap(Matrix3x4<T>& a_lhs, Matrix3x4<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	extern template void swap(Matrix3x4<REX::Float32>&, Matrix3x4<REX::Float32>&) noexcept;
}

namespace Scaleform::Render
{
	template <class T>
	class Matrix4x4
	{
	public:
		constexpr Matrix4x4() noexcept = default;

		constexpr Matrix4x4(const std::array<std::array<T, 4>, 4>& a_rhs) noexcept
			: matrix(a_rhs)
		{
		}

		constexpr Matrix4x4(const std::array<T, 4>& a_row0, const std::array<T, 4>& a_row1, const std::array<T, 4>& a_row2, const std::array<T, 4>& a_row3) noexcept
			: matrix{ a_row0, a_row1, a_row2, a_row3 }
		{
		}

		constexpr Matrix4x4(T a_m00, T a_m01, T a_m02, T a_m03, T a_m10, T a_m11, T a_m12, T a_m13, T a_m20, T a_m21, T a_m22, T a_m23, T a_m30, T a_m31, T a_m32, T a_m33) noexcept
			: matrix{ { { a_m00, a_m01, a_m02, a_m03 }, { a_m10, a_m11, a_m12, a_m13 }, { a_m20, a_m21, a_m22, a_m23 }, { a_m30, a_m31, a_m32, a_m33 } } }
		{
		}

		constexpr ~Matrix4x4() noexcept = default;

		constexpr Matrix4x4(const Matrix4x4&) noexcept = default;
		constexpr Matrix4x4(Matrix4x4&&) noexcept = default;

		constexpr Matrix4x4& operator=(const Matrix4x4&) noexcept = default;
		constexpr Matrix4x4& operator=(Matrix4x4&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Matrix4x4&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Matrix4x4&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Matrix4x4&) const noexcept = default;

		[[nodiscard]] constexpr std::array<T, 4>& operator[](std::size_t a_index) noexcept
		{
			REX::Assert(a_index < matrix.size());
			return matrix[a_index];
		}

		[[nodiscard]] constexpr const std::array<T, 4>& operator[](std::size_t a_index) const noexcept
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
		std::array<std::array<T, 4>, 4> matrix; // 00
	};

	extern template class Matrix4x4<REX::Float32>;

	template <class T>
	constexpr void swap(Matrix4x4<T>& a_lhs, Matrix4x4<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	extern template void swap(Matrix4x4<REX::Float32>&, Matrix4x4<REX::Float32>&) noexcept;
}

#if __cpp_lib_format > 0l
namespace std
{
	template <class T>
	struct formatter<Scaleform::Render::Matrix2x4<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const Scaleform::Render::Matrix2x4<T>& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "[{}, {}, {}, {}]"sv, a_value[0], a_value[1], a_value[2], a_value[3]);
		}
	};

	template <class T>
	struct formatter<Scaleform::Render::Matrix3x4<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const Scaleform::Render::Matrix3x4<T>& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "[{}, {}, {}, {}]"sv, a_value[0], a_value[1], a_value[2], a_value[3]);
		}
	};

	template <class T>
	struct formatter<Scaleform::Render::Matrix4x4<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const Scaleform::Render::Matrix4x4<T>& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "[{}, {}, {}, {}]"sv, a_value[0], a_value[1], a_value[2], a_value[3]);
		}
	};

	extern template struct formatter<Scaleform::Render::Matrix2x4<REX::Float32>>;
	extern template struct formatter<Scaleform::Render::Matrix3x4<REX::Float32>>;
	extern template struct formatter<Scaleform::Render::Matrix4x4<REX::Float32>>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <class T>
	struct formatter<Scaleform::Render::Matrix2x4<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const Scaleform::Render::Matrix2x4<T>& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "[{}, {}, {}, {}]"sv, a_value[0], a_value[1], a_value[2], a_value[3]);
		}
	};

	template <class T>
	struct formatter<Scaleform::Render::Matrix3x4<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const Scaleform::Render::Matrix3x4<T>& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "[{}, {}, {}, {}]"sv, a_value[0], a_value[1], a_value[2], a_value[3]);
		}
	};

	template <class T>
	struct formatter<Scaleform::Render::Matrix4x4<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const Scaleform::Render::Matrix4x4<T>& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "[{}, {}, {}, {}]"sv, a_value[0], a_value[1], a_value[2], a_value[3]);
		}
	};

	extern template struct formatter<Scaleform::Render::Matrix2x4<REX::Float32>>;
	extern template struct formatter<Scaleform::Render::Matrix3x4<REX::Float32>>;
	extern template struct formatter<Scaleform::Render::Matrix4x4<REX::Float32>>;
}
#endif
