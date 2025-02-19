#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSScript/ObjectTypeInfo.hpp"
#include "RE/Bethesda/BSScript/Variable.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class ObjectTypeInfo;
	class Variable;

	class Object
	{
	public:
		~Object();

		[[nodiscard]] ObjectTypeInfo* GetTypeInfo() { return type.get(); }
		[[nodiscard]] const ObjectTypeInfo* GetTypeInfo() const { return type.get(); }
		[[nodiscard]] constexpr bool IsConstructed() const noexcept { return static_cast<bool>(constructed); }
		[[nodiscard]] constexpr bool IsInitialized() const noexcept { return static_cast<bool>(initialized); }
		[[nodiscard]] constexpr bool IsValid() const noexcept { return static_cast<bool>(valid); }

		[[nodiscard]] void* Resolve(VMTypeID a_typeID) const;

		template <class T>
		[[nodiscard]] T* Resolve() const
		{
			return reinterpret_cast<T*>(Resolve(std::to_underlying(T::FORMTYPE)));
		}

		[[nodiscard]] VMHandle GetHandle() const
		{
			return handle;
		}

		Variable* GetProperty(const BSFixedString& a_name);
		[[nodiscard]] const Variable* GetProperty(const BSFixedString& a_name) const;

		[[nodiscard]] std::uint32_t DecRef() const;
		void IncRef() const;

		F4_HEAP_REDEFINE_NEW(Object);

		// members
		std::uint32_t constructed : 1;			 // 00:00
		std::uint32_t initialized : 1;			 // 00:01
		std::uint32_t valid : 1;				 // 00:02
		std::uint32_t remainingPropsToInit : 29; // 00:03
		BSTSmartPointer<ObjectTypeInfo> type;	 // 08
		BSFixedString currentState;				 // 10
		void* lockStructure;					 // 18
		VMHandle handle;						 // 20
		std::uint32_t refCountAndHandleLock;	 // 28
		Variable variables[0];					 // 30
	};
	static_assert(sizeof(Object) == 0x30);
}
