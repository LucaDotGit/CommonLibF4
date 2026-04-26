#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) NiRefObject
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiRefObject };
		inline static constexpr auto VTABLE{ VTABLE::NiRefObject };

		NiRefObject();

		virtual ~NiRefObject(); // 00

		// add
		virtual void DeleteThis(); // 01 - { delete this; }

		GAME_HEAP_REDEFINE_NEW(NiRefObject);

		[[nodiscard]] static std::uint32_t& GetTotalObjectCount();

		[[nodiscard]] std::uint32_t QRefCount() const noexcept;

		std::uint32_t IncRefCount() noexcept;
		std::uint32_t DecRefCount() noexcept;

		// members
		volatile std::uint32_t refCount{ 0 }; // 08
	};
	static_assert(sizeof(NiRefObject) == 0x10);
}
