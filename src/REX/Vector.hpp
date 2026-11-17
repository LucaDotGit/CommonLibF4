#pragma once

#include "REX/Contract.hpp"
#include "REX/Conversion.hpp"
#include "REX/Hashing.hpp"

namespace REX
{
	inline constexpr auto VECTOR_2_MAX_SIZE = static_cast<std::size_t>(2);
	inline constexpr auto VECTOR_3_MAX_SIZE = static_cast<std::size_t>(3);
	inline constexpr auto VECTOR_4_MAX_SIZE = static_cast<std::size_t>(4);

	template <class T, std::size_t N>
	class Vector final
	{
	public:
		static const Vector ZERO;
		static const Vector UNIT;

		inline static constexpr auto MAX_SIZE = N;
		static_assert(MAX_SIZE >= VECTOR_2_MAX_SIZE);

		using value_type = T;
		using container_type = std::array<value_type, MAX_SIZE>;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		constexpr Vector() noexcept = default;
		constexpr ~Vector() noexcept = default;

		constexpr Vector(value_type a_x, value_type a_y) noexcept
			requires(MAX_SIZE == VECTOR_2_MAX_SIZE)
			:
			_data{a_x, a_y}
		{
		}

		constexpr Vector(value_type a_x, value_type a_y, value_type a_z) noexcept
			requires(MAX_SIZE == VECTOR_3_MAX_SIZE)
			:
			_data{a_x, a_y, a_z}
		{
		}

		constexpr Vector(value_type a_x, value_type a_y, value_type a_z, value_type a_w) noexcept
			requires(MAX_SIZE == VECTOR_4_MAX_SIZE)
			:
			_data{a_x, a_y, a_z, a_w}
		{
		}

		constexpr explicit Vector(container_type a_value) noexcept :
			_data(std::move(a_value))
		{
		}

		constexpr explicit Vector(std::span<const value_type, MAX_SIZE> a_value) noexcept
		{
			std::copy_n(a_value.begin(), a_value.size(), _data.data());
		}

		constexpr Vector(const Vector&) noexcept = default;
		constexpr Vector(Vector&&) noexcept = default;

		constexpr auto operator=(const Vector&) noexcept -> Vector& = default;
		constexpr auto operator=(Vector&&) noexcept -> Vector& = default;

		[[nodiscard]]
		constexpr auto operator==(const Vector&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const Vector&) const noexcept = default;

		[[nodiscard]]
		constexpr auto operator+(const Vector& a_rhs) const noexcept -> Vector
		{
			auto result = Vector();
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				result._data[i] = _data[i] + a_rhs._data[i];
			}

			return result;
		}

		[[nodiscard]]
		constexpr auto operator-(const Vector& a_rhs) const noexcept -> Vector
		{
			auto result = Vector();
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				result._data[i] = _data[i] - a_rhs._data[i];
			}

			return result;
		}

		[[nodiscard]]
		constexpr auto operator*(const Vector& a_rhs) const noexcept -> Vector
		{
			auto result = Vector();
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				result._data[i] = _data[i] * a_rhs._data[i];
			}

			return result;
		}

		[[nodiscard]]
		constexpr auto operator/(const Vector& a_rhs) const noexcept -> Vector
		{
			auto result = Vector();
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				result._data[i] = _data[i] / a_rhs._data[i];
			}

			return result;
		}

		[[nodiscard]]
		constexpr auto operator*(value_type a_rhs) const noexcept -> Vector
		{
			auto result = Vector();
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				result._data[i] = _data[i] * a_rhs;
			}

			return result;
		}

		[[nodiscard]]
		constexpr auto operator/(value_type a_rhs) const noexcept -> Vector
		{
			auto result = Vector();
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				result._data[i] = _data[i] / a_rhs;
			}

			return result;
		}

		[[nodiscard]]
		constexpr auto operator+=(const Vector& a_rhs) noexcept -> Vector&
		{
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				_data[i] += a_rhs._data[i];
			}

			return *this;
		}

		[[nodiscard]]
		constexpr auto operator-=(const Vector& a_rhs) noexcept -> Vector&
		{
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				_data[i] -= a_rhs._data[i];
			}

			return *this;
		}

		[[nodiscard]]
		constexpr auto operator*=(const Vector& a_rhs) noexcept -> Vector&
		{
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				_data[i] *= a_rhs._data[i];
			}

			return *this;
		}

		[[nodiscard]]
		constexpr auto operator/=(const Vector& a_rhs) noexcept -> Vector&
		{
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				_data[i] /= a_rhs._data[i];
			}

			return *this;
		}

		[[nodiscard]]
		constexpr auto operator*=(value_type a_rhs) noexcept -> Vector&
		{
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				_data[i] *= a_rhs;
			}

			return *this;
		}

		[[nodiscard]]
		constexpr auto operator/=(value_type a_rhs) noexcept -> Vector&
		{
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				_data[i] /= a_rhs;
			}

			return *this;
		}

		[[nodiscard]]
		constexpr auto operator[](size_type a_index) noexcept -> reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		constexpr auto operator[](size_type a_index) const noexcept -> const_reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) noexcept -> reference
		{
			REX::Assert(a_index < size());
			return _data[a_index];
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(a_index < size());
			return _data[a_index];
		}

		[[nodiscard]]
		constexpr auto front() noexcept -> reference
		{
			return _data.front();
		}

		[[nodiscard]]
		constexpr auto front() const noexcept -> const_reference
		{
			return _data.front();
		}

		[[nodiscard]]
		constexpr auto back() noexcept -> reference
		{
			return _data.back();
		}

		[[nodiscard]]
		constexpr auto back() const noexcept -> const_reference
		{
			return _data.back();
		}

		[[nodiscard]]
		constexpr auto data() noexcept -> pointer
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto data() const noexcept -> const_pointer
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto begin() noexcept -> iterator
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto begin() const noexcept -> const_iterator
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto cbegin() const noexcept -> const_iterator
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto end() noexcept -> iterator
		{
			return _data.data() + size();
		}

		[[nodiscard]]
		constexpr auto end() const noexcept -> const_iterator
		{
			return _data.data() + size();
		}

		[[nodiscard]]
		constexpr auto cend() const noexcept -> const_iterator
		{
			return _data.data() + size();
		}

		[[nodiscard]]
		constexpr auto rbegin() noexcept -> reverse_iterator
		{
			return reverse_iterator(end());
		}

		[[nodiscard]]
		constexpr auto rbegin() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(end());
		}

		[[nodiscard]]
		constexpr auto crbegin() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(cend());
		}

		[[nodiscard]]
		constexpr auto rend() noexcept -> reverse_iterator
		{
			return reverse_iterator(begin());
		}

		[[nodiscard]]
		constexpr auto rend() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(begin());
		}

		[[nodiscard]]
		constexpr auto crend() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(cbegin());
		}

		[[nodiscard]]
		constexpr auto size() const noexcept -> size_type
		{
			return _data.size();
		}

		[[nodiscard]]
		constexpr auto length() const noexcept -> size_type
		{
			return size();
		}

		[[nodiscard]]
		constexpr auto max_size() const noexcept -> size_type
		{
			return size();
		}

		[[nodiscard]]
		constexpr auto empty() const noexcept -> bool
		{
			return _data.empty();
		}

		[[nodiscard]]
		constexpr auto GetX() const noexcept -> value_type
			requires(MAX_SIZE >= VECTOR_2_MAX_SIZE)
		{
			return at(0);
		}

		constexpr void SetX(value_type a_value) noexcept
			requires(MAX_SIZE >= VECTOR_2_MAX_SIZE)
		{
			at(0) = a_value;
		}

		[[nodiscard]]
		constexpr auto GetY() const noexcept -> value_type
			requires(MAX_SIZE >= VECTOR_2_MAX_SIZE)
		{
			return at(1);
		}

		constexpr void SetY(value_type a_value) noexcept
			requires(MAX_SIZE >= VECTOR_2_MAX_SIZE)
		{
			at(1) = a_value;
		}

		[[nodiscard]]
		constexpr auto GetZ() const noexcept -> value_type
			requires(MAX_SIZE >= VECTOR_3_MAX_SIZE)
		{
			return at(2);
		}

		constexpr void SetZ(value_type a_value) noexcept
			requires(MAX_SIZE >= VECTOR_3_MAX_SIZE)
		{
			at(2) = a_value;
		}

		[[nodiscard]]
		constexpr auto GetW() const noexcept -> value_type
			requires(MAX_SIZE >= VECTOR_4_MAX_SIZE)
		{
			return at(3);
		}

		constexpr void SetW(value_type a_value) noexcept
			requires(MAX_SIZE >= VECTOR_4_MAX_SIZE)
		{
			at(3) = a_value;
		}

		[[nodiscard]]
		constexpr auto ToString() const -> std::string
		{
			auto result = std::string("("sv);

			for (auto i = static_cast<size_type>(0); i < _data.size(); i++) {
				auto value = REX::ToString(_data[i]);
				if (!value.has_value()) [[unlikely]] {
					REX::Assert(false);
					continue;
				}

				result += value.value();

				if (i < _data.size() - 1) {
					result += ", "sv;
				}
			}

			result += ")"sv;
			return result;
		}

		constexpr void swap(Vector& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
		}

		// private:
		// NOLINTBEGIN(readability-identifier-naming)
		container_type _data{};
		// NOLINTEND(readability-identifier-naming)
	};

	template <class T, std::size_t N>
	inline constexpr Vector<T, N> Vector<T, N>::ZERO = Vector();

	template <class T, std::size_t N>
	inline constexpr Vector<T, N> Vector<T, N>::UNIT = []() consteval noexcept -> auto {
		auto result = Vector();
		std::fill_n(result.begin(), result.size(), static_cast<value_type>(1));
		return result;
	}();

	template <class T>
	Vector(T, T) -> Vector<T, 2>;

	template <class T>
	Vector(T, T, T) -> Vector<T, 3>;

	template <class T>
	Vector(T, T, T, T) -> Vector<T, 4>;

	using Vector2F = Vector<REX::Float32, VECTOR_2_MAX_SIZE>;
	using Vector3F = Vector<REX::Float32, VECTOR_3_MAX_SIZE>;
	using Vector4F = Vector<REX::Float32, VECTOR_4_MAX_SIZE>;

	using Vector2 = Vector<REX::Float64, VECTOR_2_MAX_SIZE>;
	using Vector3 = Vector<REX::Float64, VECTOR_3_MAX_SIZE>;
	using Vector4 = Vector<REX::Float64, VECTOR_4_MAX_SIZE>;

	using Vector2L = Vector<REX::Float128, VECTOR_2_MAX_SIZE>;
	using Vector3L = Vector<REX::Float128, VECTOR_3_MAX_SIZE>;
	using Vector4L = Vector<REX::Float128, VECTOR_4_MAX_SIZE>;

	static_assert(std::is_standard_layout_v<Vector2F>);
	static_assert(std::is_standard_layout_v<Vector3F>);
	static_assert(std::is_standard_layout_v<Vector4F>);

	static_assert(std::is_standard_layout_v<Vector2>);
	static_assert(std::is_standard_layout_v<Vector3>);
	static_assert(std::is_standard_layout_v<Vector4>);

	static_assert(std::is_standard_layout_v<Vector2L>);
	static_assert(std::is_standard_layout_v<Vector3L>);
	static_assert(std::is_standard_layout_v<Vector4L>);

	static_assert(std::is_trivially_destructible_v<Vector2F>);
	static_assert(std::is_trivially_destructible_v<Vector3F>);
	static_assert(std::is_trivially_destructible_v<Vector4F>);

	static_assert(std::is_trivially_destructible_v<Vector2>);
	static_assert(std::is_trivially_destructible_v<Vector3>);
	static_assert(std::is_trivially_destructible_v<Vector4>);

	static_assert(std::is_trivially_destructible_v<Vector2L>);
	static_assert(std::is_trivially_destructible_v<Vector3L>);
	static_assert(std::is_trivially_destructible_v<Vector4L>);

	static_assert(std::is_trivially_copyable_v<Vector2F>);
	static_assert(std::is_trivially_copyable_v<Vector3F>);
	static_assert(std::is_trivially_copyable_v<Vector4F>);

	static_assert(std::is_trivially_copyable_v<Vector2>);
	static_assert(std::is_trivially_copyable_v<Vector3>);
	static_assert(std::is_trivially_copyable_v<Vector4>);

	static_assert(std::is_trivially_copyable_v<Vector2L>);
	static_assert(std::is_trivially_copyable_v<Vector3L>);
	static_assert(std::is_trivially_copyable_v<Vector4L>);

	static_assert(std::is_trivially_move_constructible_v<Vector2F>);
	static_assert(std::is_trivially_move_constructible_v<Vector3F>);
	static_assert(std::is_trivially_move_constructible_v<Vector4F>);

	static_assert(std::is_trivially_move_constructible_v<Vector2>);
	static_assert(std::is_trivially_move_constructible_v<Vector3>);
	static_assert(std::is_trivially_move_constructible_v<Vector4>);

	static_assert(std::is_trivially_move_constructible_v<Vector2L>);
	static_assert(std::is_trivially_move_constructible_v<Vector3L>);
	static_assert(std::is_trivially_move_constructible_v<Vector4L>);
}

namespace std
{
	template <class T, std::size_t N>
	struct hash<REX::Vector<T, N>>
	{
	public:
		[[nodiscard]]
		auto operator()(const REX::Vector<T, N>& a_key) const noexcept -> std::size_t
		{
			return REX::HashRange(a_key);
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <class T, std::size_t N>
	struct formatter<REX::Vector<T, N>> : public formatter<std::string>
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
		constexpr auto format(const REX::Vector<T, N>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <class T, std::size_t N>
	struct formatter<REX::Vector<T, N>> : public formatter<std::string>
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
		constexpr auto format(const REX::Vector<T, N>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif

namespace glz
{
	template <class T, std::size_t N>
	struct meta<REX::Vector<T, N>>
	{
	public:
		inline static constexpr auto value = [](auto&& a_self) -> decltype(auto) {
			return a_self._data;
		};
	};
}
