#include "RE/RTTI.hpp"

namespace RE
{
	void* RTDynamicCast(void* a_inPtr, std::int32_t a_vfDelta, void* a_sourceType, void* a_targetType, std::int32_t a_isRef)
	{
		using FuncType = decltype(&RTDynamicCast);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::RTDynamicCast };
		return std::invoke(FUNC, a_inPtr, a_vfDelta, a_sourceType, a_targetType, a_isRef);
	}
}
