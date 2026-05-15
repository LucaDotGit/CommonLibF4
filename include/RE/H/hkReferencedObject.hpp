#pragma once

#include "RE/H/hkBaseObject.hpp"
#include "RE/H/hkMemoryRouter.hpp"

namespace RE
{
	class hkClass;
	class hkStatisticsCollector;

	class __declspec(novtable) hkReferencedObject
		: public hkBaseObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkReferencedObject };
		inline static constexpr auto VTABLE{ VTABLE::hkReferencedObject };

		inline static constexpr auto MEM_SIZE_MASK = 0x7FFFui16;

		enum class LockMode : std::int32_t
		{
			kNoLock = 0,
			kLock = 1,
			kTryLock = 2
		};

		~hkReferencedObject() override = default; // 00

		// add
		virtual const hkClass* GetClassType() const;	 // 01
		virtual void DeleteThisReferencedObject() const; // 02

		HK_HEAP_REDEFINE_NEW(hkReferencedObject);

		[[nodiscard]] std::int32_t GetAllocatedSize() const noexcept;
		[[nodiscard]] std::int32_t GetReferenceCount() const noexcept;

		void AddReference();
		void RemoveReference();

		// members
		std::uint16_t memSize{ std::numeric_limits<std::uint16_t>::max() }; // 08
		volatile std::uint16_t refCount{ 0 };								// 0A
	};
	static_assert(sizeof(hkReferencedObject) == 0x10);
}
