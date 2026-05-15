#include "RE/B/BSSystemFileStreamer.hpp"

namespace RE::BSSystemFileStreamer
{
	void UncacheAll(bool a_block)
	{
		using FuncType = decltype(&BSSystemFileStreamer::UncacheAll);
		static const auto FUNC = REL::Relocation<FuncType>{ RE::ID::BSSystemFileStreamer::UncacheAll };
		std::invoke(FUNC, a_block);
	}
}
