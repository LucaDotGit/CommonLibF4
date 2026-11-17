#include "RE/RTTI.hpp"

namespace RE::RTTI
{
	auto RTDynamicCast(
		void* a_inPtr,
		std::int32_t a_vfDelta,
		void* a_sourceType,
		void* a_targetType,
		std::int32_t a_isRef) -> void*
	{
		using FuncType = decltype(&RTDynamicCast);
		static const auto FUNC = REL::Relocation<FuncType>(ID::RTDynamicCast);
		return std::invoke(FUNC, a_inPtr, a_vfDelta, a_sourceType, a_targetType, a_isRef);
	}
}

namespace RE
{
	auto GetTypeInfo(const REL::IId& a_rttiID) noexcept -> const RTTI::TypeDescriptor&
	{
		const auto typeDescriptor = REL::Relocation<const RTTI::TypeDescriptor*>(a_rttiID);
		return *typeDescriptor;
	}
}
