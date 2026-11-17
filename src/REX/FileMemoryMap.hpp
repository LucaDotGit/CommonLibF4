#pragma once

#include "REX/Contract.hpp"
#include "REX/Error.hpp"
#include "REX/W32/CORE.hpp"
#include "REX/ZString.hpp"

namespace REX
{
	class FileMemoryMap final
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

		enum class Options : std::int32_t
		{
			Read = 1,
			ReadWrite,

			_Min = Read,
			_Max = ReadWrite,

			_Count = _Max
		};

		FileMemoryMap();
		~FileMemoryMap() noexcept;

		FileMemoryMap(const FileMemoryMap&) = delete;
		FileMemoryMap(FileMemoryMap&&) noexcept;

		auto operator=(const FileMemoryMap&) -> FileMemoryMap& = delete;
		auto operator=(FileMemoryMap&&) noexcept -> FileMemoryMap&;

		[[nodiscard]]
		auto operator[](size_type a_index) noexcept -> reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		auto operator[](size_type a_index) const noexcept -> const_reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		auto at(size_type a_index) noexcept -> reference
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]]
		auto at(size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]]
		auto front() noexcept -> reference
		{
			return at(0);
		}

		[[nodiscard]]
		auto front() const noexcept -> const_reference
		{
			return at(0);
		}

		[[nodiscard]]
		auto back() noexcept -> reference
		{
			return at(size() - 1);
		}

		[[nodiscard]]
		auto back() const noexcept -> const_reference
		{
			return at(size() - 1);
		}

		[[nodiscard]]
		auto data() noexcept -> pointer
		{
			return static_cast<pointer>(_mapViewHandle);
		}

		[[nodiscard]]
		auto data() const noexcept -> const_pointer
		{
			return static_cast<const_pointer>(_mapViewHandle);
		}

		[[nodiscard]]
		auto begin() noexcept -> iterator
		{
			return data();
		}

		[[nodiscard]]
		auto begin() const noexcept -> const_iterator
		{
			return data();
		}

		[[nodiscard]]
		auto cbegin() const noexcept -> const_iterator
		{
			return data();
		}

		[[nodiscard]]
		auto end() noexcept -> iterator
		{
			return data() + size();
		}

		[[nodiscard]]
		auto end() const noexcept -> const_iterator
		{
			return data() + size();
		}

		[[nodiscard]]
		auto cend() const noexcept -> const_iterator
		{
			return data() + size();
		}

		[[nodiscard]]
		auto rbegin() noexcept -> reverse_iterator
		{
			return reverse_iterator(end());
		}

		[[nodiscard]]
		auto rbegin() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(end());
		}

		[[nodiscard]]
		auto crbegin() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(cend());
		}

		[[nodiscard]]
		auto rend() noexcept -> reverse_iterator
		{
			return reverse_iterator(begin());
		}

		[[nodiscard]]
		auto rend() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(begin());
		}

		[[nodiscard]]
		auto crend() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(cbegin());
		}

		[[nodiscard]]
		auto size() const noexcept -> size_type
		{
			return _size;
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		constexpr auto max_size() const noexcept -> size_type
		{
			return std::numeric_limits<size_type>::max();
		}

		[[nodiscard]]
		auto empty() const noexcept -> bool
		{
			return size() == 0;
		}

		[[nodiscard]]
		auto IsFile() const noexcept -> bool
		{
			return _fileHandle != REX::W32::INVALID_HANDLE_VALUE;
		}

		[[nodiscard]]
		auto IsOpen() const noexcept -> bool
		{
			return _mapViewHandle != nullptr;
		}

		[[nodiscard]]
		auto IsOwner() const noexcept -> bool
		{
			return _isOwner;
		}

		auto Create(
			REX::ZStringView a_name,
			REX::FileMemoryMap::Options a_options = REX::FileMemoryMap::Options::ReadWrite,
			size_type a_maxSize = std::dynamic_extent) noexcept -> REX::SystemError;

		auto Create(
			const std::filesystem::path& a_filePath,
			REX::ZStringView a_name,
			REX::FileMemoryMap::Options a_options = REX::FileMemoryMap::Options::ReadWrite,
			size_type a_maxSize = std::dynamic_extent) noexcept -> REX::SystemError;

		void Close() noexcept;

	private:
		[[nodiscard]]
		auto CreateImpl(
			REX::W32::HANDLE a_fileHandle,
			REX::ZStringView a_name,
			REX::FileMemoryMap::Options a_options,
			size_type a_maxSize) noexcept -> REX::SystemError;

		REX::W32::HANDLE _fileHandle{REX::W32::INVALID_HANDLE_VALUE};
		REX::W32::HANDLE _mapHandle{0};
		void* _mapViewHandle{nullptr};
		size_type _size{0};
		bool _isOwner{false};
	};
}
