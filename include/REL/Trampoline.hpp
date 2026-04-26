#pragma once

#include "REL/Asm.hpp"

#include "REX/NotNull.hpp"

#if COMMONLIB_OPTION_XBYAK == 1
namespace Xbyak
{
	class CodeGenerator;
}
#endif

namespace REL::Impl
{
	template <std::size_t N>
	concept valid_jump_size =
		N == sizeof(REL::Asm::Branch5<0x00>) ||
		N == sizeof(REL::Asm::Branch6<0x00>);
}

namespace REL
{
	class Trampoline final
	{
	public:
		using deleter_type = std::function<void(std::byte* a_mem, std::size_t a_size)>;

		Trampoline();
		~Trampoline() noexcept;

		explicit Trampoline(std::string_view a_name);

		Trampoline(const Trampoline&) = delete;
		Trampoline(Trampoline&&) noexcept = default;

		Trampoline& operator=(const Trampoline&) = delete;
		Trampoline& operator=(Trampoline&&) noexcept = default;

		[[nodiscard]] constexpr bool IsEmpty() const noexcept { return _capacity == 0; }
		[[nodiscard]] constexpr std::size_t GetCapacity() const noexcept { return _capacity; }
		[[nodiscard]] constexpr std::size_t GetAllocatedSize() const noexcept { return _size; }
		[[nodiscard]] constexpr std::size_t GetFreeSize() const noexcept { return _capacity - _size; }

		void Create(std::size_t a_size, void* a_module = nullptr);

		void Init(std::byte* a_mem, std::size_t a_size, deleter_type a_deleter = {});

		[[nodiscard]] std::byte* Allocate(std::size_t a_size) noexcept;

#if COMMONLIB_OPTION_XBYAK == 1
		[[nodiscard]] std::byte* Allocate(const Xbyak::CodeGenerator& a_code) noexcept;
#endif

		template <class T, class... Args>
		[[nodiscard]] T* Allocate(Args&&... a_args) noexcept
			requires(std::is_constructible_v<T, Args...>);

		template <std::size_t N>
		std::uintptr_t WriteCall(std::uintptr_t a_source, std::uintptr_t a_target) noexcept
			requires(Impl::valid_jump_size<N>);

		template <std::size_t N, class F>
		std::uintptr_t WriteCall(std::uintptr_t a_source, const F& a_target) noexcept
			requires(Impl::valid_jump_size<N> &&
					 std::is_function_v<F>);

		template <std::size_t N>
		std::uintptr_t WriteJump(std::uintptr_t a_source, std::uintptr_t a_target) noexcept
			requires(Impl::valid_jump_size<N>);

		template <std::size_t N, class F>
		std::uintptr_t WriteJump(std::uintptr_t a_source, const F& a_target) noexcept
			requires(Impl::valid_jump_size<N> &&
					 std::is_function_v<F>);

		std::uintptr_t WriteCall5(std::uintptr_t a_source, std::uintptr_t a_target) noexcept;
		std::uintptr_t WriteCall6(std::uintptr_t a_source, std::uintptr_t a_target) noexcept;
		std::uintptr_t WriteJump5(std::uintptr_t a_source, std::uintptr_t a_target) noexcept;
		std::uintptr_t WriteJump6(std::uintptr_t a_source, std::uintptr_t a_target) noexcept;

		std::uintptr_t AllocateBranch5(std::uintptr_t a_target) noexcept;
		std::uintptr_t AllocateBranch6(std::uintptr_t a_target) noexcept;

	private:
		void Release() noexcept;
		void LogStats() const noexcept;

		std::map<std::uintptr_t, std::byte*> _branch5;
		std::map<std::uintptr_t, std::byte*> _branch6;
		std::string _name{ "Default Trampoline"sv };
		deleter_type _deleter;
		std::byte* _data{ nullptr };
		std::size_t _capacity{ 0 };
		std::size_t _size{ 0 };
	};

	[[nodiscard]] auto GetTrampoline() -> const REX::NotNull<std::unique_ptr<Trampoline>>&;
}

#include "REL/Trampoline.inl"
