#pragma once

#include "REX/ErrorCode.hpp"
#include "REX/W32/CORE.hpp"

namespace REX
{
	class MemoryMap final
	{
	public:
		using value_type = std::byte;
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

		MemoryMap();
		~MemoryMap() noexcept;

		MemoryMap(const MemoryMap&) = delete;
		MemoryMap(MemoryMap&&) noexcept = default;

		MemoryMap& operator=(const MemoryMap&) = delete;
		MemoryMap& operator=(MemoryMap&&) noexcept = default;

		[[nodiscard]] reference operator[](size_type a_index) noexcept { return at(a_index); }
		[[nodiscard]] const_reference operator[](size_type a_index) const noexcept { return at(a_index); }

		[[nodiscard]] reference at(size_type a_index) noexcept
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]] const_reference at(size_type a_index) const noexcept
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]] reference front() noexcept { return at(0); }
		[[nodiscard]] const_reference front() const noexcept { return at(0); }

		[[nodiscard]] reference back() noexcept { return at(size() - 1); }
		[[nodiscard]] const_reference back() const noexcept { return at(size() - 1); }

		[[nodiscard]] pointer data() noexcept { return static_cast<pointer>(_mapViewHandle); }
		[[nodiscard]] const_pointer data() const noexcept { return static_cast<const_pointer>(_mapViewHandle); }

		[[nodiscard]] iterator begin() noexcept { return data(); }
		[[nodiscard]] const_iterator begin() const noexcept { return data(); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return data(); }

		[[nodiscard]] iterator end() noexcept { return data() + size(); }
		[[nodiscard]] const_iterator end() const noexcept { return data() + size(); }
		[[nodiscard]] const_iterator cend() const noexcept { return data() + size(); }

		[[nodiscard]] reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
		[[nodiscard]] const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
		[[nodiscard]] const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

		[[nodiscard]] reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
		[[nodiscard]] const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
		[[nodiscard]] const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		[[nodiscard]] size_type size() const noexcept { return _size; }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); } // NOLINT(readability-convert-member-functions-to-static)

		[[nodiscard]] bool empty() const noexcept { return size() == 0; }

		[[nodiscard]] bool IsFile() const noexcept { return _fileHandle != REX::W32::INVALID_HANDLE_VALUE; }
		[[nodiscard]] bool IsOpen() const noexcept { return _mapViewHandle != nullptr; }
		[[nodiscard]] bool IsOwner() const noexcept { return _isOwner; }

		REX::SystemError Create(bool a_write, std::string_view a_name, size_type a_size) noexcept;
		REX::SystemError Create(bool a_write, const std::filesystem::path& a_path, std::string_view a_name, size_type a_size = std::dynamic_extent) noexcept;

		void Close() noexcept;

	private:
		[[nodiscard]] REX::SystemError CreateImpl(bool a_write, REX::W32::HANDLE a_fileHandle, std::string_view a_name, size_type a_size) noexcept;

		REX::W32::HANDLE _fileHandle{ REX::W32::INVALID_HANDLE_VALUE };
		REX::W32::HANDLE _mapHandle{ 0 };
		void* _mapViewHandle{ nullptr };
		size_type _size{ 0 };
		bool _isOwner{ false };
	};
}
