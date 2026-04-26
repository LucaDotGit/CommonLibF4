#pragma once

#include "msvc/type_info.hpp"

namespace RE::RTTI
{
	template <class T>
	using RVA = REL::RTTI::RVA<T>;

	using TypeDescriptor = msvc::type_info;

	using BaseClassDescriptor = REL::RTTI::BaseClassDescriptor<TypeDescriptor>;

	using ClassHierarchyDescriptor = REL::RTTI::ClassHierarchyDescriptor<TypeDescriptor>;

	using CompleteObjectLocator = REL::RTTI::CompleteObjectLocator<TypeDescriptor>;
}

namespace RE
{
	[[nodiscard]] void* RTDynamicCast(void* a_inPtr, std::int32_t a_vfDelta, void* a_sourceType, void* a_targetType, std::int32_t a_isRef);

	template <class To, class From>
	[[nodiscard]] To DynamicCast(From* a_from) //
		noexcept(!std::is_reference_v<To>)
		requires(REL::RTTI::valid_cast<From*, To>)
	{
		if (!a_from) {
			return nullptr;
		}

		if constexpr (std::same_as<std::remove_cv_t<From>, std::remove_cv_t<To>>) {
			return const_cast<To>(a_from);
		}
		else {
			static const auto FROM_RTTI = REL::Relocation<void*>{ REX::remove_cvpr_t<From>::RTTI };
			static const auto TO_RTTI = REL::Relocation<void*>{ REX::remove_cvpr_t<To>::RTTI };

			return static_cast<To>(
				RTDynamicCast(
					const_cast<void*>(
						static_cast<const volatile void*>(a_from)),
					0,
					FROM_RTTI.get(),
					TO_RTTI.get(),
					0));
		}
	}
}
