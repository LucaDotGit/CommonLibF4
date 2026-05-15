#include "RE/I/IFormFactory.hpp"

namespace RE
{
	auto IFormFactory::GetFormFactories()
		-> std::span<IFormFactory*, std::to_underlying(FormType::kTotal)>
	{
		static const auto FACTORIES = REL::Relocation<std::array<IFormFactory*, std::to_underlying(FormType::kTotal)>*>{ ID::IFormFactory::Factories };
		return { *FACTORIES };
	}
}
