#pragma once

namespace REL
{
	inline constexpr auto MODULE_SECTION_NAME_DATA = ".data"sv;
	inline constexpr auto MODULE_SECTION_NAME_IDATA = ".idata"sv;
	inline constexpr auto MODULE_SECTION_NAME_INTERPR = ".interpr"sv;
	inline constexpr auto MODULE_SECTION_NAME_PDATA = ".pdata"sv;
	inline constexpr auto MODULE_SECTION_NAME_RDATA = ".rdata"sv;
	inline constexpr auto MODULE_SECTION_NAME_TEXT = ".text"sv;
	inline constexpr auto MODULE_SECTION_NAME_TLS = ".tls"sv;

	inline constexpr auto MODULE_SECTION_NAMES = std::array{
		MODULE_SECTION_NAME_DATA,
		MODULE_SECTION_NAME_IDATA,
		MODULE_SECTION_NAME_INTERPR,
		MODULE_SECTION_NAME_PDATA,
		MODULE_SECTION_NAME_RDATA,
		MODULE_SECTION_NAME_TEXT,
		MODULE_SECTION_NAME_TLS
	};

	class ModuleSection final
	{
	public:
		constexpr ModuleSection() noexcept = default;
		constexpr ~ModuleSection() noexcept = default;

		constexpr ModuleSection(std::uintptr_t a_proxyBase, std::uintptr_t a_address, std::uintptr_t a_size) noexcept :
			_proxyBase(a_proxyBase),
			_address(a_address),
			_size(a_size)
		{
		}

		constexpr ModuleSection(const ModuleSection&) noexcept = default;
		constexpr ModuleSection(ModuleSection&&) noexcept = default;

		constexpr auto operator=(const ModuleSection&) noexcept -> ModuleSection& = default;
		constexpr auto operator=(ModuleSection&&) noexcept -> ModuleSection& = default;

		[[nodiscard]]
		constexpr auto GetAddress() const noexcept -> std::uintptr_t
		{
			return _address;
		}

		[[nodiscard]]
		constexpr auto GetOffset() const noexcept -> std::size_t
		{
			return GetAddress() - _proxyBase;
		}

		[[nodiscard]]
		constexpr auto GetSize() const noexcept -> std::size_t
		{
			return _size;
		}

		[[nodiscard]]
		constexpr auto GetPointer() const noexcept -> void*
		{
			return std::bit_cast<void*>(GetAddress());
		}

		template <class T>
		[[nodiscard]]
		constexpr auto GetPointer() const noexcept -> T*
		{
			return static_cast<T*>(GetPointer());
		}

	private:
		std::uintptr_t _proxyBase{0};
		std::uintptr_t _address{0};
		std::size_t _size{0};
	};
}
