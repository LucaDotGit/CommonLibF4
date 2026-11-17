#pragma once

namespace RE
{
	class MemoryStats;

	class __declspec(novtable) IMemoryStoreBase
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IMemoryStoreBase;
		inline static constexpr const auto& VTABLE = VTABLE::IMemoryStoreBase;

		virtual ~IMemoryStoreBase() = default; // 0x00

		// add
		virtual auto Size(const void* a_mem) const -> std::size_t = 0;		   // 0x01
		virtual void GetMemoryStats(MemoryStats* a_stats) = 0;				   // 0x02
		virtual auto ContainsBlockImpl(const void* a_block) const -> bool = 0; // 0x03
	};

	static_assert(sizeof(IMemoryStoreBase) == 0x08);
}
