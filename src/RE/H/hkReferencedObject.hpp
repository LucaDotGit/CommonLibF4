#pragma once

#include "RE/H/hkBaseObject.hpp"
#include "RE/H/hkMemoryRouter.hpp"

namespace RE
{
	class hkClass;
	class hkStatisticsCollector;

	class __declspec(novtable) hkReferencedObject : public hkBaseObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkReferencedObject;
		inline static constexpr const auto& VTABLE = VTABLE::hkReferencedObject;

		inline static constexpr auto MEM_SIZE_MASK = static_cast<std::uint16_t>(0x7FFF);

		enum class LockMode : std::int32_t
		{
			NoLock = 0,
			Lock = 1,
			TryLock = 2
		};

		~hkReferencedObject() override = default; // 0x00

		// add
		virtual auto GetClassType() const -> const hkClass*; // 0x01
		virtual void DeleteThisReferencedObject() const;	 // 0x02

		HK_HEAP_REDEFINE_NEW(hkReferencedObject);

		[[nodiscard]]
		auto GetAllocatedSize() const noexcept -> std::int32_t;
		[[nodiscard]]
		auto GetReferenceCount() const noexcept -> std::int32_t;

		void AddReference() const;
		void RemoveReference() const;

		// members
		std::uint16_t memSize{std::numeric_limits<std::uint16_t>::max()}; // 0x08
		mutable volatile std::uint16_t refCount{0};						  // 0x0A
	};

	static_assert(sizeof(hkReferencedObject) == 0x10);
}
