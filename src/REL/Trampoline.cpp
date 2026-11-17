#include "REL/Trampoline.hpp"

#include "REL/ASM/Call5.hpp"
#include "REL/ASM/Call6.hpp"
#include "REL/ASM/Jump14.hpp"
#include "REL/ASM/Jump5.hpp"
#include "REL/ASM/Jump6.hpp"
#include "REL/Memory.hpp"
#include "REL/Module.hpp"
#include "REL/ModuleSection.hpp"
#include "REX/ByteUnits.hpp"
#include "REX/Error.hpp"
#include "REX/Logging/ILogger.hpp"
#include "REX/Message.hpp"
#include "REX/W32/KERNEL32.hpp"

namespace REL::Impl
{
	namespace
	{
		constexpr auto DEFAULT_TRAMPOLINE_NAME = "Default Trampoline"sv;

		[[nodiscard]]
		constexpr auto RoundUp(std::size_t a_number, std::size_t a_multiple) noexcept -> std::size_t
		{
			if (a_multiple == 0) {
				return 0;
			}

			const auto remainder = a_number % a_multiple;
			return (remainder == 0) ? a_number : (a_number + a_multiple - remainder);
		}

		[[nodiscard]]
		constexpr auto RoundDown(std::size_t a_number, std::size_t a_multiple) noexcept -> std::size_t
		{
			if (a_multiple == 0) {
				return 0;
			}

			const auto remainder = a_number % a_multiple;
			return (remainder == 0) ? a_number : (a_number - remainder);
		}

		// Source: https://stackoverflow.com/a/54732489
		[[nodiscard]]
		__declspec(allocator)
		__declspec(restrict) auto AllocateTrampoline(std::size_t a_size, std::uintptr_t a_address) noexcept
			-> std::byte*
		{
			constexpr auto MIN_RANGE = static_cast<std::uintptr_t>(REX::Gibibyte(2).count());
			constexpr auto MAX_ADDRESS = std::numeric_limits<std::uintptr_t>::max();

			auto systemInfo = REX::W32::SYSTEM_INFO();
			REX::W32::GetSystemInfo(std::addressof(systemInfo));

			const auto granularity = systemInfo.allocationGranularity;
			const auto minAddress = a_address >= MIN_RANGE ? RoundUp(a_address - MIN_RANGE, granularity) : 0;
			const auto maxAddress =
				a_address < (MAX_ADDRESS - MIN_RANGE) ? RoundDown(a_address + MIN_RANGE, granularity) : MAX_ADDRESS;

			auto memoryInfo = REX::W32::MEMORY_BASIC_INFORMATION();
			auto currentAddress = minAddress;

			do {
				if (REX::W32::VirtualQuery(
						std::bit_cast<void*>(currentAddress),
						std::addressof(memoryInfo),
						sizeof(memoryInfo)) == 0) [[unlikely]] {
					const auto currentError = REX::GetCurrentSystemError();
					REX::Fail(
						"Failed to query the trampoline memory information.\n"
						"System Error (0x{:08X}): {}"sv,
						currentError.value(),
						currentError.message());
				}

				const auto baseAddress = std::bit_cast<std::uintptr_t>(memoryInfo.baseAddress);
				currentAddress = baseAddress + memoryInfo.regionSize;

				if (memoryInfo.state != REX::W32::MEM_FREE) {
					continue;
				}

				const auto address = RoundUp(baseAddress, granularity);
				if (address >= currentAddress || (currentAddress - address) < a_size) {
					continue;
				}

				auto* mem = REX::W32::VirtualAlloc(
					std::bit_cast<void*>(address),
					a_size,
					REX::W32::MEM_COMMIT | REX::W32::MEM_RESERVE,
					REX::W32::PAGE_EXECUTE_READWRITE);
				if (!mem) [[unlikely]] {
					const auto currentError = REX::GetCurrentSystemError();
					REX::Fail(
						"Failed to allocate trampoline memory.\n"
						"System Error (0x{:08X}): {}"sv,
						currentError.value(),
						currentError.message());
				}

				return reinterpret_cast<std::byte*>(mem);
			}
			while (currentAddress < maxAddress);

			return nullptr;
		}
	}
}

namespace REL
{
	Trampoline::Trampoline() noexcept :
		_name(Impl::DEFAULT_TRAMPOLINE_NAME)
	{
	}

	Trampoline::Trampoline(std::string a_name) noexcept :
		_name(std::move(a_name))
	{
	}

	Trampoline::Trampoline(std::shared_ptr<REX::Logging::ILogger> a_logger) noexcept :
		_logger(std::move(a_logger)),
		_name(Impl::DEFAULT_TRAMPOLINE_NAME)
	{
	}

	Trampoline::Trampoline(std::shared_ptr<REX::Logging::ILogger> a_logger, std::string a_name) noexcept :
		_logger(std::move(a_logger)),
		_name(std::move(a_name))
	{
	}

	Trampoline::~Trampoline() noexcept
	{
		Dispose();
	}

	void Trampoline::Create(size_type a_size, void* a_module)
	{
		if (a_size == 0) [[unlikely]] {
			REX::Fail(
				"Failed to create a trampoline.\n"
				"The requested size is zero.\n"
				"Trampoline Name: \"{}\""sv,
				_name);
		}

		if (!a_module) {
			const auto textSection = REL::Module::GetSingleton().GetSectionByName(REL::MODULE_SECTION_NAME_TEXT);
			if (!textSection.has_value()) [[unlikely]] {
				REX::Fail(
					"Failed to create a trampoline.\n"
					"The module does not contain a valid \"{}\" section.\n"
					"Module Version: {}\n"
					"Trampoline Name: \"{}\""sv,
					REL::MODULE_SECTION_NAME_TEXT,
					REL::Module::GetSingleton().GetVersion(),
					_name);
			}

			a_module = textSection->GetPointer<std::byte>() + textSection->GetSize();
		}

		auto* mem = Impl::AllocateTrampoline(a_size, std::bit_cast<std::uintptr_t>(a_module));
		if (!mem) [[unlikely]] {
			REX::Fail(
				"Failed to allocate trampoline memory.\n"
				"Trampoline Name: \"{}\""sv,
				_name);
		}

		Setup(
			mem,
			a_size,
			[](void* a_mem,
			   [[maybe_unused]]
			   size_type a_size) noexcept -> void {
				REX::W32::VirtualFree(a_mem, 0, REX::W32::MEM_RELEASE);
			});
	}

	void Trampoline::Setup(pointer a_mem, size_type a_size, std::move_only_function<deleter_type> a_deleter)
	{
		if (a_mem) {
			REL::WriteZeros(a_mem, a_size);
		}

		Dispose();

		_deleter = std::move(a_deleter);
		_data = a_mem;
		_capacity = a_size;
		_size = 0;

		LogStats();
	}

	__declspec(allocator) __declspec(restrict) auto Trampoline::Allocate(size_type a_size) noexcept
		-> Trampoline::pointer
	{
		const auto freeSize = _capacity - _size;
		if (a_size > freeSize) [[unlikely]] {
			REX::Fail(
				"Failed to handle a trampoline allocation request.\n"
				"The requested size exceeds the available free size.\n"
				"Trampoline Name: \"{}\"\n"
				"Allocation Size: {}\n"
				"Free Size: {}"sv,
				_name,
				a_size,
				freeSize);
		}

		auto* mem = _data + _size;
		_size += a_size;

		LogStats();
		return mem;
	}

#if (COMMONLIB_FEATURE_XBYAK == 1)
	__declspec(allocator) __declspec(restrict) auto Trampoline::Allocate(const Xbyak::CodeGenerator& a_code) noexcept
		-> Trampoline::pointer
	{
		auto* mem = Allocate(a_code.getSize());
		std::copy_n(reinterpret_cast<const_pointer>(a_code.getCode()), a_code.getSize(), mem);
		return mem;
	}
#endif

	auto Trampoline::WriteCall5(std::uintptr_t a_source, std::uintptr_t a_target) noexcept -> std::uintptr_t
	{
		const auto oldAddress = REL::ASM::Call5::TARGET(a_source);
		const auto assembly = REL::ASM::Call5(a_source, AllocateBranch5(a_target));

		const auto writeResult = REL::WriteSafeData(a_source, assembly);
		if (!writeResult.has_value()) [[unlikely]] {
			REX::Fail(
				"Failed to write a trampoline call 5 assembly.\n"
				"Trampoline Name: \"{}\"\n"
				"System Error (0x{:08X}): {}"sv,
				_name,
				writeResult.error().value(),
				writeResult.error().message());
		}

		return oldAddress;
	}

	auto Trampoline::WriteCall6(std::uintptr_t a_source, std::uintptr_t a_target) noexcept -> std::uintptr_t
	{
		const auto oldAddress = REL::ASM::Call6::TARGET(a_source);
		const auto assembly = REL::ASM::Call6(a_source, AllocateBranch6(a_target));

		const auto writeResult = REL::WriteSafeData(a_source, assembly);
		if (!writeResult.has_value()) [[unlikely]] {
			REX::Fail(
				"Failed to write a trampoline call 6 assembly.\n"
				"Trampoline Name: \"{}\"\n"
				"System Error (0x{:08X}): {}"sv,
				_name,
				writeResult.error().value(),
				writeResult.error().message());
		}

		return oldAddress;
	}

	auto Trampoline::WriteJump5(std::uintptr_t a_source, std::uintptr_t a_target) noexcept -> std::uintptr_t
	{
		const auto oldAddress = REL::ASM::Jump5::TARGET(a_source);
		const auto assembly = REL::ASM::Jump5(a_source, AllocateBranch5(a_target));

		const auto writeResult = REL::WriteSafeData(a_source, assembly);
		if (!writeResult.has_value()) [[unlikely]] {
			REX::Fail(
				"Failed to write a trampoline jump 5 assembly.\n"
				"Trampoline Name: \"{}\"\n"
				"System Error (0x{:08X}): {}"sv,
				_name,
				writeResult.error().value(),
				writeResult.error().message());
		}

		return oldAddress;
	}

	auto Trampoline::WriteJump6(std::uintptr_t a_source, std::uintptr_t a_target) noexcept -> std::uintptr_t
	{
		const auto oldAddress = REL::ASM::Jump6::TARGET(a_source);
		const auto assembly = REL::ASM::Jump6(a_source, AllocateBranch6(a_target));

		const auto writeResult = REL::WriteSafeData(a_source, assembly);
		if (!writeResult.has_value()) [[unlikely]] {
			REX::Fail(
				"Failed to write a trampoline jump 6 assembly.\n"
				"Trampoline Name: \"{}\"\n"
				"System Error (0x{:08X}): {}"sv,
				_name,
				writeResult.error().value(),
				writeResult.error().message());
		}

		return oldAddress;
	}

	auto Trampoline::AllocateBranch5(std::uintptr_t a_target) noexcept -> std::uintptr_t
	{
		using BranchType = Branch5MemoryType;

		const auto branchIt = _branchMap.find(a_target);
		if (branchIt != _branchMap.end()) {
			const auto assembly = branchIt->second;
			if (assembly.size() != sizeof(BranchType)) [[unlikely]] {
				REX::Fail(
					"Failed to find memory for a trampoline branch 5.\n"
					"Trampoline Name: \"{}\""sv,
					_name);
			}

			auto* mem = reinterpret_cast<BranchType*>(assembly.data());
			mem->address = std::bit_cast<std::array<std::uint8_t, sizeof(std::uintptr_t)>>(a_target);
			return std::bit_cast<std::uintptr_t>(mem);
		}

		auto* mem = Allocate<BranchType>(a_target);
		if (!mem) [[unlikely]] {
			REX::Fail(
				"Failed to allocate memory for a trampoline branch 5.\n"
				"Trampoline Name: \"{}\""sv,
				_name);
		}

		_branchMap.emplace(a_target, std::span{reinterpret_cast<pointer>(mem), sizeof(BranchType)});
		return std::bit_cast<std::uintptr_t>(mem);
	}

	auto Trampoline::AllocateBranch6(std::uintptr_t a_target) noexcept -> std::uintptr_t
	{
		using BranchType = Branch6MemoryType;

		const auto branchIt = _branchMap.find(a_target);
		if (branchIt != _branchMap.end()) {
			const auto assembly = branchIt->second;
			if (assembly.size() != sizeof(BranchType)) [[unlikely]] {
				REX::Fail(
					"Failed to find memory for a trampoline branch 6.\n"
					"Trampoline Name: \"{}\""sv,
					_name);
			}

			auto* mem = reinterpret_cast<BranchType*>(assembly.data());
			*mem = a_target;
			return std::bit_cast<std::uintptr_t>(mem);
		}

		auto* mem = Allocate<BranchType>(a_target);
		if (!mem) [[unlikely]] {
			REX::Fail(
				"Failed to allocate memory for a trampoline branch 6.\n"
				"Trampoline Name: \"{}\""sv,
				_name);
		}

		_branchMap.emplace(a_target, std::span{reinterpret_cast<pointer>(mem), sizeof(BranchType)});
		return std::bit_cast<std::uintptr_t>(mem);
	}

	void Trampoline::Dispose() noexcept
	{
		if (_data && _deleter) {
			std::invoke(_deleter, _data, _capacity);
		}

		_branchMap.clear();
		_data = nullptr;
		_capacity = 0;
		_size = 0;
	}

	void Trampoline::LogStats() const noexcept
	{
		if (!_logger) {
			return;
		}

		const auto percentage = _capacity == 0 ?
									static_cast<REX::Float64>(0.0) :
									(static_cast<REX::Float64>(_size) / static_cast<REX::Float64>(_capacity)) *
										static_cast<REX::Float64>(100.0);
		_logger->LogDebug("{} => {}B / {}B ({:05.02f}%)"sv, _name, _size, _capacity, percentage);
	}
}
