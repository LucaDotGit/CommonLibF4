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
		inline static constexpr auto RTTI{ ::RE::RTTI::Scaleform__SysAllocBase };
		inline static constexpr auto VTABLE{ ::RE::VTABLE::Scaleform__SysAllocBase };

		virtual ~SysAllocBase() = default; // 00

		// add
		virtual bool InitHeapEngine(const void* a_heapDesc); // 01 - { return false; }
		virtual bool ShutdownHeapEngine();					 // 02 - { return true; }
	};
	static_assert(sizeof(SysAllocBase) == 0x08);

	class __declspec(novtable) SysAlloc
		: public SysAllocBase // 00
	{
	public:
		inline static constexpr auto RTTI{ ::RE::RTTI::Scaleform__SysAlloc };
		inline static constexpr auto VTABLE{ ::RE::VTABLE::Scaleform__SysAlloc };

		~SysAlloc() override = default; // 00

		// override (SysAllocBase)
		bool InitHeapEngine(const void* a_heapDesc) override; // 01 - { return false; }
		bool ShutdownHeapEngine() override;					  // 02 - { return false; }

		// add
		virtual void* Alloc(std::size_t a_size, std::size_t a_align) = 0;											  // 03
		virtual void Free(void* a_ptr, std::size_t a_size, std::size_t a_align) = 0;								  // 04
		virtual void* Realloc(void* a_oldPtr, std::size_t a_oldSize, std::size_t a_newSize, std::size_t a_align) = 0; // 05
	};
	static_assert(sizeof(SysAlloc) == 0x08);

	class __declspec(novtable) SysAllocPaged
		: public SysAllocBase // 00
	{
	public:
		inline static constexpr auto RTTI{ ::RE::RTTI::Scaleform__SysAllocPaged };
		inline static constexpr auto VTABLE{ ::RE::VTABLE::Scaleform__SysAllocPaged };

		class Info
		{
		public:
			// members
			std::size_t minAlign;			// 00
			std::size_t maxAlign;			// 08
			std::size_t granularity;		// 10
			std::size_t sysDirectThreshold; // 18
			std::size_t maxHeapGranularity; // 20
			bool hasRealloc;				// 28
		};
		static_assert(sizeof(Info) == 0x30);

		~SysAllocPaged() override = default; // 00

		// add
		virtual void GetInfo(Info* a_info) const = 0;																					  // 03
		virtual void* Alloc(std::size_t a_size, std::size_t a_align) = 0;																  // 04
		virtual bool Free(void* a_ptr, std::size_t a_size, std::size_t a_align) = 0;													  // 05
		virtual bool ReallocInPlace(void* a_oldPtr, std::size_t a_oldSize, std::size_t a_newSize, std::size_t a_align);					  // 06 - { return false; }
		virtual void* AllocSysDirect(std::size_t a_size, std::size_t a_alignment, std::size_t* a_actualSize, std::size_t* a_actualAlign); // 07 - { return nullptr; }
		virtual bool FreeSysDirect(void* a_ptr, std::size_t a_size, std::size_t a_alignment);											  // 08 - { return false; }
		virtual std::size_t GetBase() const;																							  // 09 - { return 0; }
		virtual std::size_t GetSize() const;																							  // 0A - { return 0; }
		virtual std::size_t GetFootprint() const;																						  // 0B - { return 0; }
		virtual std::size_t GetUsedSpace() const;																						  // 0C - { return 0; }
		virtual void VisitMem(Heap::MemVisitor* a_visitor) const;																		  // 0D - { return; }
		virtual void VisitSegments(Heap::SegVisitor* a_visitor, std::size_t a_catSeg, std::size_t a_catUnused) const;					  // 0E - { return; }
	};
	static_assert(sizeof(SysAllocPaged) == 0x08);
}
