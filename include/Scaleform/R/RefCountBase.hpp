#pragma once

#include "Scaleform/M/Memory.hpp"

namespace Scaleform
{
	class __declspec(novtable) RefCountImplCore
	{
	public:
		inline static constexpr auto RTTI{ ::RE::RTTI::Scaleform__RefCountImplCore };
		inline static constexpr auto VTABLE{ ::RE::VTABLE::Scaleform__RefCountImplCore };

		virtual ~RefCountImplCore() = default; // 00

		// members
		volatile std::int32_t refCount{ 1 }; // 08
	};
	static_assert(sizeof(RefCountImplCore) == 0x10);

	class __declspec(novtable) RefCountImpl
		: public RefCountImplCore // 00
	{
	public:
		inline static constexpr auto RTTI{ ::RE::RTTI::Scaleform__RefCountImpl };
		inline static constexpr auto VTABLE{ ::RE::VTABLE::Scaleform__RefCountImpl };

		~RefCountImpl() override = default; // 00

		SF_HEAP_REDEFINE_NEW(RefCountImpl);

		[[nodiscard]] std::int32_t GetRefCount() const noexcept;

		void AddRef() noexcept;
		void Release() noexcept;
	};
	static_assert(sizeof(RefCountImpl) == 0x10);

	template <class Base, std::int32_t>
	class __declspec(novtable) RefCountBaseStatImpl
		: public Base // 00
	{
	public:
	};
	// static_assert(sizeof(RefCountBaseStatImpl<void*, 0>) == 0x10);

	template <class, std::int32_t STAT>
	class __declspec(novtable) RefCountBase
		: public RefCountBaseStatImpl<RefCountImpl, STAT> // 00
	{
	public:
		~RefCountBase() override = default; // 00
	};
	// static_assert(sizeof(RefCountBase<void*, 0>) == 0x10);
}
