#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) NiRefObject
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiRefObject;
		inline static constexpr const auto& VTABLE = VTABLE::NiRefObject;

		NiRefObject();

		virtual ~NiRefObject(); // 0x00

		// add
		virtual void DeleteThis() const; // 0x01

		GAME_HEAP_REDEFINE_NEW(NiRefObject);

		[[nodiscard]]
		static auto GetTotalObjectCount() noexcept -> std::uint32_t&;

		[[nodiscard]]
		auto QRefCount() const noexcept -> std::uint32_t;

		auto IncRefCount() const noexcept -> std::uint32_t;
		auto DecRefCount() const noexcept -> std::uint32_t;

		// members
		mutable volatile std::uint32_t refCount{0}; // 0x08
	};

	static_assert(sizeof(NiRefObject) == 0x10);
}
