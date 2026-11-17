#pragma once

#include "REX/Contract.hpp"

#if (COMMONLIB_FEATURE_XBYAK == 1)
namespace Xbyak
{
	class CodeGenerator;
}
#endif

namespace REL::ASM
{
	class Jump14;
}

namespace REX::Logging
{
	class ILogger;
}

namespace REL
{
	class Trampoline final
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
		using deleter_type = void(pointer a_mem, size_type a_size) const noexcept;

		using Branch5MemoryType = REL::ASM::Jump14;
		using Branch6MemoryType = std::uintptr_t;

		Trampoline() noexcept;
		explicit Trampoline(std::string a_name) noexcept;
		explicit Trampoline(std::shared_ptr<REX::Logging::ILogger> a_logger) noexcept;
		Trampoline(std::shared_ptr<REX::Logging::ILogger> a_logger, std::string a_name) noexcept;

		~Trampoline() noexcept;

		Trampoline(const Trampoline&) = delete;
		Trampoline(Trampoline&&) noexcept = default;

		auto operator=(const Trampoline&) -> Trampoline& = delete;
		auto operator=(Trampoline&&) noexcept -> Trampoline& = default;

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
			return _data;
		}

		[[nodiscard]]
		auto data() const noexcept -> const_pointer
		{
			return _data;
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
		auto GetName() const noexcept
		{
			return std::string_view(_name);
		}

		void Create(size_type a_size, void* a_module = nullptr);

		void Setup(pointer a_mem, size_type a_size, std::move_only_function<deleter_type> a_deleter = {});

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto Allocate(size_type a_size) noexcept -> pointer;

#if (COMMONLIB_FEATURE_XBYAK == 1)
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto Allocate(const Xbyak::CodeGenerator& a_code) noexcept
			-> pointer;
#endif

		template <class T, class... Args>
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto Allocate(Args&&... a_args)
			noexcept(std::is_nothrow_constructible_v<T, Args...>) -> T*
			requires(std::is_constructible_v<T, Args...>)
		{
			auto* mem = Allocate(sizeof(T));
			if (!mem) {
				return nullptr;
			}

			return std::construct_at(reinterpret_cast<T*>(mem), std::forward<Args>(a_args)...);
		}

		auto WriteCall5(std::uintptr_t a_source, std::uintptr_t a_target) noexcept -> std::uintptr_t;
		auto WriteCall6(std::uintptr_t a_source, std::uintptr_t a_target) noexcept -> std::uintptr_t;
		auto WriteJump5(std::uintptr_t a_source, std::uintptr_t a_target) noexcept -> std::uintptr_t;
		auto WriteJump6(std::uintptr_t a_source, std::uintptr_t a_target) noexcept -> std::uintptr_t;

		auto AllocateBranch5(std::uintptr_t a_target) noexcept -> std::uintptr_t;
		auto AllocateBranch6(std::uintptr_t a_target) noexcept -> std::uintptr_t;

	private:
		void Dispose() noexcept;
		void LogStats() const noexcept;

		std::shared_ptr<REX::Logging::ILogger> _logger;
		std::string _name;
		std::move_only_function<deleter_type> _deleter;
		pointer _data{nullptr};
		size_type _size{0};
		size_type _capacity{0};
		std::unordered_map<std::uintptr_t, std::span<std::byte>> _branchMap;
	};
}
