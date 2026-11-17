#pragma once

#include "Scaleform/M/Memory.hpp"

namespace Scaleform
{
	class __declspec(novtable) RefCountImplCore
	{
	public:
		inline static constexpr const auto& RTTI = RE::RTTI::Scaleform__RefCountImplCore;
		inline static constexpr const auto& VTABLE = RE::VTABLE::Scaleform__RefCountImplCore;

		virtual ~RefCountImplCore() = default; // 0x00

		// members
		mutable volatile std::int32_t refCount{1}; // 0x08
	};

	static_assert(sizeof(RefCountImplCore) == 0x10);

	class __declspec(novtable) RefCountImpl : public RefCountImplCore // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RE::RTTI::Scaleform__RefCountImpl;
		inline static constexpr const auto& VTABLE = RE::VTABLE::Scaleform__RefCountImpl;

		~RefCountImpl() override = default; // 0x00

		SCALEFORM_HEAP_REDEFINE_NEW(RefCountImpl);

		[[nodiscard]]
		auto GetRefCount() const noexcept -> std::int32_t;

		void AddRef() const noexcept;
		void Release() const noexcept;
	};

	static_assert(sizeof(RefCountImpl) == 0x10);

	template <class Base, std::int32_t>
	class __declspec(novtable) RefCountBaseStatImpl : public Base // 0x00
	{
	public:
	};

	// static_assert(sizeof(RefCountBaseStatImpl<void*, 0>) == 0x10);

	template <class, std::int32_t STAT>
	class __declspec(novtable) RefCountBase : public RefCountBaseStatImpl<RefCountImpl, STAT> // 0x00
	{
	public:
		~RefCountBase() override = default; // 0x00
	};

	// static_assert(sizeof(RefCountBase<void*, 0>) == 0x10);
}
