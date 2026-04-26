#pragma once

namespace RE
{
	class NiAvObject;
}

namespace RE::BSShaderUtil
{
	void SetMaterialAlpha(NiAvObject* a_object, REX::Float32 a_alpha, bool a_onlyFade);
}
