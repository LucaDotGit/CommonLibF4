#pragma once

namespace RE::BSThreadEvent
{
	enum class EventType : std::int32_t
	{
		OnStartup = 0,
		OnShutdown = 1
	};

	inline void InitSDM()
	{
		using FuncType = decltype(&BSThreadEvent::InitSDM);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSThreadEvent::InitSDM);
		std::invoke(FUNC);
	}
}
