#pragma once

#include "REL/RTTI/Rva.hpp"
#include "REX/EnumSet.hpp"

namespace REL::RTTI
{
	template <class TypeDescriptor>
	class ClassHierarchyDescriptor;

	template <class TypeDescriptor>
	class BaseClassDescriptor final
	{
	public:
		enum class Attribute : std::uint32_t
		{
			None = 0,
			NotVisible = 1 << 0,
			Ambiguous = 1 << 1,
			Private = 1 << 2,
			PrivateOrProtectedBase = 1 << 3,
			Virtual = 1 << 4,
			NonPolymorphic = 1 << 5,
			HasHierarchyDescriptor = 1 << 6
		};

		class Pmd final
		{
		public:
			// members
			std::int32_t mDisp; // 0x00
			std::int32_t pDisp; // 0x04
			std::int32_t vDisp; // 0x08
		};

		static_assert(sizeof(Pmd) == 0x0C);

		// members
		Rva<TypeDescriptor> typeDescriptor;							   // 0x00
		std::uint32_t numContainedBases;							   // 0x04
		Pmd where;													   // 0x08
		REX::EnumSet<Attribute, std::uint32_t> attributes;			   // 0x14
		Rva<ClassHierarchyDescriptor<TypeDescriptor>> classDescriptor; // 0x1C
	};

	static_assert(sizeof(BaseClassDescriptor<std::type_info>) == 0x1C);
}
