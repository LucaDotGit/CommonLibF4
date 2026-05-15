#pragma once

#include "REL/RTTI/RVA.hpp"

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
			kNone = 0,
			kNotVisible = 1 << 0,
			kAmbiguous = 1 << 1,
			kPrivate = 1 << 2,
			kPrivateOrProtectedBase = 1 << 3,
			kVirtual = 1 << 4,
			kNonPolymorphic = 1 << 5,
			kHasHierarchyDescriptor = 1 << 6
		};

		class PMD final
		{
		public:
			// members
			std::int32_t mDisp; // 00
			std::int32_t pDisp; // 04
			std::int32_t vDisp; // 08
		};
		static_assert(sizeof(PMD) == 0x0C);

		// members
		RVA<TypeDescriptor> typeDescriptor;							   // 00
		std::uint32_t numContainedBases;							   // 04
		PMD where;													   // 08
		REX::EnumSet<Attribute, std::uint32_t> attributes;			   // 14
		RVA<ClassHierarchyDescriptor<TypeDescriptor>> classDescriptor; // 1C
	};
	static_assert(sizeof(BaseClassDescriptor<std::type_info>) == 0x1C);
}
