#include "REL/Trampoline.hpp"

#include "REL/Memory.hpp"

#include "REX/Contract.hpp"
#include "REX/ErrorCode.hpp"
#include "REX/Log.hpp"
#include "REX/Message.hpp"
#include "REX/W32/KERNEL32.hpp"

// xbyak brings in <Windows.h>
#if COMMONLIB_OPTION_XBYAK == 1
#include <xbyak/xbyak.h>

#undef max
#undef MEM_COMMIT
#undef MEM_FREE
#undef MEM_RELEASE
#undef MEM_RESERVE
#undef PAGE_EXECUTE_READWRITE
#endif

namespace REL::Impl
{
	[[nodiscard]] static constexpr std::size_t RoundUp(std::size_t a_number, std::size_t a_multiple) noexcept
	{
		if (a_multiple == 0) {
			return 0;
		}

		const auto remainder = a_number % a_multiple;
		return (remainder == 0) ? a_number : (a_number + a_multiple - remainder);
	}

	[[nodiscard]] static constexpr std::size_t RoundDown(std::size_t a_number, std::size_t a_multiple) noexcept
	{
		if (a_multiple == 0) {
			return 0;
		}

		const auto remainder = a_number % a_multiple;
		return (remainder == 0) ? a_number : (a_number - remainder);
	}

	// Source: https://stackoverflow.com/a/54732489
	[[nodiscard]] static std::byte* AllocateTrampoline(std::size_t a_size, std::uintptr_t a_address)
	{
		constexpr auto GIGA_BYTE = static_cast<std::size_t>(1) << 30;
		constexpr auto MIN_RANGE = static_cast<std::uintptr_t>(GIGA_BYTE * 2);
		constexpr auto MAX_ADDRESS = std::numeric_limits<std::uintptr_t>::max();

		auto systemInfo = REX::W32::SYSTEM_INFO();
		REX::W32::GetSystemInfo(std::addressof(systemInfo));
		const auto granularity = systemInfo.allocationGranularity;

		auto minAddress = a_address >= MIN_RANGE ? RoundUp(a_address - MIN_RANGE, granularity) : 0;
		auto maxAddress = a_address < (MAX_ADDRESS - MIN_RANGE) ? RoundDown(a_address + MIN_RANGE, granularity) : MAX_ADDRESS;

		auto memoryInfo = REX::W32::MEMORY_BASIC_INFORMATION();
		do {
			if (REX::W32::VirtualQuery(std::bit_cast<void*>(minAddress), std::addressof(memoryInfo), sizeof(memoryInfo)) == 0) [[unlikely]] {
				const auto currentError = REX::GetCurrentSystemError();
				REX::Fail(
					"Failed to query memory information.\n"
					"System Error (0x{:08X}): {}"sv,
					currentError.value(), currentError.message());
			}

			const auto baseAddress = std::bit_cast<std::uintptr_t>(memoryInfo.baseAddress);
			minAddress = baseAddress + memoryInfo.regionSize;

			if (memoryInfo.state != REX::W32::MEM_FREE) {
				continue;
			}

			// if rounding did not advance us into the next region and the region is the required size
			auto address = RoundUp(baseAddress, granularity);
			if (address >= minAddress || (minAddress - address) < a_size) {
				continue;
			}

			auto* mem = REX::W32::VirtualAlloc(std::bit_cast<void*>(address), a_size,
				REX::W32::MEM_COMMIT | REX::W32::MEM_RESERVE, REX::W32::PAGE_EXECUTE_READWRITE);
			if (!mem) [[unlikely]] {
				const auto currentError = REX::GetCurrentSystemError();
				REX::Fail(
					"Failed to allocate memory.\n"
					"System Error (0x{:08X}): {}"sv,
					currentError.value(), currentError.message());
			}

			return reinterpret_cast<std::byte*>(mem);
		}
		while (minAddress < maxAddress);

		return nullptr;
	}
}

namespace REL
{
	Trampoline::Trampoline() = default;

	Trampoline::~Trampoline() noexcept
	{
		Release();
	}

	Trampoline::Trampoline(std::string_view a_name)
		: _name(a_name)
	{
	}

	void Trampoline::Create(std::size_t a_size, void* a_module)
	{
		if (a_size == 0) [[unlikely]] {
			REX::Fail("Failed to create trampoline due to empty size."sv);
		}

		if (!a_module) {
			const auto textSection = REL::Module::GetSingleton()->GetSection(REL::MODULE_SECTION_NAME_TEXT);
			a_module = textSection.GetPointer<std::byte>() + textSection.GetSize();
		}

		auto* mem = Impl::AllocateTrampoline(a_size, std::bit_cast<std::uintptr_t>(a_module));
		if (!mem) [[unlikely]] {
			REX::Fail("Failed to allocate memory for trampoline."sv);
		}

		Init(mem, a_size, [](void* a_mem, [[maybe_unused]] std::size_t a_size) noexcept {
			REX::W32::VirtualFree(a_mem, 0, REX::W32::MEM_RELEASE);
		});
	}

	void Trampoline::Init(std::byte* a_mem, std::size_t a_size, deleter_type a_deleter)
	{
		if (a_mem) {
			REL::MemWriteZero(a_mem, a_size);
		}

		Release();

		_deleter = std::move(a_deleter);
		_data = a_mem;
		_capacity = a_size;
		_size = 0;

		LogStats();
	}

	std::byte* Trampoline::Allocate(std::size_t a_size) noexcept
	{
		if (a_size > GetFreeSize()) [[unlikely]] {
			REX::Fail(
				"Failed to handle allocation request.\n"
				"Allocation Size: {}\n"
				"Free Size: {}"sv,
				a_size,
				GetFreeSize());
		}

		auto* mem = _data + _size;
		_size += a_size;

		LogStats();
		return mem;
	}

#if COMMONLIB_OPTION_XBYAK == 1
	std::byte* Trampoline::Allocate(const Xbyak::CodeGenerator& a_code) noexcept
	{
		auto* mem = Allocate(a_code.getSize());
		std::copy_n(reinterpret_cast<const std::byte*>(a_code.getCode()), a_code.getSize(), mem);
		return mem;
	}
#endif

	std::uintptr_t Trampoline::WriteCall5(std::uintptr_t a_source, std::uintptr_t a_target) noexcept
	{
		const auto oldAddress = REL::Asm::Call5::TARGET(a_source);
		const auto assembly = REL::Asm::Call5(a_source, AllocateBranch5(a_target));
		const auto writeError = REL::WriteSafeData(a_source, assembly);

		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			REX::Fail(
				"Failed to write Call5 assembly\n"
				"System Error (0x{:08X}): {}"sv,
				writeError.value(), writeError.message());
		}

		return oldAddress;
	}

	std::uintptr_t Trampoline::WriteCall6(std::uintptr_t a_source, std::uintptr_t a_target) noexcept
	{
		const auto oldAddress = REL::Asm::Call6::TARGET(a_source);
		const auto assembly = REL::Asm::Call6(a_source, AllocateBranch6(a_target));
		const auto writeError = REL::WriteSafeData(a_source, assembly);

		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			REX::Fail(
				"Failed to write Call6 assembly\n"
				"System Error (0x{:08X}): {}"sv,
				writeError.value(), writeError.message());
		}

		return oldAddress;
	}

	std::uintptr_t Trampoline::WriteJump5(std::uintptr_t a_source, std::uintptr_t a_target) noexcept
	{
		const auto oldAddress = REL::Asm::Jump5::TARGET(a_source);
		const auto assembly = REL::Asm::Jump5(a_source, AllocateBranch5(a_target));
		const auto writeError = REL::WriteSafeData(a_source, assembly);

		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			REX::Fail(
				"Failed to write Jump5 assembly\n"
				"System Error (0x{:08X}): {}"sv,
				writeError.value(), writeError.message());
		}

		return oldAddress;
	}

	std::uintptr_t Trampoline::WriteJump6(std::uintptr_t a_source, std::uintptr_t a_target) noexcept
	{
		const auto oldAddress = REL::Asm::Jump6::TARGET(a_source);
		const auto assembly = REL::Asm::Jump6(a_source, AllocateBranch6(a_target));
		const auto writeError = REL::WriteSafeData(a_source, assembly);

		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			REX::Fail(
				"Failed to write Jump6 assembly\n"
				"System Error (0x{:08X}): {}"sv,
				writeError.value(), writeError.message());
		}

		return oldAddress;
	}

	std::uintptr_t Trampoline::AllocateBranch5(std::uintptr_t a_target) noexcept
	{
		const auto branchIt = _branch5.find(a_target);
		if (branchIt != _branch5.end()) {
			auto* mem = reinterpret_cast<Asm::Jump14*>(branchIt->second);
			mem->addr = a_target;
			return std::bit_cast<std::uintptr_t>(mem);
		}

		auto* mem = Allocate<Asm::Jump14>(a_target);
		if (!mem) [[unlikely]] {
			REX::Fail("Failed to allocate memory for trampoline branch 5."sv);
		}

		_branch5.emplace(a_target, reinterpret_cast<std::byte*>(mem));
		return std::bit_cast<std::uintptr_t>(mem);
	}

	std::uintptr_t Trampoline::AllocateBranch6(std::uintptr_t a_target) noexcept
	{
		const auto branchIt = _branch6.find(a_target);
		if (branchIt != _branch6.end()) {
			auto* mem = reinterpret_cast<std::uintptr_t*>(branchIt->second);
			*mem = a_target;
			return std::bit_cast<std::uintptr_t>(mem);
		}

		auto* mem = Allocate<std::uintptr_t>(a_target);
		if (!mem) [[unlikely]] {
			REX::Fail("Failed to allocate memory for trampoline branch 6."sv);
		}

		_branch6.emplace(a_target, reinterpret_cast<std::byte*>(mem));
		return std::bit_cast<std::uintptr_t>(mem);
	}

	void Trampoline::Release() noexcept
	{
		if (_data && _deleter) {
			try {
				std::invoke(_deleter, _data, _capacity);
			}
			catch ([[maybe_unused]] const std::bad_alloc& error) {
				REX::AllocationFail("Failed to allocate memory for xSE trampoline deleter."sv);
			}
			catch (const std::exception& error) {
				REX::Fail("Failed to invoke trampoline deleter: {}"sv,
					error.what());
			}
			catch (...) {
				REX::Fail("Failed to invoke trampoline deleter due to an unknown error."sv);
			}
		}

		_branch5.clear();
		_branch6.clear();
		_data = nullptr;
		_capacity = 0;
		_size = 0;
	}

	void Trampoline::LogStats() const noexcept
	{
		const auto percentage = _capacity == 0 ? 0.0_f64 : (static_cast<REX::Float64>(_size) / static_cast<REX::Float64>(_capacity)) * 100.0_f64;
		REX::LogDebug("{} => {}B / {}B ({:05.02f}%)"sv,
			_name, _size, _capacity, percentage);
	}

	auto GetTrampoline() -> const REX::NotNull<std::unique_ptr<Trampoline>>&
	{
		static const auto INSTANCE = REX::NotNull(std::make_unique<Trampoline>());
		return INSTANCE;
	}
}
