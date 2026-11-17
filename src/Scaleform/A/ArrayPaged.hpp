#pragma once

#include "Scaleform/A/Allocator.hpp"
#include "Scaleform/S/StatBasicValues.hpp"

namespace Scaleform
{
	template <class T, std::int32_t PageSh = 0, std::int32_t PtrPoolInc = 0, class Allocator = AllocatorPagedCC<T, 0>>
	class ArrayPagedBase : public Allocator // 0x00
	{
	public:
		// members
		std::uint64_t size;		// 0x08
		std::uint64_t numPages; // 0x10
		std::uint64_t maxPages; // 0x18
		T** pages;				// 0x20
	};

	static_assert(sizeof(ArrayPagedBase<std::any>) == 0x28);

	template <class T, std::int32_t PageSh = 6, std::int32_t PtrPoolInc = 64, std::int32_t SID = Stat_Default_Mem>
	class ArrayPagedPOD : public ArrayPagedBase<T, PageSh, PtrPoolInc, AllocatorPagedGH_POD<T, SID>>
	{
	public:
	};

	static_assert(sizeof(ArrayPagedPOD<std::any>) == 0x28);

	template <class T, std::int32_t PageSh = 0, std::int32_t PtrPoolInc = 0, std::int32_t SID = 0>
	class ArrayPagedCC : public ArrayPagedBase<T, PageSh, PtrPoolInc, AllocatorPagedCC<T, SID>>
	{
	public:
		T defaultValue; // 0x28
	};

	static_assert(sizeof(ArrayPagedCC<std::uintptr_t>) == 0x30);
}
