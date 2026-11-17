#include "RE/I/IFormFactory.hpp"

namespace RE
{
	auto IFormFactory::GetFormFactories() -> std::span<IFormFactory*, std::to_underlying(FormType::_Count)>
	{
		static const auto FACTORIES = REL::Relocation<std::array<IFormFactory*, std::to_underlying(FormType::_Count)>*>{
			ID::IFormFactory::Factories
		};
		return {*FACTORIES};
	}
}
