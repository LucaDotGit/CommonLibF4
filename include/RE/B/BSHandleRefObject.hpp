#pragma once

#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class __declspec(novtable) BSHandleRefObject
		: public NiRefObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSHandleRefObject };
		inline static constexpr auto VTABLE{ VTABLE::BSHandleRefObject };

		inline static constexpr auto REF_COUNT_MASK = 0x3FFui32;
		inline static constexpr auto IS_VALID_BIT = 1ui32 << 10;

		~BSHandleRefObject() override; // 00

		[[nodiscard]] bool IsValid() const noexcept;
		[[nodiscard]] std::uint32_t QRefCount() const noexcept;

		std::uint32_t IncRefCount() noexcept;
		std::uint32_t DecRefCount() noexcept;
	};
	static_assert(sizeof(BSHandleRefObject) == 0x10);
}
