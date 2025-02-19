#include "RE/Bethesda/BSScript/Struct.hpp"

namespace RE::BSScript
{
	Struct::~Struct()
	{
		if (constructed) {
			const auto size = type ? type->variables.size() : 0;
			for (auto i = 0ui32; i < size; ++i) {
				variables[i].reset();
			}

			constructed = false;
		}
	}
}
