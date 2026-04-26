#pragma once

#include "REX/Concepts.hpp"

namespace REX
{
	class MemoryStream final
	{
	public:
		using value_type = std::byte;
		using container_type = std::vector<value_type>;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		constexpr MemoryStream() = default;
		constexpr ~MemoryStream() noexcept = default;

		constexpr explicit MemoryStream(size_type a_size)
			: _buffer(a_size)
		{
		}

		constexpr explicit MemoryStream(const_iterator a_begin, const_iterator a_end)
			: _buffer{ a_begin, a_end }
		{
		}

		constexpr explicit MemoryStream(std::span<const value_type> a_data)
			: _buffer{ a_data.begin(), a_data.end() }
		{
		}

		constexpr explicit MemoryStream(container_type&& a_data) noexcept
			: _buffer(std::move(a_data))
		{
		}

		constexpr MemoryStream(const MemoryStream&) = default;
		constexpr MemoryStream(MemoryStream&&) noexcept = default;

		constexpr MemoryStream& operator=(std::span<const value_type> a_data)
		{
			_buffer.assign(a_data.begin(), a_data.end());
			_position = 0;
			return *this;
		}

		constexpr MemoryStream& operator=(container_type&& a_data) noexcept
		{
			_buffer = std::move(a_data);
			_position = 0;
			return *this;
		}

		constexpr MemoryStream& operator=(const MemoryStream&) = default;
		constexpr MemoryStream& operator=(MemoryStream&&) noexcept = default;

		[[nodiscard]] constexpr reference operator[](size_type a_index) noexcept { return _buffer[a_index]; }
		[[nodiscard]] constexpr const_reference operator[](size_type a_index) const noexcept { return _buffer[a_index]; }

		[[nodiscard]] constexpr reference at(size_type a_index) noexcept { return _buffer[a_index]; }
		[[nodiscard]] constexpr const_reference at(size_type a_index) const noexcept { return _buffer[a_index]; }

		[[nodiscard]] constexpr reference front() noexcept { return _buffer.front(); }
		[[nodiscard]] constexpr const_reference front() const noexcept { return _buffer.front(); }

		[[nodiscard]] constexpr reference back() noexcept { return _buffer.back(); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return _buffer.back(); }

		[[nodiscard]] constexpr pointer data() noexcept { return _buffer.data(); }
		[[nodiscard]] constexpr const_pointer data() const noexcept { return _buffer.data(); }

		[[nodiscard]] constexpr std::span<value_type> buffer() noexcept { return _buffer; }
		[[nodiscard]] constexpr std::span<const value_type> buffer() const noexcept { return _buffer; }

		[[nodiscard]] constexpr iterator begin() noexcept { return _buffer.data(); }
		[[nodiscard]] constexpr const_iterator begin() const noexcept { return _buffer.data(); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return _buffer.data(); }

		[[nodiscard]] constexpr iterator end() noexcept { return _buffer.data() + _buffer.size(); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return _buffer.data() + _buffer.size(); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return _buffer.data() + _buffer.size(); }

		[[nodiscard]] constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

		[[nodiscard]] constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		[[nodiscard]] constexpr size_type size() const noexcept { return _buffer.size(); }
		[[nodiscard]] constexpr size_type capacity() const noexcept { return _buffer.capacity(); }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return _buffer.max_size(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return _buffer.empty(); }
		[[nodiscard]] constexpr bool at_start() const noexcept { return _position == 0; }
		[[nodiscard]] constexpr bool at_end() const noexcept { return _position >= _buffer.size(); }

		[[nodiscard]] constexpr size_type position() const noexcept { return _position; }
		constexpr void position(size_type a_position) const noexcept { _position = std::min(a_position, _buffer.size()); }

		constexpr void rewind() const noexcept { _position = 0; }

		[[nodiscard]] constexpr bool read(pointer a_buffer, size_type a_size) const
		{
			const auto newPosition = _position + a_size;
			if (newPosition > _buffer.size()) {
				return false;
			}

			std::copy(_buffer.data() + _position, _buffer.data() + newPosition, a_buffer);
			_position = newPosition;
			return true;
		}

		template <REX::trivially_writable T>
		[[nodiscard]] bool read(T* a_buffer, size_type a_size) const
		{
			return read(reinterpret_cast<pointer>(a_buffer), a_size * sizeof(T));
		}

		template <REX::trivially_writable T>
		[[nodiscard]] bool read(T& a_value) const
		{
			return read(reinterpret_cast<pointer>(std::addressof(a_value)), sizeof(T));
		}

		template <REX::trivially_writable T>
		[[nodiscard]] bool read(std::span<T> a_buffer) const
		{
			return read(reinterpret_cast<pointer>(a_buffer.data()), a_buffer.size_bytes());
		}

		constexpr bool write(const_pointer a_data, size_type a_size)
		{
			const auto newPosition = _position + a_size;
			if (newPosition > _buffer.size()) {
				_buffer.resize(newPosition);
			}

			std::copy(a_data, a_data + a_size, _buffer.data() + _position);
			_position = newPosition;
			return true;
		}

		template <REX::trivially_readable T>
		bool write(const T* a_data, size_type a_size)
		{
			return write(reinterpret_cast<const_pointer>(a_data), a_size * sizeof(T));
		}

		template <REX::trivially_readable T>
		bool write(const T& a_value)
		{
			return write(reinterpret_cast<const_pointer>(std::addressof(a_value)), sizeof(T));
		}

		template <REX::trivially_readable T>
		bool write(std::span<const T> a_data)
		{
			return write(reinterpret_cast<const_pointer>(a_data.data()), a_data.size_bytes());
		}

		constexpr void resize(size_type a_size)
		{
			_buffer.resize(a_size);
			_position = 0;
		}

		constexpr void resize(size_type a_size, value_type a_value)
		{
			_buffer.resize(a_size, a_value);
			_position = 0;
		}

		constexpr void reserve(size_type a_size)
		{
			_buffer.reserve(a_size);
		}

		constexpr void shrink_to_fit()
		{
			_buffer.shrink_to_fit();
		}

		constexpr void clear() noexcept
		{
			_buffer.clear();
			_position = 0;
		}

		constexpr void swap(MemoryStream& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_buffer, a_other._buffer);
			std::swap(_position, a_other._position);
		}

	private:
		container_type _buffer;
		mutable size_type _position{ 0 };
	};

	constexpr void swap(MemoryStream& a_lhs, MemoryStream& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}
