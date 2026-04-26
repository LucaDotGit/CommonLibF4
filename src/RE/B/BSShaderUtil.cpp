#include "RE/B/BSShaderUtil.hpp"

namespace RE::BSShaderUtil
{
	void SetMaterialAlpha(NiAvObject* a_object, REX::Float32 a_alpha, bool a_onlyFade)
	{
		using FuncType = decltype(&BSShaderUtil::SetMaterialAlpha);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSShaderUtil::SetMaterialAlpha };
		FUNC(a_object, a_alpha, a_onlyFade);
	}
}
