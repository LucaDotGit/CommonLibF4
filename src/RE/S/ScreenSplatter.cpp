#include "RE/S/ScreenSplatter.hpp"

namespace RE::ScreenSplatter
{
	void Clear()
	{
		using FuncType = decltype(&ScreenSplatter::Clear);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ScreenSplatter::Clear };
		FUNC();
	}

	void Update()
	{
		using FuncType = decltype(&ScreenSplatter::Update);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ScreenSplatter::Update };
		FUNC();
	}
}
