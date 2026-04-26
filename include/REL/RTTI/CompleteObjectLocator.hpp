#pragma once

#include "REL/RTTI/RVA.hpp"

#include "REX/Enum.hpp"

namespace REL::RTTI
{
	template <class TypeDescriptor>
	class ClassHierarchyDescriptor;

	template <class TypeDescriptor>
	class CompleteObjectLocator
	{
	public:
		enum class Signature : std::int32_t
		{
			kX86 = 0,
			kX64 = 1
		};

		// members
		REX::Enum<Signature, std::int32_t> signature;				   // 00
		std::uint32_t offset;										   // 04
		std::uint32_t ctorDispOffset;								   // 08
		RVA<TypeDescriptor> typeDescriptor;							   // 0C
		RVA<ClassHierarchyDescriptor<TypeDescriptor>> classDescriptor; // 10
		RVA<CompleteObjectLocator<TypeDescriptor>> self;			   // 14
	};
	static_assert(sizeof(CompleteObjectLocator<std::type_info>) == 0x18);
}
