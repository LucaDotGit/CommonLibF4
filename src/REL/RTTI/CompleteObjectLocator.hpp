#pragma once

#include "REL/RTTI/Rva.hpp"
#include "REX/Enum.hpp"

namespace REL::RTTI
{
	template <class TypeDescriptor>
	class ClassHierarchyDescriptor;

	template <class TypeDescriptor>
	class CompleteObjectLocator final
	{
	public:
		enum class Signature : std::int32_t
		{
			X86 = 0,
			X64 = 1,

			_Min = X86,
			_Max = X64,

			_Count = _Max + 1
		};

		// members
		REX::Enum<Signature, std::int32_t> signature;				   // 0x00
		std::uint32_t offset;										   // 0x04
		std::uint32_t ctorDispOffset;								   // 0x08
		Rva<TypeDescriptor> typeDescriptor;							   // 0x0C
		Rva<ClassHierarchyDescriptor<TypeDescriptor>> classDescriptor; // 0x10
		Rva<CompleteObjectLocator<TypeDescriptor>> self;			   // 0x14
	};

	static_assert(sizeof(CompleteObjectLocator<std::type_info>) == 0x18);
}
