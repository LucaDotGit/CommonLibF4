#pragma once

#include "REL/Module.hpp"

namespace REL
{
	class Offset
	{
	public:
		constexpr Offset() noexcept = default;

		explicit constexpr Offset(std::size_t a_offset) noexcept :
			_offset(a_offset)
		{
		}

		constexpr Offset& operator=(std::size_t a_offset) noexcept
		{
			_offset = a_offset;
			return *this;
		}

		[[nodiscard]] std::uintptr_t address() const { return base() + offset(); }
		[[nodiscard]] constexpr std::size_t offset() const noexcept { return _offset; }

	private:
		[[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

		std::size_t _offset{ 0 };
	};

	class VariantOffset
	{
	public:
		constexpr VariantOffset() noexcept = default;

		explicit constexpr VariantOffset(
			[[maybe_unused]] std::size_t a_f4Offset,
			[[maybe_unused]] std::size_t a_ngOffset,
			[[maybe_unused]] std::size_t a_vrOffset) noexcept
		{
#ifdef ENABLE_FALLOUT_F4
			_f4Offset = a_f4Offset;
#endif
#ifdef ENABLE_FALLOUT_NG
			_ngOffset = a_ngOffset;
#endif
#ifdef ENABLE_FALLOUT_VR
			_vrOffset = a_vrOffset;
#endif
		}

		[[nodiscard]] std::uintptr_t address() const
		{
			auto thisOffset = offset();
			return thisOffset ? base() + thisOffset : 0;
		}

		[[nodiscard]] FALLOUT_REL std::size_t offset() const noexcept
		{
			switch (Module::GetRuntime()) {
#ifdef ENABLE_FALLOUT_NG
				case Module::Runtime::NG:
					return _ngOffset;
#endif
#ifdef ENABLE_FALLOUT_F4
				case Module::Runtime::F4:
					return _f4Offset;
#endif
#ifdef ENABLE_FALLOUT_VR
				case Module::Runtime::VR:
					return _vrOffset;
#endif
				default:
					return 0;
			}
		}

		[[nodiscard]] FALLOUT_REL explicit operator Offset() const noexcept { return Offset(offset()); }

	private:
		[[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

#ifdef ENABLE_FALLOUT_F4
		std::size_t _f4Offset{ 0 };
#endif
#ifdef ENABLE_FALLOUT_NG
		std::size_t _ngOffset{ 0 };
#endif
#ifdef ENABLE_FALLOUT_VR
		std::size_t _vrOffset{ 0 };
#endif
	};
}
