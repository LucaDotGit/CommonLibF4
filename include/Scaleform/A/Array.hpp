#pragma once

#include "Scaleform/A/Allocator.hpp"
#include "Scaleform/S/StatBasicValues.hpp"

namespace Scaleform
{
	class MemoryHeap;

	class ArrayDefaultPolicy
	{
	public:
		// members
		std::size_t capacity; // 00
	};
	static_assert(sizeof(ArrayDefaultPolicy) == 0x08);

	template <std::int32_t MinCapacity = 0, std::int32_t Granularity = 4, bool NeverShrink = false>
	class ArrayConstPolicy
	{
	public:
		// members
		std::size_t capacity; // 00
	};
	static_assert(sizeof(ArrayConstPolicy<>) == 0x08);

	template <class T, class Allocator, class SizePolicy>
	class ArrayDataBase
	{
	public:
		// members
		T* data;		   // 00
		std::size_t size;  // 08
		SizePolicy policy; // 10
	};
	static_assert(sizeof(ArrayDataBase<std::any, std::any, ArrayDefaultPolicy>) == 0x18);

	template <class T, class Allocator, class SizePolicy>
	class ArrayData
		: public ArrayDataBase<T, Allocator, SizePolicy>
	{
	public:
	};
	static_assert(sizeof(ArrayData<std::any, std::any, ArrayDefaultPolicy>) == 0x18);

	template <class T, class Allocator, class SizePolicy>
	class ArrayDataDH : ArrayDataBase<T, Allocator, SizePolicy>
	{
	public:
		// members
		const MemoryHeap* heap;
	};
	static_assert(sizeof(ArrayDataDH<std::any, std::any, ArrayDefaultPolicy>) == 0x20);

	template <class T, class Allocator, class SizePolicy>
	class ArrayDataCC
		: public ArrayDataBase<T, Allocator, SizePolicy>
	{
	public:
		T defaultValue;
	};
	static_assert(sizeof(ArrayDataCC<std::uintptr_t, std::any, ArrayDefaultPolicy>) == 0x20);

	template <class T>
	class ArrayBase
	{
	public:
		// members
		T data; // 00
	};
	static_assert(sizeof(ArrayBase<std::uintptr_t>) == 0x08);

	template <class T, std::int32_t SID = kStat_Default_Mem, class SizePolicy = ArrayDefaultPolicy>
	class Array
		: public ArrayBase<ArrayData<T, AllocatorGH<T, SID>, SizePolicy>>
	{
	public:
	};
	static_assert(sizeof(Array<std::any, kStat_Default_Mem, ArrayDefaultPolicy>) == 0x18);

	template <class T, std::int32_t SID = kStat_Default_Mem, class SizePolicy = ArrayDefaultPolicy>
	class ArrayLH
		: public ArrayBase<ArrayData<T, AllocatorLH<T, SID>, SizePolicy>>
	{
	public:
	};
	static_assert(sizeof(ArrayLH<std::any, kStat_Default_Mem, ArrayDefaultPolicy>) == 0x18);

	template <class T, std::int32_t SID = kStat_Default_Mem, class SizePolicy = ArrayDefaultPolicy>
	class ArrayDH
		: public ArrayBase<ArrayDataDH<T, AllocatorDH<T, SID>, SizePolicy>>
	{
	public:
	};
	static_assert(sizeof(ArrayDH<std::any, kStat_Default_Mem, ArrayDefaultPolicy>) == 0x20);

	template <class T, std::int32_t SID = kStat_Default_Mem, class SizePolicy = ArrayDefaultPolicy>
	class ArrayCC
		: public ArrayBase<ArrayDataCC<T, AllocatorLH<T, SID>, SizePolicy>>
	{
	public:
	};
	static_assert(sizeof(ArrayCC<std::uintptr_t, kStat_Default_Mem, ArrayDefaultPolicy>) == 0x20);

	template <class T, std::int32_t SID = kStat_Default_Mem, class SizePolicy = ArrayDefaultPolicy>
	class ArrayPOD
		: public ArrayBase<ArrayData<T, AllocatorGH_POD<T, SID>, SizePolicy>>
	{
	public:
	};
	static_assert(sizeof(ArrayPOD<std::any, kStat_Default_Mem, ArrayDefaultPolicy>) == 0x18);
}
