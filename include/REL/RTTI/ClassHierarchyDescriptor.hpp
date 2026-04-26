#pragma once

#include "REL/RTTI/RVA.hpp"

#include "REX/EnumSet.hpp"

namespace REL::RTTI
{
	template <class TypeDescriptor>
	class BaseClassDescriptor;

	template <class TypeDescriptor>
	class ClassHierarchyDescriptor
	{
	public:
		enum class Attribute : std::uint32_t
		{
			kNoInheritance = 0,
			kMultipleInheritance = 1 << 0,
			kVirtualInheritance = 1 << 1,
			kAmbiguousInheritance = 1 << 2
		};

		// members
		std::uint32_t signature;								 // 00
		REX::EnumSet<Attribute, std::uint32_t> attributes;		 // 04
		std::uint32_t numBaseClasses;							 // 08
		RVA<BaseClassDescriptor<TypeDescriptor>> baseClassArray; // 0C
	};
	static_assert(sizeof(ClassHierarchyDescriptor<std::type_info>) == 0x10);
}
