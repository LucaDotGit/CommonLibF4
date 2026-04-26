#include "RE/N/NiAlphaProperty.hpp"

namespace RE
{
	NiAlphaProperty::NiAlphaProperty()
	{
		REL::EmplaceVtable(this);
	}

	void NiAlphaProperty::SetDestBlendMode(AlphaFunction a_func)
	{
		using FuncType = decltype(&NiAlphaProperty::SetDestBlendMode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiAlphaProperty::SetDestBlendMode };
		FUNC(this, a_func);
	}

	void NiAlphaProperty::SetSrcBlendMode(AlphaFunction a_func)
	{
		using FuncType = decltype(&NiAlphaProperty::SetSrcBlendMode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiAlphaProperty::SetSrcBlendMode };
		FUNC(this, a_func);
	}

	void NiAlphaProperty::SetTestMode(TestFunction a_func)
	{
		using FuncType = decltype(&NiAlphaProperty::SetTestMode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiAlphaProperty::SetTestMode, Offset::NiAlphaProperty::SetTestMode };
		FUNC(this, a_func);
	}

	void NiAlphaProperty::SetAlphaBlending(bool a_value)
	{
		using FuncType = decltype(&NiAlphaProperty::SetAlphaBlending);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiAlphaProperty::SetAlphaBlending };
		FUNC(this, a_value);
	}

	void NiAlphaProperty::SetAlphaTesting(bool a_value)
	{
		using FuncType = decltype(&NiAlphaProperty::SetAlphaTesting);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiAlphaProperty::SetAlphaTesting, Offset::NiAlphaProperty::SetAlphaTesting };
		FUNC(this, a_value);
	}
}
