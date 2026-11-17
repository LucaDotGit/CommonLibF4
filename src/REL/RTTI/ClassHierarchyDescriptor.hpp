#pragma once

#include "REL/RTTI/Rva.hpp"
#include "REX/EnumSet.hpp"

namespace REL::RTTI
{
	template <class TypeDescriptor>
	class BaseClassDescriptor;

	template <class TypeDescriptor>
	class ClassHierarchyDescriptor final
	{
	public:
		enum class Attribute : std::uint32_t
		{
			NoInheritance = 0,
			MultipleInheritance = 1 << 0,
			VirtualInheritance = 1 << 1,
			AmbiguousInheritance = 1 << 2
		};

		// members
		std::uint32_t signature;								 // 0x00
		REX::EnumSet<Attribute, std::uint32_t> attributes;		 // 0x04
		std::uint32_t numBaseClasses;							 // 0x08
		Rva<BaseClassDescriptor<TypeDescriptor>> baseClassArray; // 0x0C
	};

	static_assert(sizeof(ClassHierarchyDescriptor<std::type_info>) == 0x10);
}
