#pragma once

#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class __declspec(novtable) BSHandleRefObject : public NiRefObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSHandleRefObject;
		inline static constexpr const auto& VTABLE = VTABLE::BSHandleRefObject;

		inline static constexpr auto REF_COUNT_MASK = static_cast<std::uint32_t>(0x3FF);
		inline static constexpr auto IS_VALID_BIT = static_cast<std::uint32_t>(1) << 10;

		~BSHandleRefObject() override; // 0x00

		[[nodiscard]]
		auto IsValid() const noexcept -> bool;
		[[nodiscard]]
		auto QRefCount() const noexcept -> std::uint32_t;

		auto IncRefCount() const noexcept -> std::uint32_t;
		auto DecRefCount() const noexcept -> std::uint32_t;
	};

	static_assert(sizeof(BSHandleRefObject) == 0x10);
}
