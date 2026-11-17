#pragma once

#include "REX/Concepts.hpp"
#include "REX/Container.hpp"
#include "REX/Contract.hpp"
#include "REX/SeekOrigin.hpp"

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

		constexpr MemoryStream() noexcept = default;

		constexpr explicit MemoryStream(size_type a_size) :
			_buffer(a_size)
		{
		}

		constexpr MemoryStream(const_iterator a_begin, const_iterator a_end) :
			_buffer{a_begin, a_end}
		{
		}

		constexpr explicit MemoryStream(std::span<const value_type> a_data) :
			_buffer{a_data.begin(), a_data.end()}
		{
		}

		constexpr explicit MemoryStream(container_type&& a_data) noexcept :
			_buffer(std::move(a_data))
		{
		}

		constexpr ~MemoryStream() noexcept = default;

		constexpr MemoryStream(const MemoryStream&) = default;
		constexpr MemoryStream(MemoryStream&&) noexcept = default;

		constexpr auto operator=(std::span<const value_type> a_data) -> MemoryStream&
		{
			_buffer.assign(a_data.begin(), a_data.end());
			_position = 0;
			return *this;
		}

		constexpr auto operator=(container_type&& a_data) noexcept -> MemoryStream&
		{
			_buffer = std::move(a_data);
			_position = 0;
			return *this;
		}

		constexpr auto operator=(const MemoryStream&) -> MemoryStream& = default;
		constexpr auto operator=(MemoryStream&&) noexcept -> MemoryStream& = default;

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
			return _buffer[a_index];
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(a_index < size());
			return _buffer[a_index];
		}

		[[nodiscard]]
		constexpr auto front() noexcept -> reference
		{
			return _buffer.front();
		}

		[[nodiscard]]
		constexpr auto front() const noexcept -> const_reference
		{
			return _buffer.front();
		}

		[[nodiscard]]
		constexpr auto back() noexcept -> reference
		{
			return _buffer.back();
		}

		[[nodiscard]]
		constexpr auto back() const noexcept -> const_reference
		{
			return _buffer.back();
		}

		[[nodiscard]]
		constexpr auto data() noexcept -> pointer
		{
			return _buffer.data();
		}

		[[nodiscard]]
		constexpr auto data() const noexcept -> const_pointer
		{
			return _buffer.data();
		}

		[[nodiscard]]
		constexpr auto begin() noexcept -> iterator
		{
			return _buffer.data();
		}

		[[nodiscard]]
		constexpr auto begin() const noexcept -> const_iterator
		{
			return _buffer.data();
		}

		[[nodiscard]]
		constexpr auto cbegin() const noexcept -> const_iterator
		{
			return _buffer.data();
		}

		[[nodiscard]]
		constexpr auto end() noexcept -> iterator
		{
			return _buffer.data() + _buffer.size();
		}

		[[nodiscard]]
		constexpr auto end() const noexcept -> const_iterator
		{
			return _buffer.data() + _buffer.size();
		}

		[[nodiscard]]
		constexpr auto cend() const noexcept -> const_iterator
		{
			return _buffer.data() + _buffer.size();
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
			return _buffer.size();
		}

		[[nodiscard]]
		constexpr auto capacity() const noexcept -> size_type
		{
			return _buffer.capacity();
		}

		[[nodiscard]]
		constexpr auto max_size() const noexcept -> size_type
		{
			return _buffer.max_size();
		}

		[[nodiscard]]
		constexpr auto empty() const noexcept -> bool
		{
			return _buffer.empty();
		}

		[[nodiscard]]
		constexpr auto GetPosition() const noexcept -> size_type
		{
			return _position;
		}

		constexpr void SetPosition(size_type a_position) const noexcept
		{
			Seek(static_cast<difference_type>(a_position), SeekOrigin::Begin);
		}

		constexpr void ModPosition(difference_type a_offset) const noexcept
		{
			Seek(a_offset, SeekOrigin::Current);
		}

		constexpr void ResetPosition() const noexcept
		{
			Seek(0, SeekOrigin::Begin);
		}

		constexpr auto Seek(difference_type a_offset, SeekOrigin a_seekOrigin) const noexcept -> size_type
		{
			switch (a_seekOrigin) {
				case SeekOrigin::Begin: {
					if (a_offset < 0) {
						_position = 0;
						return 0;
					}

					_position =
						static_cast<size_type>(std::min(static_cast<difference_type>(_buffer.size()), a_offset));
					return _position;
				}
				case SeekOrigin::Current: {
					const auto newPosition = static_cast<difference_type>(_position) + a_offset;
					if (newPosition < 0) {
						_position = 0;
						return 0;
					}

					_position =
						static_cast<size_type>(std::min(static_cast<difference_type>(_buffer.size()), newPosition));
					return _position;
				}
				case SeekOrigin::End: {
					const auto newPosition = static_cast<difference_type>(_buffer.size()) + a_offset;
					if (newPosition < 0) {
						_position = 0;
						return 0;
					}

					_position =
						static_cast<size_type>(std::min(static_cast<difference_type>(_buffer.size()), newPosition));
					return _position;
				}
				[[unlikely]]
				default: {
					REX::Assert(false);
					_position = 0;
					return 0;
				}
			}
		}

		[[nodiscard]]
		constexpr auto Peek() const noexcept -> std::optional<value_type>
		{
			if (_position >= _buffer.size()) {
				return std::nullopt;
			}

			return _buffer[_position];
		}

		[[nodiscard]]
		constexpr auto TryRead(pointer a_buffer, size_type a_size) const noexcept -> size_type
		{
			if (a_size == 0) {
				return 0;
			}

			const auto availableSize = std::min(a_size, _buffer.size() - _position);
			if (availableSize == 0) {
				return 0;
			}

			std::copy_n(_buffer.data() + _position, availableSize, a_buffer);
			_position += availableSize;

			return availableSize;
		}

		[[nodiscard]]
		constexpr auto Read(pointer a_buffer, size_type a_size) const noexcept -> bool
		{
			return TryRead(a_buffer, a_size) == a_size;
		}

		constexpr void Write(const_pointer a_data, size_type a_size)
		{
			if (a_size == 0) {
				return;
			}

			const auto newPosition = _position + a_size;
			if (newPosition > _buffer.size()) {
				REX::ResizeForOverwrite(_buffer, newPosition);
			}

			std::copy_n(a_data, a_size, _buffer.data() + _position);
			_position += a_size;
		}

		constexpr void resize(size_type a_newSize)
		{
			_buffer.resize(a_newSize);
			_position = 0;
		}

		constexpr void resize(size_type a_newSize, value_type a_value)
		{
			_buffer.resize(a_newSize, a_value);
			_position = 0;
		}

		constexpr void reserve(size_type a_newCapacity)
		{
			_buffer.reserve(a_newCapacity);
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

		template <REX::trivially_writable T>
		[[nodiscard]]
		auto TryRead(T* a_buffer, size_type a_size) const noexcept -> size_type
		{
			return TryRead(reinterpret_cast<pointer>(a_buffer), a_size * sizeof(T));
		}

		template <REX::trivially_writable T, std::size_t N>
		[[nodiscard]]
		auto TryRead(std::span<T, N> a_buffer) const noexcept -> size_type
		{
			return TryRead(reinterpret_cast<pointer>(a_buffer.data()), a_buffer.size_bytes());
		}

		template <REX::trivially_writable T>
		[[nodiscard]]
		auto Read(T* a_buffer, size_type a_size) const noexcept -> bool
		{
			return Read(reinterpret_cast<pointer>(a_buffer), a_size * sizeof(T));
		}

		template <REX::trivially_writable T, std::size_t N>
		[[nodiscard]]
		auto Read(std::span<T, N> a_buffer) const noexcept -> bool
		{
			return Read(reinterpret_cast<pointer>(a_buffer.data()), a_buffer.size_bytes());
		}

		template <REX::trivially_writable T>
		[[nodiscard]]
		auto Read(T& a_outValue) const noexcept -> bool
		{
			return Read(reinterpret_cast<pointer>(std::addressof(a_outValue)), sizeof(T));
		}

		template <REX::trivially_writable T>
		[[nodiscard]]
		auto Read() const noexcept -> std::optional<T>
		{
			auto result = T();

			if (!Read(result)) [[unlikely]] {
				return std::nullopt;
			}

			return result;
		}

		template <REX::trivially_readable T>
		void Write(const T* a_data, size_type a_size)
		{
			Write(reinterpret_cast<const_pointer>(a_data), a_size * sizeof(T));
		}

		template <REX::trivially_readable T, std::size_t N>
		void Write(std::span<const T, N> a_span)
		{
			Write(reinterpret_cast<const_pointer>(a_span.data()), a_span.size_bytes());
		}

		template <REX::trivially_readable T>
		void Write(const T& a_value)
		{
			Write(reinterpret_cast<const_pointer>(std::addressof(a_value)), sizeof(T));
		}

	private:
		container_type _buffer;
		mutable size_type _position{0};
	};
}
