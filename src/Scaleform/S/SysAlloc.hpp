#pragma once

namespace Scaleform::Heap
{
	class MemVisitor;
	class SegVisitor;
}

namespace Scaleform
{
	class __declspec(novtable) SysAllocBase
	{
	public:
		inline static constexpr const auto& RTTI = RE::RTTI::Scaleform__SysAllocBase;
		inline static constexpr const auto& VTABLE = RE::VTABLE::Scaleform__SysAllocBase;

		virtual ~SysAllocBase() = default; // 0x00

		// add
		virtual auto InitHeapEngine(const void* a_heapDesc) -> bool; // 0x01 - { return false; }
		virtual auto ShutdownHeapEngine() -> bool;					 // 0x02 - { return true; }
	};

	static_assert(sizeof(SysAllocBase) == 0x08);

	class __declspec(novtable) SysAlloc : public SysAllocBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RE::RTTI::Scaleform__SysAlloc;
		inline static constexpr const auto& VTABLE = RE::VTABLE::Scaleform__SysAlloc;

		~SysAlloc() override = default; // 0x00

		// override (SysAllocBase)
		auto InitHeapEngine(const void* a_heapDesc) -> bool override; // 0x01 - { return false; }
		auto ShutdownHeapEngine() -> bool override;					  // 0x02 - { return false; }

		// add
		virtual auto Alloc(std::size_t a_size, std::size_t a_align) -> void* = 0;	 // 0x03
		virtual void Free(void* a_ptr, std::size_t a_size, std::size_t a_align) = 0; // 0x04
		virtual auto Realloc(
			void* a_oldPtr,
			std::size_t a_oldSize,
			std::size_t a_newSize,
			std::size_t a_align) -> void* = 0; // 0x05
	};

	static_assert(sizeof(SysAlloc) == 0x08);

	class __declspec(novtable) SysAllocPaged : public SysAllocBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RE::RTTI::Scaleform__SysAllocPaged;
		inline static constexpr const auto& VTABLE = RE::VTABLE::Scaleform__SysAllocPaged;

		class Info
		{
		public:
			// members
			std::size_t minAlign;			// 0x00
			std::size_t maxAlign;			// 0x08
			std::size_t granularity;		// 0x10
			std::size_t sysDirectThreshold; // 0x18
			std::size_t maxHeapGranularity; // 0x20
			bool hasRealloc;				// 0x28
		};

		static_assert(sizeof(Info) == 0x30);

		~SysAllocPaged() override = default; // 0x00

		// add
		virtual void GetInfo(Info* a_info) const = 0;										 // 0x03
		virtual auto Alloc(std::size_t a_size, std::size_t a_align) -> void* = 0;			 // 0x04
		virtual auto Free(void* a_ptr, std::size_t a_size, std::size_t a_align) -> bool = 0; // 0x05
		virtual auto ReallocInPlace(
			void* a_oldPtr,
			std::size_t a_oldSize,
			std::size_t a_newSize,
			std::size_t a_align) -> bool; // 0x06 - { return false; }
		virtual auto AllocSysDirect(
			std::size_t a_size,
			std::size_t a_alignment,
			std::size_t* a_actualSize,
			std::size_t* a_actualAlign) -> void*; // 0x07 - { return nullptr; }
		virtual auto FreeSysDirect(
			void* a_ptr,
			std::size_t a_size,
			std::size_t a_alignment) -> bool;					  // 0x08 - { return false; }
		virtual auto GetBase() const -> std::size_t;			  // 0x09 - { return 0; }
		virtual auto GetSize() const -> std::size_t;			  // 0x0A - { return 0; }
		virtual auto GetFootprint() const -> std::size_t;		  // 0x0B - { return 0; }
		virtual auto GetUsedSpace() const -> std::size_t;		  // 0x0C - { return 0; }
		virtual void VisitMem(Heap::MemVisitor* a_visitor) const; // 0x0D - { return; }
		virtual void VisitSegments(Heap::SegVisitor* a_visitor, std::size_t a_catSeg, std::size_t a_catUnused)
			const; // 0x0E - { return; }
	};

	static_assert(sizeof(SysAllocPaged) == 0x08);
}
